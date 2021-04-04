import machine
import os

import gc
gc.collect()

uart = machine.UART(0, 115200)
os.dupterm(uart)

if machine.reset_cause() != machine.SOFT_RESET:
    # do
    from network import WLAN
    station = WLAN(antenna=WLAN.INT_ANT)
    # og_ssid = station.ssid()
    # og_auth = station.auth()
    station.mode(WLAN.STA)
    try:
        station.connect("Gargoylee", auth=(WLAN.WPA2, "d6ny5v1x2pc7st8m"), timeout=5000)
    except:
        station.init(mode=WLAN.AP, ssid='sid', auth=(WLAN.WPA2,"12345678"), channel=2)
# clientId = ubinascii.hexlify(machine.unique_id())
# mqttServer = 'mqtt.flespi.io'
# mqttPort = 1883
# mqttUser = b''
# mqttToken = b'GWGifQeEPqm7MbsGiO8TOmFtK79ZC6s8SYfWChqgxCd8CuCK8ArMLX4jU18mXqjE'
# mqttKeepalive = 60
# last_message = 0
# message_interval = 5
# counter = 0
# station = network.WLAN(network.STA_IF)
# station.active(True)
# station.connect(ssid, password)
# while station.isconnected() == False:
# pass
# print('Connection successful')
# print(station.ifconfig())
