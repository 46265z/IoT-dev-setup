import pycom
import time
import machine
import utime
import _thread
from machine import Timer
from LIS2HH12 import LIS2HH12
from SI7006A20 import SI7006A20
from LTR329ALS01 import LTR329ALS01
from MPL3115A2 import MPL3115A2,ALTITUDE,PRESSURE
from pysense import Pysense
py = Pysense()

pycom.heartbeat(False)

# mp = MPL3115A2(py,mode=ALTITUDE)
mpp = MPL3115A2(py,mode=PRESSURE) # Returns pressure in Pa. Mode may also be set to ALTITUDE, returning a value in meters
si = SI7006A20(py)
t_ambient = 24.4
lt = LTR329ALS01(py)
acc = LIS2HH12()

int_counter = 0

def dump_sensor_data():
    a_lock = _thread.allocate_lock()
    with a_lock:
        pybytes.send_signal(0,"MPP Temperature: %s" % str(mpp.temperature()))
        pybytes.send_signal(1,"MPP Pressure: %s" % str(mpp.pressure())) # the pressure in (Pa)
        pybytes.send_signal(2,"SI Temperature: %s" % str(si.temperature()))
        # # Relative humidity, expressed as a percentage,
        # # indicates a present state of absolute humidity
        # # relative to a maximum humidity given the same temperature.
        pybytes.send_signal(3,"rel humidity in %s" % str(si.humidity())) # percentage relative humidity
        pybytes.send_signal(4,"Light sensor: %s" % str(lt.light()))
        pybytes.send_signal(5,"Acceleration: %s" % str(acc.pitch()))
        pybytes.send_signal(6,"Battery voltage: %s" % str(py.read_battery_voltage()))


chrono = Timer.Chrono()

class Clock:

    def __init__(self):
        # self.seconds = 0
        self.__alarm = Timer.Alarm(self._seconds_handler,2, periodic=True)
        self.__chrono = Timer.Chrono()
    def _seconds_handler(self, alarm):
        self.__chrono.start()
        
        print("%s have passed" % str("some"))
        dump_sensor_data()
        test = self.__chrono.read()
        print(test)
        self.__chrono.stop()
        self.__chrono.reset()
        pybytes.send_signal(7,"Execution time: %s" % str(test))


clock = Clock()