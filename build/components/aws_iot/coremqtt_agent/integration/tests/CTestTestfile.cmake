# CMake generated Testfile for 
# Source directory: /workspaces/iot-reference-arm-corstone3xx/components/aws_iot/coremqtt_agent/integration/tests
# Build directory: /workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/freertos-agent-message-test[1]_include.cmake")
include("/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/mqtt-agent-task-test[1]_include.cmake")
include("/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/freertos-command-pool-test[1]_include.cmake")
include("/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/mqtt-subscription-manager-test[1]_include.cmake")
subdirs("config_mocks")
