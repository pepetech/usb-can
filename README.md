# usb-can

This is an open source C++ library for use with the <a href="https://media.giphy.com/media/J0WeVOLjuqW2I/giphy.gif">USB-CAN</a> converter developed by Rafael Silva and João Silva

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- You will need root access to a Linux machine.
- You will need to install development packages for libudev and libusb

- You will need the <a href="https://github.com/signal11/hidapi">hidapi</a> library installed 

- You will need to install libusb
```
sudo apt-get install libudev-dev libusb-1.0-0-dev
```

### Installing

A step by step series of examples that tell you how to get a development environment running

- Clone this repository to your working directory

```
sudo git clone https://github.com/Crying-Face-Emoji/MCP2210-CAN-sdk
```

- Go to the source directory

```
cd MCP2210-CAN-sdk/
```

- Run make

```
sudo make
```

## Running

- You may need to add the provided udev rules to the /etc/udev/rules.d directory.

```
sudo cp mcp2210-hid.rules /etc/udev/rules.d
```
- Depending on your user permissions, you might need to run the compilled binary with root access (sudo)

TODO: Explain how to run the automated tests for this system

## Authors

* **Rafael Silva** - *Initial work* - [crying-face-emoji](https://github.com/crying-face-emoji)
* **João Silva** - *Initial work* - [vankxr](https://github.com/vankxr)

See also the list of [contributors](https://github.com/Crying-Face-Emoji/MCP2210-CAN-sdk/graphs/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* <a href="https://github.com/kerrydwong/MCP2210-Library">kerrydwong</a> - *mcp2210 library used as base*
* <a href="https://github.com/signal11/hidapi">signal11</a> - *original HID API*
