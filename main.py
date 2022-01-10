import time
import pycom
import machine
from mqtt import MQTTClient_lib as MQTTClient
from LIS2HH12 import LIS2HH12

pycom.heartbeat(False)
pycom.rgbled(0x0A0A08)

acc = LIS2HH12()
client = MQTTClient("lopyPyscan", "mqtt.flespi.io", user="JIbSuYlgiTvbdhIviQoWoDy5lPZJ9y5I45rpRAtZkOZnVxG1bTNqmblyPa7My0jr",password="", port=1883)

client.connect()

while True:
    for i in range(0,20):
        acc_measurement = str(acc.acceleration())
        time.sleep(0.5)

        print("Acceleration: " + acc_measurement)
        pybytes.send_signal(1, acc_measurement)
        time.sleep(0.5)

        client.publish(topic="lopy4/acceleration", msg=acc_measurement)

        # sleep for 1 milisecond before iterating again
        time.sleep(0.5)