import time
from LIS2HH12 import LIS2HH12 
from pysense import Pysense 
py = Pysense()
acc = LIS2HH12()
 
while True: 
   pitch = acc.pitch() 
   roll = acc.roll() 
   print('{},{}'.format(pitch,roll)) 
   time.sleep_ms(100) 
