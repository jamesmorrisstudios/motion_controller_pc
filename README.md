gun_controller_pc
=================

PC component of the gun controller. See gun_controller_uc or gun_controller_uc_arduino for the other component


This project takes a serial input (specifically from a uC) and translates it into keyboard and mouse events
using the Windows SendInput API. Obviously this is Windows only. At this point I have no intention to make
a Linux or Mac version.

The project was made with Visual Studio 2010.


The idea behind it is to make an easily customizable controller for PC games that don't necessarily support
game controllers.

It supports serial data in 64 byte groups. It supports sixteen 16bit analog values and 64 digital values.
The mapping of what inputs go to what (such as gyro, accelerometer, etc) can all be configured in an ini file.


Analog values such as those from a thumbstick can also be mapped to a button press from the ini file.
Right now this is limited to analog center position plus/minus threshold = button press.

Active high or active low buttons are supported, active low by default and an option to flip them on a button by button basis.


Multiple profiles are supported to change the key mapping and they can be easily switched.
