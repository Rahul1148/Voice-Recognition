# Copyright (c) 2022, Arm Limited and Contributors. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
from tpip_checker import (
    check_for_cmake_tpip_changes,
    check_for_url_changes_in_source_files,
    check_file_changes,
)
from unittest.mock import patch, MagicMock


def test_check_for_cmake_tpip_changes():
    # Test case 1 - FetchContent_Declare added
    change = {
        "diff": """
@@ -0,0 +1,43 @@
+FetchContent_Declare(
+    googletest
+    GIT_SHALLOW    ON
+    GIT_TAG        main
+)
"""
    }
    file = "testfile.cmake"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/\
tools/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/testfile.cmake"

    expected = f"\n[{file}]({file_url})\n"
    expected += "\n- @@ -0,0 +1,43 @@\n"
    expected += "\n- FetchContent_Declare has been modified.\n"

    assert check_for_cmake_tpip_changes(file, file_url, change) == expected

    # Test case 2 - FetchContent_Declare removed
    change = {
        "diff": """
@@ -0,0 +1,43 @@
-FetchContent_Declare(
-    googletest
-    GIT_SHALLOW    ON
-    GIT_TAG        main
-)
"""
    }
    file = "testfile.cmake"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/\
tools/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/testfile.cmake"

    expected = f"\n[{file}]({file_url})\n"
    expected += "\n- @@ -0,0 +1,43 @@\n"
    expected += "\n- FetchContent_Declare has been modified.\n"

    assert check_for_cmake_tpip_changes(file, file_url, change) == expected

    # Test case 3 - No FetchContent_Declare or URL changes
    change = {
        "diff": """
@@ -0,0 +1,43 @@
-    googletest
-    GIT_SHALLOW    ON
-    GIT_TAG        main
"""
    }
    file = "testfile.cmake"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/\
tools/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/testfile.cmake"

    expected = ""
    assert check_for_cmake_tpip_changes(file, file_url, change) == expected

    # Test case 4 - A URL change
    change = {
        "diff": """
@@ -0,0 +1,43 @@
-    googletest
-    GIT_REPOSITORY https://github.com/google/googletest.git
-    GIT_SHALLOW    ON
-    GIT_TAG        main
"""
    }
    file = "testfile.cmake"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/\
tools/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/testfile.cmake"

    expected = f"\n[{file}]({file_url})\n"
    expected += "\n- @@ -0,0 +1,43 @@\n"
    expected += "\n- A URL line has been modified.\n"

    assert check_for_cmake_tpip_changes(file, file_url, change) == expected


def test_check_for_url_changes_in_source_files():

    # Test case 1 - URL added
    change = {
        "diff": """
@@ -0,0 +1,5 @@
+void main()
+{
+    // This url should be flagged by the TPIP scanner
+    char[] = "https://docs.python.org/3/library/unittest.mock.html";
+} """
    }
    file = "testfile.c"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/\
tools/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/templates/testfile.c"

    expected = f"\n[{file}]({file_url})\n"
    expected += "\n- @@ -0,0 +1,5 @@\n"
    expected += "\n- A URL line has been modified.\n"

    assert check_for_url_changes_in_source_files(file, file_url, change) == expected

    # Test case 2 - URL removed
    change = {
        "diff": """
@@ -0,0 +1,5 @@
-    char[] = "https://docs.python.org/3/library/unittest.mock.html";
"""
    }
    file = "testfile.c"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/\
tools/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/templates/testfile.c"

    expected = f"\n[{file}]({file_url})\n"
    expected += "\n- @@ -0,0 +1,5 @@\n"
    expected += "\n- A URL line has been modified.\n"

    assert check_for_url_changes_in_source_files(file, file_url, change) == expected

    # Test case 3 - URL added in a non source file
    change = {
        "diff": """
@@ -0,0 +1,5 @@
+    "https://docs.python.org/3/library/unittest.mock.html";
"""
    }
    file = "testfile.txt"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/tools\
/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/templates/testfile.txt"

    expected = ""

    assert check_for_url_changes_in_source_files(file, file_url, change) == expected

    # Test case 4 - No URL change in a source file
    change = {
        "diff": """
@@ -0,0 +1,5 @@
+    "/* This is just a text change */";
"""
    }
    file = "testfile.c"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/tools\
/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/templates/testfile.c"

    expected = ""

    assert check_for_url_changes_in_source_files(file, file_url, change) == expected

    # Test case 5 - No URL change in a non source file
    change = {
        "diff": """
@@ -0,0 +1,5 @@
+    "This is just a text change.";
"""
    }
    file = "testfile.txt"
    file_url = "https://gitlab.oss.arm.com/engineering/iot-m-sw/open-iot-sdk/tools\
/developer-tools/-/blob/dev/anna.bridge/auto-tpip-check-test/templates/testfile.txt"

    expected = ""

    assert check_for_url_changes_in_source_files(file, file_url, change) == expected


@patch(
    "tpip_checker.check_for_cmake_tpip_changes",
    MagicMock(return_value=".cmake change detected"),
)
@patch(
    "tpip_checker.check_for_url_changes_in_source_files",
    MagicMock(return_value="URL change detected"),
)
def test_check_file_changes():
    # Test case 1 - Check .gitmodules file is handled correctly
    change = {"new_path": ".gitmodules", "diff": ""}
    path_base = "/test"
    server_url = "http://testserver.com"

    expected = "\n[.gitmodules](http://testserver.com/test/.gitmodules)\n"
    expected += "\n- The gitmodules content has been changed.\n"
    assert check_file_changes(change, path_base, server_url) == expected

    # Test case 2 - Check flow for cmake files
    change = {"new_path": "test.cmake", "diff": ""}
    path_base = "/test"
    server_url = "http://testserver.com"

    expected = ".cmake change detected"
    assert check_file_changes(change, path_base, server_url) == expected

    # Test case 3 - Check flow for other files
    change = {"new_path": "test.h", "diff": ""}
    path_base = "/test"
    server_url = "http://testserver.com"

    expected = "URL change detected"
    assert check_file_changes(change, path_base, server_url) == expected
