# MCP2210-CAN-sdk

This is an open source C++ library for use with the <a href="https://i.imgflip.com/aze98.gif">USB-CAN</a> converter developed by Rafael Silva and João Silva

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software and how to install them

```
you will need root access to a Linux machine

You may need to add the provided udev rule (99-hid.rules) to the /etc/udev/rules.d directory.

you will need to install development packages for libudev and libusb
sudo apt-get install libudev-dev libusb-1.0-0-dev
```

### Installing

A step by step series of examples that tell you how to get a development env running

Clone this repository to your working directory

```
sudo git clone https://github.com/Crying-Face-Emoji/MCP2210-CAN-sdk
```

go to the source directory

```
cd MCP2210-CAN-sdk/
```

run make

```
sudo make
```

## Running

todo: Explain how to run the automated tests for this system

```
must run under Linux machine

the compiled code needs root access to the device and need to be run using "sudo".
```

## Authors

* **Rafael Silva** - *Initial work* - [Crying-Face-Emoji](https://github.com/Crying-Face-Emoji)
* **João Silva** - *Initial work* - [vankxr](https://github.com/vankxr)

See also the list of [contributors](https://github.com/Crying-Face-Emoji/MCP2210-CAN-sdk/graphs/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* <a href="https://github.com/kerrydwong/MCP2210-Library">kerrydwong</a> - *mcp2210 library used as base*
* <a href="https://github.com/signal11/hidapi">signal11</a> - *original HID API*
