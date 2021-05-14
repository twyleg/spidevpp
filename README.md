# spidevpp - C++ wrapper for spidev

spidevpp provides a simple wrapper to easily use spidev from C++ applications. Many Raspberry Pi projects use the [bcm2835 library](http://www.airspayce.com/mikem/bcm2835/) to access the SPI interface. The downside is that it requires root privileges to access /dev/mem and is therefire not suitable for many applications. Using spidev to access the SPI interface is a promising alternative that allows access to non-root users based on udev rules.

The library provides the spidev interface and a GPIO interface (without any dependencies like wiringPi etc.) to drive additional CS lines, reset lines or any other output that needs to be set for an SPI slave device to work properly.

The project can be pulled in as a submodule and integrates with cmake (Check [mfrc522-cpp](https://github.com/twyleg/mfrc522-cpp) for an example). It was successfully tested on a Raspberry Pi 3B+ with Raspbian GNU/Linux 10 (buster) but should be compatible with every linux that provides spidev kernel support.

## Prerequisites

To make SPI and GPIO accessible to non-root users, make sure that you have udev rules like the following in place:

	SUBSYSTEM=="spidev", GROUP="spi", MODE="0660"
	SUBSYSTEM=="bcm2835-gpiomem", GROUP="gpio", MODE="0660"

On Raspbian/Raspberry Pi OS this should already be included in **/dev/udev/rules.d/99-com.rules** and will cause the spidev and GPIO devices to be assigned to the spi/gpio groups with read/write access. 

Make sure that your user is a member of the groups **spi** and **gpio** or create the groups and add the user witht he following commands:

	sudo groupadd spi
	sudo groupadd gpio
	sudo adduser opendashboard spi
	sudo adduser opendashboard gpio
	
## Building

Clone the repo:

	git clone https://github.com/twyleg/spidevpp
	
Create a build directory:

	cd spidev
	mkdir build
	
Run cmake:

	cd build
	cmake ..
	
Build:

	make
	
## Example application for smoke testing

The project provides a loopback example for smoke testing that expects the MISO and MOSI pin to be connected. This way the write and read functionality can be tested without an additional slave device by simply writting some data and receiving the data at the same time.

	cd spidevpp/build/apps/loopback_example_app
	./loopback_example_app /dev/spidev0.0
	
This should create the following result:

	read check PASSED
	write check PASSED
	readWrite check PASSED

## Troubleshooting

### Conflict between bcm2835 and spidev on RPi

Be aware that running an application that uses the bcm2835 spi implementation can cause spidev to malfunction. The reason seem to be that bcm2835 keeps ownership of the CS pins which makes it impossible for the spidev driver to drive the CS lines and enable the slave devices. A quick and dirty fix is to restart the RPi or to simply reload the following kernel modules:

	sudo rmmod spi_bcm2835
	sudo modprobe spi_bcm2835