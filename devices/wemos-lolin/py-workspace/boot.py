# This file is executed on every boot (including wake-boot from deepsleep)
# # MY IMPORTS
import time
import ubinascii
from umqttsimple import MQTTClient
import machine
import micropython
import network
# # MY IMPORTS
import esp
#esp.osdebug(None)
import uos, machine
#uos.dupterm(None, 1) # disable REPL on UART(0)
import gc
#import webrepl
#webrepl.start()
gc.collect()

ESSID = 'Gargoyle'
PSK = 'd6ny5v1x2pc7st8m'
mqttServer = 'mqtt.flespi.io'
# EXAMPLE IP ADDRESS
# mqtt_server = '192.168.1.144'
# # more MQTT settings
mqttPort = 1883
mqttToken = b'OTmCEt6k2OigAir8DleU0vCNp6AyeakSTvknOexERDIfL0de9gWZzmAOh0al0l1J'
mqttKeepalive = 60
# # #

clientId = ubinascii.hexlify(machine.unique_id())
mqttUser = b''
topic_sub = b'notification'
topic_pub = b'hello'

last_message = 0
message_interval = 5
counter = 0

# # esp.freemem()
def do_connect():
    import network
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect(ESSID, PSK)
        while not wlan.isconnected():
            pass
    print('network config:', wlan.ifconfig())
do_connect()
