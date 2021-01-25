import time
import pycom

from pysense import Pysense
from LIS2HH12 import LIS2HH12
from SI7006A20 import SI7006A20
from LTR329ALS01 import LTR329ALS01
from MPL3115A2 import MPL3115A2, ALTITUDE, PRESSURE

py = Pysense()
si = SI7006A20(py)
lt = LTR329ALS01(py)
li = LIS2HH12(py)

# Disable heartbeat LED
pycom.heartbeat(False)

while True:
    pycom.rgbled(0x000014)

    print('\n\n** Digital Ambient Light Sensor (LTR-329ALS-01)')
    print('Light', lt.light())

    print('\n\n** Humidity and Temperature Sensor (SI7006A20)')
    print('Humidity', si.humidity())
    print('Temperature', si.temperature())

    mpPress = MPL3115A2(py, mode=PRESSURE)
    print('\n\n** Barometric Pressure Sensor with Altimeter (MPL3115A2)')
    print('Pressure (hPa)', mpPress.pressure()/100)

    mpAlt = MPL3115A2(py, mode=ALTITUDE)
    print('Altitude', mpAlt.altitude())
    print('Temperature', mpAlt.temperature())

    pybytes.send_signal(1, si.temperature())
    pybytes.send_signal(2, si.humidity())
    pybytes.send_signal(3, mpAlt.altitude())
    pybytes.send_signal(4, mpPress.pressure()/100)
    pybytes.send_signal(5, lt.light())
    

    pycom.rgbled(0x001400)
    time.sleep(7)