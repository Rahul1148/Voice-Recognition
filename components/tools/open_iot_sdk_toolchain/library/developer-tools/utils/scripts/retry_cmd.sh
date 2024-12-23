#!/usr/bin/env sh
# Copyright (c) 2023, Arm  Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

set -x
set +e # handle error in the script

CMD=$1
RETRY_LIMIT=$2


for i in $(seq 1 "$RETRY_LIMIT"); do
  echo "run $i time"
  ${CMD}
  status=$?
  if [ $status -eq 0 ];then
    break
  fi
done
if [ $status -ne 0 ];then
    exit $status
fi
