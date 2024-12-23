# Copyright (c) 2022, Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
import uuid
import base64
import re
import os
import logging
import gitlab
import click
import sys
from datetime import datetime
from dateutil.parser import parse
from azure.iot.hub import IoTHubRegistryManager
from azure.iot.hub.models import Twin
import boto3


@click.command(name="create-device")
@click.option(
    "--out-file",
    required=False,
    help="Output file",
)
@click.pass_context
def create_device_aws(ctx, out_file):
    iot = ctx.obj["iot"]
    aws_region = os.environ.get("AWS_REGION")
    aws_account = boto3.client("sts").get_caller_identity().get("Account")
    ota_cert_id = os.environ.get("IOT_OTA_CERT_ID")
    ci_project_id = os.environ.get("CI_PROJECT_ID")
    ci_pipeline_id = os.environ.get("CI_PIPELINE_ID")
    thing_name = f"iotmsw_ci-{ci_project_id}-{ci_pipeline_id}-{str(uuid.uuid4())[:8]}"
    iot.create_thing(thingName=thing_name)["thingArn"]
    iot.attach_thing_principal(
        thingName=thing_name,
        principal=f"arn:aws:iot:{aws_region}:{aws_account}:cert/{ota_cert_id}",
    )
    with open(out_file, "w") as the_file:
        the_file.write(thing_name)


def should_this_device_be_deleted(gitlab_client, device_name):
    try:
        pre_text, a_project_id, a_pipeline_id, a_uuid = device_name.split("-")
    except ValueError:
        return False

    try:
        gitlab_project = gitlab_client.projects.get(a_project_id)
    except gitlab.exceptions.GitlabGetError:
        logging.warning(f"No Project ID associated to this device {device_name}")
        return False

    try:
        pipeline = gitlab_project.pipelines.get(a_pipeline_id)
    except gitlab.exceptions.GitlabGetError:
        logging.warning(f"No Pipeline associated to this device {device_name}")
        return True

    if pipeline.finished_at is None:
        return False

    SECOND_IN_A_DAY = 24 * 60 * 60

    ts = datetime.timestamp(parse(pipeline.finished_at))
    # Delete if older than 7 days
    if ts + (7 * SECOND_IN_A_DAY) < datetime.timestamp(datetime.now()):
        logging.info(f"Device {device_name} can be removed")
        return True
    return False


@click.command(name="cleanup")
@click.pass_context
def cleanup_aws(ctx):
    iot = ctx.obj["iot"]
    server_url = os.environ.get("CI_SERVER_URL")
    aws_region = os.environ.get("AWS_REGION")
    ota_cert_id = os.environ.get("IOT_OTA_CERT_ID")
    aws_account = boto3.client("sts").get_caller_identity().get("Account")
    principal_certificate = f"arn:aws:iot:{aws_region}:{aws_account}:cert/{ota_cert_id}"
    gitlab_client = gitlab.Gitlab(
        server_url,
        ctx.obj["private_token"],
    )

    nextToken = ""
    while True:
        things = iot.list_things(maxResults=1, nextToken=nextToken)
        for a_thing in things["things"]:
            logging.info(f"Checking device {a_thing['thingName']}")
            if should_this_device_be_deleted(gitlab_client, a_thing["thingName"]):
                iot.detach_thing_principal(
                    thingName=a_thing["thingName"], principal=principal_certificate
                )
                iot.delete_thing(thingName=a_thing["thingName"])

        if "nextToken" not in things:
            break
        nextToken = things["nextToken"]


@click.command(name="create-device")
@click.option(
    "--out-file",
    required=False,
    help="Output file",
)
@click.pass_context
def create_device_azure(ctx, out_file):
    ci_project_id = os.environ.get("CI_PROJECT_ID")
    ci_pipeline_id = os.environ.get("CI_PIPELINE_ID")
    device_id = f"iotmsw_ci-{ci_project_id}-{ci_pipeline_id}-{str(uuid.uuid4())[:8]}"
    primary_key = base64.b64encode(str(uuid.uuid4()).encode()).decode()
    secondary_key = base64.b64encode(str(uuid.uuid4()).encode()).decode()
    connection_string = f"HostName={ctx.obj['host_name']};DeviceId={device_id};SharedAccessKey={primary_key}"  # noqa: E501

    device_state = "enabled"
    ctx.obj["iothub_registry_manager"].create_device_with_sas(
        device_id, primary_key, secondary_key, device_state
    )
    with open(out_file, "w") as the_file:
        the_file.write(connection_string)
    # Add a unique tag for Device Update, using the Device Id for simplicity
    device_twin_patch = Twin()
    device_twin_patch.tags = {"ADUGroup": device_id}
    ctx.obj["iothub_registry_manager"].update_twin(device_id, device_twin_patch)


@click.command(name="cleanup")
@click.pass_context
def cleanup_azure(ctx):
    server_url = os.environ.get("CI_SERVER_URL")
    gitlab_client = gitlab.Gitlab(
        server_url,
        ctx.obj["private_token"],
    )

    processed = []
    while True:
        this_loop_ids = []
        # get_devices processes only provides maximu 1000
        # workaround to loop if there are deletion in one round
        for device in ctx.obj["iothub_registry_manager"].get_devices():
            device_id = device.device_id
            if device_id in processed:
                continue
            else:
                processed.append(device_id)
            this_loop_ids.append(device_id)
            logging.info(f"Checking device {device_id}")
            if should_this_device_be_deleted(gitlab_client, device_id):
                logging.info(f"Deleting device {device.device_id}")
                ctx.obj["iothub_registry_manager"].delete_device(device_id)
        if this_loop_ids == []:
            break


@click.group()
@click.pass_context
def azure(ctx):
    if os.getenv("AZURE_IOT_HUB_CONNECTION_STRING") is None:
        logging.error("You must set AZURE_IOT_HUB_CONNECTION_STRING in environment")
        sys.exit(1)
    ctx.obj["iothub_connection_str"] = os.getenv("AZURE_IOT_HUB_CONNECTION_STRING")
    m = re.search(r"HostName=(.*?);", ctx.obj["iothub_connection_str"])
    ctx.obj["host_name"] = m.group(1)
    ctx.obj["iothub_registry_manager"] = IoTHubRegistryManager.from_connection_string(
        ctx.obj["iothub_connection_str"]
    )


@click.group()
@click.pass_context
def aws(ctx):
    aws_region = os.environ.get("AWS_REGION")
    ctx.obj["iot"] = boto3.client("iot", aws_region)


@click.group()
@click.pass_context
@click.option(
    "--verbose",
    default=False,
    is_flag=True,
    help="Enable verbose logging",
)
@click.option(
    "--private-token",
    required=False,
    help="Private token for GitLab API requests",
)
def main(ctx, verbose, private_token):
    """
    This is utility to create/delete cloud devices dynamically in CI
    """
    ctx.obj = {
        "private_token": private_token,
    }
    if verbose:
        logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)
    else:
        logging.basicConfig(stream=sys.stdout, level=logging.INFO)


if __name__ == "__main__":
    aws.add_command(create_device_aws)
    aws.add_command(cleanup_aws)
    azure.add_command(create_device_azure)
    azure.add_command(cleanup_azure)
    main.add_command(azure)
    main.add_command(aws)
    main()
