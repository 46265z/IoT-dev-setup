# Expansion Board 3.0
Съвместимост с WiPy 3.0,  LoPy4, SiPy, FiPy и GPy.

[Product page](https://docs.pycom.io/datasheets/expansionboards/expansion3/)
[Datasheet](https://docs.pycom.io/gitbook/assets/expansion3-specsheet-1.pdf)
[Pinout](https://docs.pycom.io/gitbook/assets/expansion3-pinout.pdf)

![](https://pycom.io/wp-content/uploads/2020/03/Website-Product-Shots-ExpB-Front.png)

---
## Connecting to MQTT broker
Note that in the follow example I used WiPy 3.0 with the expansion board.

### boot.py
```python
import time
from umqttsimple import MQTTClient
import ubinascii
import machine
import micropython
import network
# import esp
# esp.osdebug(None)
import gc
gc.collect()

ssid = 'YOUR_WIFI_SSID'
password = 'YOUR_WIFI_PASSWORD'
mqtt_server = 'BROKER_IP_ADDRESS_OR_DOMAIN_NAME'
#EXAMPLE IP ADDRESS
#mqtt_server = '192.168.1.144'
client_id = ubinascii.hexlify(machine.unique_id())
topic_sub = b'notification'
topic_pub = b'hello'

last_message = 0
message_interval = 5
counter = 0

station = network.WLAN(network.STA_IF)

station.active(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

print('Connection successful')
print(station.ifconfig())
```

### main.py
In this example the main file could be empty. The following code blinks the onboard led.
```python
import pycom
import time

pycom.heartbeat(False)

while True:
    #colors in hexadecimal (0xRRGGBB)
    pycom.rgbled(0xFF0000)  # Red
    time.sleep(1)
    pycom.rgbled(0x00FF00)  # Green
    time.sleep(1)
    pycom.rgbled(0x0000FF)  # Blue
    time.sleep(1)
```
