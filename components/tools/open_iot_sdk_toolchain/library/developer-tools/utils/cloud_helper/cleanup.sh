#!/usr/bin/env sh
set -ex
# Copyright (c) 2023 Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

DIR=$(dirname "${0}")
HERE=$(realpath "${DIR}")

# CI may need special aws instructions for higher privileges
if [ -n "$CI_USER_PRIVILEGED_AWS_ROLE" ];then
  aws sts assume-role --role-arn "${CI_USER_PRIVILEGED_AWS_ROLE}" --role-session-name AWSCLI-Session > "/tmp/creds" 2>&1
  AWS_ACCESS_KEY_ID=$(jq -r '.Credentials.AccessKeyId' /tmp/creds)
  export AWS_ACCESS_KEY_ID="$AWS_ACCESS_KEY_ID"
  AWS_SECRET_ACCESS_KEY=$(jq -r '.Credentials.SecretAccessKey' /tmp/creds)
  export AWS_SECRET_ACCESS_KEY="$AWS_SECRET_ACCESS_KEY"
  AWS_SESSION_TOKEN=$(jq -r '.Credentials.SessionToken' /tmp/creds)
  export AWS_SESSION_TOKEN="$AWS_SESSION_TOKEN"
fi
python "$HERE"/cli.py aws cleanup
python "$HERE"/cli.py azure cleanup
