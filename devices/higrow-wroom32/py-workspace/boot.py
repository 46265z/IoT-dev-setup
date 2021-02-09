import time
from umqttsimple import MQTTClient
import ubinascii
import machine
import micropython
import network
import esp
esp.osdebug(None)
import gc
gc.collect()

ESSID = ''
PSK = ''
mqtt_server = 'mqtt.flespi.io'
# EXAMPLE IP ADDRESS
# mqtt_server = '192.168.1.144'
# # more MQTT settings
mqtt_port = 1883
mqtt_token = b''
mqttKeepalive = 60
# # #

client_id = ubinascii.hexlify(machine.unique_id())
mqtt_user = b''
topic_sub = b'notification'
topic_pub = b'hello'

last_message = 0
message_interval = 5
counter = 0

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