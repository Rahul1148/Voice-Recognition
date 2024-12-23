# Copyright (c) 2022, Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
import re
import json


def _get_license_json_table(license_md_file):
    with open(license_md_file) as the_file:
        contents = the_file.read()
    start_expression = "```json:table"
    end_expression = "```"
    pattern = f"{start_expression}(.*){end_expression}"
    matches = re.findall(pattern, contents, re.DOTALL)

    # this repository doesn't have license json
    if len(matches) == 0:
        return None
    assert len(matches) == 1, "We expect exactly one json table in this file"
    return matches[0]


def _update_json(json_table, component_repo, component_new_sha):
    tmp_json = json.loads(json_table)
    json_components = tmp_json["items"]
    for an_item in json_components:
        found = False
        for key, value in an_item.items():
            if key == "Origin" and value == component_repo.split(".git")[0]:
                found = True
                break
        if found:
            an_item["Version"] = component_new_sha
            break

    return json.dumps(tmp_json, indent=4)


def update_license(license_file, component_repo, updated_sha):
    original = _get_license_json_table(license_file)
    if None is original:
        return
    replace = _update_json(original, component_repo, updated_sha)

    with open(license_file) as the_file:
        contents = the_file.read()
    contents = contents.replace(original, "\n" + replace + "\n")
    with open(license_file, "w") as the_file:
        the_file.write(contents)
