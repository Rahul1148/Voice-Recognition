#!/usr/bin/env python3

# Copyright (c) 2023, Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

import base64
import click
import hashlib
import os
from datetime import datetime, timedelta, timezone

from azure.core.exceptions import HttpResponseError
from azure.identity import DefaultAzureCredential
from azure.iot.deviceupdate import DeviceUpdateClient
from azure.storage.blob import ContainerClient

# The following environment variables are predefined in the CI environment and
# same across all pipelines, so they are not passed as command line arguments.
endpoint = os.environ["AZURE_DEVICE_UPDATE_ENDPOINT"]
instance = os.environ["AZURE_DEVICE_UPDATE_INSTANCE"]
storage_url = os.environ["AZURE_STORAGE_URL"]
storage_container = os.environ["AZURE_STORAGE_CONTAINER"]
storage_conn_str = os.environ["AZURE_STORAGE_CONN_STR"]
storage_sas_token = os.environ["AZURE_STORAGE_SAS_TOKEN"]

# DefaultAzureCredential() gets Azure Active Directory service principal
# from the environment variables
# AZURE_CLIENT_ID, AZURE_CLIENT_SECRET, AZURE_TENANT_ID
device_update_client = DeviceUpdateClient(
    credential=DefaultAzureCredential(), endpoint=endpoint, instance_id=instance
)
storage_client = ContainerClient.from_connection_string(
    storage_conn_str, container_name=storage_container
)


@click.group()
def main():
    pass


def get_file_size(file_path):
    return os.path.getsize(file_path)


def get_file_hash(file_path):
    with open(file_path, "rb") as f:
        bytes = f.read()  # read entire file as bytes
        return base64.b64encode(hashlib.sha256(bytes).digest()).decode("utf-8")


def get_remote_file_path(directory_name, file_name):
    return directory_name + "/" + os.path.basename(file_name)


def get_remote_file_url_with_sas(directory_name, file_name):
    return (
        storage_url
        + "/"
        + storage_container
        + "/"
        + get_remote_file_path(directory_name, file_name)
        + "?"
        + storage_sas_token
    )


@main.command(
    name="import",
    help="Upload files to storage container and import update to Device Update service",
)
@click.option("--manifest", required=True, help="Path to import manifest file")
@click.option(
    "--payload",
    required=True,
    multiple=True,
    help="Path to a payload to import (can be passed more than once)",
)
@click.option("--directory", required=True, help="Directory in the storage container")
def import_update(manifest, payload, directory):
    for blob in [manifest, *payload]:
        with open(blob, "rb") as data:
            remote_path = get_remote_file_path(directory, blob)
            storage_client.upload_blob(name=remote_path, data=data)
            print("Uploaded to storage container: " + remote_path)

    update = [
        {
            "importManifest": {
                "url": get_remote_file_url_with_sas(directory, manifest),
                "sizeInBytes": get_file_size(manifest),
                "hashes": {"sha256": get_file_hash(manifest)},
            },
            "files": [
                {
                    "fileName": os.path.basename(payload[0]),
                    "url": get_remote_file_url_with_sas(directory, payload[0]),
                }
            ],
        }
    ]
    try:
        response = device_update_client.device_update.begin_import_update(update)
        response.wait()
    except HttpResponseError as e:
        print("Failed to import update: {}".format(e))

    print("Update imported successfully")


@main.command(name="deploy", help="Deploy a device update")
@click.option("--deployment-id", required=True, help="ID to give to the deployment")
@click.option("--provider", required=True, help="Provider of the update")
@click.option("--update", required=True, help="Name of the update")
@click.option("--version", required=True, help="Version of the update")
@click.option("--group", required=True, help="Group to deploy the update to")
@click.option(
    "--delay",
    default=0,
    type=int,
    help="Optional delay (in seconds) so the device has time to can get online first",
)
def deploy_update(deployment_id, provider, update, version, group, delay):
    try:
        deployment = {
            "deploymentId": deployment_id,
            "startDateTime": str(datetime.now(timezone.utc) + timedelta(seconds=delay)),
            "update": {
                "updateId": {"provider": provider, "name": update, "version": version},
            },
            "groupId": group,
        }
        device_update_client.device_management.create_or_update_deployment(
            group, deployment_id, deployment
        )
        print("Update deployed: " + deployment_id)
    except HttpResponseError as e:
        print("Failed to deploy update: {}".format(e))


@main.command(name="cleanup", help="Delete the deployment, update and blobs")
@click.option("--group", required=True, help="Group the updated was deployed to")
@click.option("--deployment-id", required=True, help="Deployment ID")
@click.option("--provider", required=True, help="Provider of the update")
@click.option("--update", required=True, help="Name of the update")
@click.option("--version", required=True, help="Version of the update")
@click.option(
    "--directory", required=True, help="Directory of blobs in the storage container"
)
def cleanup_update(group, deployment_id, provider, update, version, directory):
    try:
        device_update_client.device_management.delete_deployment(group, deployment_id)
        print("Deployment deleted")
    except HttpResponseError as e:
        print("Failed to delete deployment: {}".format(e))

    try:
        device_update_client.device_update.begin_delete_update(
            provider, update, version
        )
        print("Update deleted")
    except HttpResponseError as e:
        print("Failed to delete update: {}".format(e))

    for blob in storage_client.list_blobs(name_starts_with=(directory + "/")):
        storage_client.delete_blob(blob.name)
        print("Deleted blob from storage container: " + blob.name)


if __name__ == "__main__":
    main()
