#!/usr/bin/env sh
set -ex
# Copyright (c) 2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
DIR=$(dirname "${0}")
HERE=$(realpath "${DIR}")

show_usage (){
    cat <<EOF
Usage: $0 [options]

Generate aws credentials

Options:
    --help            Show this help
    --out-creds-file  Out file Credetials
    --out-keys-file   Out file Keys
EOF
}

SHORT=c:,k:,h
LONG=out-creds-file:,out-keys-file:,help
OPTS=$(getopt --options $SHORT --longoptions $LONG -- "$@")

eval set -- "$OPTS"

while :
do
  case "$1" in
    -h | --help )
      show_usage
      exit 0
      ;;
    -c | --out-creds-file )
      OUT_CREDS_PATH=$2
      shift 2
      ;;
    -k | --out-keys-file )
      OUT_KEYS_PATH=$2
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

if [ -z "$OUT_CREDS_PATH" ] || [ -z "$OUT_KEYS_PATH" ];then
  show_usage
  exit 1
fi
# CI needs special aws instructions for higher privileges
if [ -n "$CI_USER_PRIVILEGED_AWS_ROLE" ];then
  aws sts assume-role --role-arn "${CI_USER_PRIVILEGED_AWS_ROLE}" --role-session-name AWSCLI-Session > "/tmp/creds" 2>&1
  AWS_ACCESS_KEY_ID=$(jq -r '.Credentials.AccessKeyId' /tmp/creds)
  export AWS_ACCESS_KEY_ID="$AWS_ACCESS_KEY_ID"
  AWS_SECRET_ACCESS_KEY=$(jq -r '.Credentials.SecretAccessKey' /tmp/creds)
  export AWS_SECRET_ACCESS_KEY="$AWS_SECRET_ACCESS_KEY"
  AWS_SESSION_TOKEN=$(jq -r '.Credentials.SessionToken' /tmp/creds)
  export AWS_SESSION_TOKEN="$AWS_SESSION_TOKEN"
fi

python "${HERE}"/cli.py aws create-device --out-file /tmp/aws_device_id
AWS_IOT_THING_NAME=$(cat /tmp/aws_device_id)
export AWS_IOT_THING_NAME="$AWS_IOT_THING_NAME"

envsubst < "${HERE}"/header_templates/aws_clientcredential_h_template > "${OUT_CREDS_PATH}"

# Everything that is needed for aws_clientcredential_keys must already be set in the environment
envsubst < "${HERE}"/header_templates/aws_clientcredential_keys_h_template > "${OUT_KEYS_PATH}"
