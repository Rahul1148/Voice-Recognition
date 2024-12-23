# Arm® Mali™-C55 bare-metal driver


## Introduction

This reporitory contains a bare-metal driver for Arm® Mali™-C55 ISP.


## Directory structure

The project contains the following subdirectories within [software/driver/bare-metal](./software/driver/bare-metal/):

| Subdirectory | Description |
| ---          | ---         |
|[app](./software/driver/bare-metal/app/)|Example application that initialize the driver and provides the callback skeletons|
|[app/control](./software/driver/bare-metal/app/control/)|Adaptation layer for control tool|
|[inc](./software/driver/bare-metal/inc/)|Firmware configuration settings for a specific platform|
|[inc/api](./software/driver/bare-metal/inc/api/)|Headers for API|
|[inc/isp](./software/driver/bare-metal/inc/isp/)|Headers for ISP driver|
|[inc/sys](./software/driver/bare-metal/inc/sys/)|Headers for platform adaptation driver|
|[src/calibration](./software/driver/bare-metal/src/calibration/)|Example calibration files for a sensor|
|[src/driver/lens](./software/driver/bare-metal/src/driver/lens/)|Skeleton for lens driver|
|[src/driver/sensor](./software/driver/bare-metal/src/driver/sensor/)|Skeleton for sensor driver|
|[src/fw](./software/driver/bare-metal/src/fw/)|Helpers for fw_lib|
|[src/fw_lib](./software/driver/bare-metal/src/fw_lib)|Driver source for ISP driver|
|[src/fw/platform](./software/driver/bare-metal/src/platform/)|Skeleton for platform adaptation driver|


## Getting started

The project contains an example [Makefile](./software/driver/bare-metal/Makefile)
to show how to compile the whole project.

For reuse in other projects, there is a [CMakeLists.txt](./CMakeLists.txt) file
for CMake integration. This file provides the `isp_driver` library. It is linked
against `isp_firmware_config` library which should provide include path for
`runtime_initialization_settings.h`. For a standalone application, it needs to
be linked with a platform adaptation driver, a sensor driver, a lens driver, and
calibrations.


## Contributing

See [CONTRIBUTING](CONTRIBUTING.md) for more information.


## License

Source code is available under the terms of the BSD 3-Clause License. See the
[LICENSE](./LICENSE) file for more details.

## Security issues reporting

If you find any security vulnerabilities, please do not report it in the GitLab issue tracker. Instead, send an email
to the security team at arm-security@arm.com stating that you may have found a security vulnerability in the Arm®
Mali™-C55 bare-metal driver.

More details can be found at [Arm Developer website](https://developer.arm.com/support/arm-security-updates/report-security-vulnerabilities).
