# Siemens RCR10 boilercontrol for Raspberry Pi

## Overview

The protocol used by Siemens for the RCR10/433 isn't well documented, and therefore isn't supported by the more "commercial" radio transceivers out there, such as the RFXCom RFXTRX433 generation USB transceivers. Therefore a more 'hacky' approach is required to integrate it with other popular Domotics control software (such as [Domoticz](http://www.domoticz.com))

You will need: 

* [Cheap 433Mhz Transmitter and Receiver modules](http://www.amazon.co.uk/433Mhz-transmitter-receiver-Arduino-project/dp/B00E9OGFLQ)
* [Analogue audio cable with 3.5mm plug](http://www.amazon.co.uk/Stereo-Audio-Cable-Meter-3-5mm/dp/B000Q6LT26/ref=sr_1_1?s=electronics&ie=UTF8&qid=1459175899&sr=1-1&keywords=stereo+lead)
* A 1k resistor, and a 4.2k resistor.

This is a (little bit hacky) utility for sending "call for heat" ON and OFF messages to my Siemens RCR10/433 receiver boiler control relay.

*NOTE*: The ON and OFF packets herein are specific to my receiver: they probably contain some ID that was exchanged during the "learn" mode pairing between receiver and thermostat.

Currently configured to use WiringPi PIN 0 (GPIO 17) to transmit on (should be connected to DATA pin of a 433Mhz transmitter).

NOTE: the install script will setup an init script (debian-compatible) that exports GPIO 17 with direction=out.

## Usage

To call for heat (turn boiler ON):

    callforheat 1

To cancel call for heat (turn boiler OFF):

    callforheat 0

NOTE: sudo is not needed if GPIO-Admin was used the export the pins and the current user is in the gpio group. Otherwise, sudo is needed when executing, to ensure that the pin is accessible.

## Dependencies

[WiringPi](http://wiringpi.com/)

Install depends on:
[GPIO-Admin](https://github.com/quick2wire/quick2wire-gpio-admin)

## Build
To build for the Raspberry PI:

    make PLATFORM=pi

To install on the Raspberry PI:

    make install PLATFORM=pi

To uninstall

    make uninstall PLATFORM=pi

## More Information

A blog post Ross made in response to a question about his project with led to his authoring of the original repo:

http://rossharper.net/2015/11/decoding-a-siemens-rcr10433-thermostat-signal-to-control-a-boiler-from-a-raspberry-pi/
