# Pico Real-time Webserver

[![CMake Build Workflow](https://github.com/milosz275/pico-realtime-webserver/actions/workflows/cmake.yml/badge.svg)](https://github.com/milosz275/pico-realtime-webserver/actions/workflows/cmake.yml)
[![CodeQL with CMake Build](https://github.com/milosz275/pico-realtime-webserver/actions/workflows/codeql.yml/badge.svg)](https://github.com/milosz275/pico-realtime-webserver/actions/workflows/codeql.yml)
[![Doxygen Pages](https://github.com/milosz275/pico-realtime-webserver/actions/workflows/doxygen-pages.yml/badge.svg)](https://github.com/milosz275/pico-realtime-webserver/actions/workflows/doxygen-pages.yml)
[![License](https://img.shields.io/github/license/milosz275/pico-realtime-webserver)](/LICENSE)

![logo](assets/logo.png)

This is an example repository for a real-time web server running on Raspberry Pi Pico W using [FreeRTOS Kernel](https://github.com/freertos/freertos-kernel). The server is capable of serving static files and handling multiple connections at the same time.

- [GitHub repository](https://github.com/milosz275/pico-realtime-webserver)
- [Doxygen documentation](https://milosz275.github.io/pico-realtime-webserver/)

## Table of Contents

- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Configuration](#configuration)
  - [Building](#building)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Getting Started

Before cloning the repository, check if you already have those repositories with corresponding exports set up:

| Dependency | Export Path |
|------------|--------------|
| [pico-sdk](https://github.com/raspberrypi/pico-sdk) | `PICO_SDK_PATH` |
| [pico-extras](https://github.com/raspberrypi/pico-extras) | `PICO_EXTRAS_PATH` |
| [freertos-kernel](https://github.com/freertos/freertos-kernel) | `FREERTOS_KERNEL_PATH` |

If you don't have them set up, you can simply clone the repository with submodules:

```bash
git clone --recurse-submodules https://github.com/milosz275/pico-realtime-webserver.git
cd pico-realtime-webserver
```

This will clone the repository with all the required submodules in `lib` directory.

If you already have the repositories and exports set up, you can clone the repository without submodules:

```bash
git clone https://github.com/milosz275/pico-realtime-webserver.git
cd pico-realtime-webserver
```

CMake will automatically find the required libraries if the exports are set up correctly.

### Prerequisites

The following commands install the required dependencies on Ubuntu and Debian based systems:

```bash
sudo apt-get install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential ninja-build
```

### Configuration

Please create a `wifi_credentials.h` file inside `include` directory. The file should contain the following lines:

```c
#ifndef _WIFI_CREDENTIALS_H
#define _WIFI_CREDENTIALS_H

#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "wifi_password"

#endif
```

### Building

To build the project use `chmod +x ./build.sh && ./build.sh` or run the following commands:

```bash
mkdir build
cd build
cmake -G Ninja ..
ninja
```

This will produce `.uf2` file located in `build/src` directory. You can flash it to your Pico W device using the USB mass storage mode. [Instruction](https://youtu.be/d-karKb53og?si=i1do_1Gk_GdIMxir)

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/milosz275/pico-realtime-webserver/blob/main/LICENSE) file for details.

## Acknowledgments

- [Pico W Template](https://github.com/milosz275/pico-w-template)
- [Pico W FreeRTOS](https://github.com/milosz275/pico-w-freertos)
- [Pico Webserver Example](https://github.com/krzmaz/pico-w-webserver-example)
