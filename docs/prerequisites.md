# Prerequisites

flespi account

PyBytes account

Pycom Firmware Updater tool https://software.pycom.io/downloads/linux-1.16.5.html

nodeJS

vscode/atom with pymakr addon

on linux, add urself to dialout/uucp group

__how to__
on arch:

`$ sudo usermod -a -G uucp <username>`

`$ sudo chmod 666 /dev/tty<device-port>`

after this pymakr plugin for atom/vscode should work as expected

on win, make sure u have all drivers (CH340, CP21XX, etc)

Serial COM Terminal of ur choice

Arduino IDE ?

python 3

esptool

maybe ampy?

<small>recommended</small>

[<small> mosquitto](https://mosquitto.org/download/) as local mqtt broker </small>

<small> pub sub tools </small>

docker

docker-compose

golang
