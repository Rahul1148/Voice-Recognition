#!/usr/bin/env sh
set -ex
# Copyright (c) 2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

DIR=$(dirname "${0}")
HERE=$(realpath "${DIR}")

show_usage() {
    cat <<EOF
Usage: $0 [options]

Generate Azure credentials

Options:
    --help            Show this help
    --out-file        Out file Credetials
    --template-type   Out file Keys
EOF
}

SHORT=c:,k:,h
LONG=template-type:,out-file:,help
OPTS=$(getopt --options $SHORT --longoptions $LONG -- "$@")

eval set -- "$OPTS"

while :
do
  case "$1" in
    -h | --help )
      show_usage
      exit 0
      ;;
    -t | --template-type )
      template_type=$2
      shift 2
      ;;
    -o | --out-file )
      out_file=$2
      shift 2
      ;;
    --)
      shift;
      break
      ;;
    *)
      echo "Unexpected option: $1"
      show_usage
      exit 2
      ;;
  esac
done

if [ -z "$template_type" ] || [ -z "$out_file" ]; then
  show_usage
  exit 1
fi

python "${HERE}"/cli.py azure create-device --out-file /tmp/azure_device_id
IOTHUB_DEVICE_CONNECTION_STRING=$(cat /tmp/azure_device_id)
export IOTHUB_DEVICE_CONNECTION_STRING="$IOTHUB_DEVICE_CONNECTION_STRING"
# Azure uses two kind of template files.
# create header files depending on the template_type
if [ "$template_type" = "iot" ]
then
  envsubst < "${HERE}"/header_templates/iothub_credentials_h_template > "$out_file"
elif [ "$template_type" = "nx" ]
then
  HOST_NAME=$(echo "$IOTHUB_DEVICE_CONNECTION_STRING" | cut -d ";" -f1 |cut -d"=" -f2)
  export HOST_NAME="$HOST_NAME"
  DEVICE_ID=$(echo "$IOTHUB_DEVICE_CONNECTION_STRING" | cut -d ";" -f2 |cut -d"=" -f2)
  export DEVICE_ID="$DEVICE_ID"
  DEVICE_SYMMETRIC_KEY=$(echo "$IOTHUB_DEVICE_CONNECTION_STRING" | cut -d ";" -f3 |cut -d"=" -f2)
  export DEVICE_SYMMETRIC_KEY="$DEVICE_SYMMETRIC_KEY"
  envsubst <"${HERE}"/header_templates/nx_azure_iot_credentials_h_template > "$out_file"
fi
