if(EXISTS "/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/freertos-agent-message-test[1]_tests.cmake")
  include("/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/freertos-agent-message-test[1]_tests.cmake")
else()
  add_test(freertos-agent-message-test_NOT_BUILT freertos-agent-message-test_NOT_BUILT)
endif()
