if(EXISTS "/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/mqtt-subscription-manager-test[1]_tests.cmake")
  include("/workspaces/iot-reference-arm-corstone3xx/build/components/aws_iot/coremqtt_agent/integration/tests/mqtt-subscription-manager-test[1]_tests.cmake")
else()
  add_test(mqtt-subscription-manager-test_NOT_BUILT mqtt-subscription-manager-test_NOT_BUILT)
endif()