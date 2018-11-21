MCP2210-CAN-sdk
===============

This is an open source C++ library for the USB-CAN converter developed by Rafael Silva and João Silva

This is based on a library for Microchip's USB-to-SPI protocol converter chip <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/22288A.pdf">MCP2210</a> initially developed by <a href="https://github.com/kerrydwong/MCP2210-Library">kerrydwong.

Notes:
<ul>
<li>
It was developed and test under Linux.
</li>
<li>
the compiled code needs root access to the device and need to be run using "sudo". You may need to add the provided udev rule (99-hid.rules) to the /etc/udev/rules.d directory.
</li>
<li>
you will need to install development packages for libudev, libusb.
sudo apt-get install libudev-dev libusb-1.0-0-dev
</li>
</ul>







