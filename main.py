from pysense import Pysense
from LIS2HH12 import LIS2HH12
import pycom
import time
import machine
import utime
import _thread

# import gc
from LIS2HH12 import LIS2HH12
from SI7006A20 import SI7006A20
from LTR329ALS01 import LTR329ALS01
from MPL3115A2 import MPL3115A2,ALTITUDE,PRESSURE
# gc.collect()
py = Pysense()

pycom.heartbeat(False)
py.setup_int_pin_wake_up(False)
py.setup_int_wake_up(True, False)

# mp = MPL3115A2(py,mode=ALTITUDE)
mpp = MPL3115A2(py,mode=PRESSURE) # Returns pressure in Pa. Mode may also be set to ALTITUDE, returning a value in meters
si = SI7006A20(py)
t_ambient = 24.4
lt = LTR329ALS01(py)
acc = LIS2HH12()
print("Battery voltage: " + str(py.read_battery_voltage()))

int_counter = 0

def accel_activity_handler(pin_o):
    # machine.reset()
    pycom.rgbled(0x800080)
    print('saw the interrupt')
    pybytes.send_signal(0, "Movement! " + str(acc.pitch()))
    pybytes.send_signal(15, "Movement! " + str(acc.pitch()))
    global int_counter
    int_counter+=1
    print(int_counter)
    time.sleep(1)
    pycom.rgbled(0)
# pycom.heartbeat(False)


def th_func(delay, id):
    while True:
        time.sleep(delay)
        print('Running thread %d' % id)

def dump_sensor_data():
    # chrono.start()
    a_lock = _thread.allocate_lock()
    with a_lock:
        pybytes.send_signal(0,str(mpp.temperature()))
        # pybytes.send_signal(1,mp.altitude())
        # utime.sleep_ms(100)
        pybytes.send_signal(1,str(mpp.pressure())) # the pressure in (Pa)
        # utime.sleep_ms(100)
        pybytes.send_signal(2,str(si.temperature()))
        # utime.sleep_ms(100)
        # # Relative humidity, expressed as a percentage,
        # # indicates a present state of absolute humidity
        # # relative to a maximum humidity given the same temperature.
        pybytes.send_signal(3,"rel humidity in %s"%str(si.humidity())) # percentage relative humidity
        # utime.sleep_ms(100)
        pybytes.send_signal(4,str(lt.light()))
    # chrono.stop()
    # lap = chrono.read()
    # return lap
    # chrono.reset()

    pycom.heartbeat(False)


from machine import Timer
chrono = Timer.Chrono()

class Clock:

    def __init__(self):
        # self.seconds = 0
        self.__alarm = Timer.Alarm(self._seconds_handler,2, periodic=True)
        self.__chrono = Timer.Chrono()
    def _seconds_handler(self, alarm):
        # chrono.start()
        # self.seconds += 1
        # print("%02d seconds have passed" % self.seconds)
        self.__chrono.start()
        
        print("%s have passed" % str("some"))
        dump_sensor_data()
        test = self.__chrono.read()
        print(test)
        self.__chrono.stop()
        self.__chrono.reset()
        pybytes.send_signal(5,str(test))
        print('='*15)
        # print(" %s " % str(x))
        # print(x)
        print()
        # patuka = chrono.read()
        # print(patuka)
        # chrono.reset()
        # if self.seconds == 10:
            # alarm.cancel() # stop     counting after 10 seconds

# lt = LTR329ALS01(py)
clock = Clock()

## ACCELEROMETER INTERRUPT
acc = LIS2HH12()
acc.enable_activity_interrupt(1000, 200, handler=accel_activity_handler)
# py.setup_sleep(3)
# py.go_to_sleep()

# for i in range(2):
#     _thread.start_new_thread(th_func(i + 1, i))

# # TODO --------------------------------------------
# from pysense import Pysense
# from LIS2HH12 import LIS2HH12
# import pycom
# import time
# import machine
# import utime
# import _thread

# py = Pysense()

# pycom.heartbeat(False)

# py.setup_int_pin_wake_up(False)
# py.setup_int_wake_up(True, False)

# int_counter = 0

# def accel_activity_handler(pin_o):
#     if pin_o():
#         # machine.reset()
#         pycom.rgbled(0x800080)
#         print('saw the interrupt')
#         pybytes.send_signal(0, "Movement! " + str(acc.pitch()))
#         global int_counter
#         int_counter+=1
#         print(int_counter)
#         time.sleep(1)
#         pycom.rgbled(0)

#     pycom.heartbeat(False)

# ## ACCELEROMETER INTERRUPT
# acc = LIS2HH12()
# acc.enable_activity_interrupt(1000, 200, handler=accel_activity_handler)
# py.setup_sleep(3)
# py.go_to_sleep()
