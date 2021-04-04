from network import WLAN
from mqtt import MQTTClient
import machine
import time

def settimeout(duration): 
    pass

wlan = WLAN(mode=WLAN.STA)
# wlan.antenna(WLAN.EXT_ANT)
wlan

while not wlan.isconnected(): 
     machine.idle()

print("Connected to Wifi\n")
client = MQTTClient("pySense", "mqtt.flespi.io",user="MMgKrEkM2qxlyaoseix7tffZ4EtxfkMQWRqcjBM9PaleaxwdFR8WWdMOF59JdKpY", password="", port=1883)
client.settimeout = settimeout
client.connect()

while True:
     print("Sending ON")
     client.publish("/lights", "ON")
     time.sleep(1)
     print("Sending OFF")
     client.publish("/lights", "OFF")
     time.sleep(1)
# client.set_callback(sub_cb)
# client.connect()