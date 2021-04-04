from pytrack import Pytrack
from LIS2HH12 import LIS2HH12
import pycom
import time
import machine
import utime
import _thread

py = Pytrack()

pycom.heartbeat(False)

py.setup_int_pin_wake_up(False)
py.setup_int_wake_up(True, True)

int_counter = 0

def accel_activity_handler(pin_o):
    if pin_o():
        machine.reset()
        pycom.rgbled(0x800080)
        print('saw the interrupt')
        pybytes.send_signal(0, "Movement! " + str(acc.pitch()))
        global int_counter
        int_counter+=1
        print(int_counter)
        time.sleep(1)   
        pycom.rgbled(0)

    pycom.heartbeat(False)

## ACCELEROMETER INTERRUPT
acc = LIS2HH12()
acc.enable_activity_interrupt(1000, 200, handler=accel_activity_handler)
py.setup_sleep(3)
py.go_to_sleep()
# a_lock = _thread.allocate_lock()

# with a_lock:
#     pybytes.send_signal(0, "Movement! " + str(acc.pitch()))