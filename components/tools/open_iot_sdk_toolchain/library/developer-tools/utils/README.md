
Open IoT SDK CI needs Azure and AWS devices for testing. This utility provides wrappers for programmatic ways to create Azure and AWS devices.

This document is intended for developers who updates the Open IoT SDK CI. Normally such developers have the permissions and infrastructure to follow the steps below.

### Pre-Requisite

Device in Azure or AWS are created in this format `CI_PROJECT_ID:CI_PIPELINE_ID:UUID`

In CI those parameters will be set. If you need to test from local environment. You can export these to an appropriate variable.

### AWS
#### Pre-requisite
* Certificate for IoT Things are pre-created and store to environmental variable such as
  `IOT_OTA_CLIENT_CERT`, `IOT_OTA_CLIENT_PRIV` and `IOT_OTA_CLIENT_PUB`
  Locally you may create a ceritficate using:
  `aws iot create-keys-and-certificate --set-as-active`
* An IoT Policy exists and attached to the certificate. This is also a one time operation done in CI. Locally, you may do:
  `aws iot attach-policy --target ${certificateArn} --policy-name ${policyName}`
#### Steps to create a device
* Export Credentials copied from AWS LZ. These include AWS_TOKEN, SESSION_ID etc.
* AWS things are created and associated to a pre-created certificate. The certificate credentials must be set correctly in environment variables such `IOT_OTA_CLIENT_CERT`, `IOT_OTA_CLIENT_PRIV` and `IOT_OTA_CLIENT_PUB` (as given above)

Set other environmental variables such as:
  * IOT_OTA_CERT_ID
  * AWS_REGION
  * AWS_IOT_END_POINT_NAME
* Run `./developer-tools/utils/cloud_helper/aws.sh`
## Azure
* Set credentials:
  * Utility uses `AZURE_IOT_HUB_CONNECTION_STRING`
* Run /cloud_helper/az.sh nx (or iot)

## cleanup devices
cleanup of device is done if the pipeline which created the device finished 7 days ago.

* You can run ./developer-tools/utils/cloud_helper/cleanup.sh
