import machine
import urequests
import time
# from time import RTC
import machine

adc = machine.ADC(machine.Pin(32)) # Pin to Read sensor voltage

######################
# Sensor calibration #
######################

# values on right are inverse * 1000 values on left
# dry air = 759 (0%) = 1.31752305665349143610013175231
# water = 382 (100%) = 2.61780104712041884816753926702
# The Difference     = 1.30027799046692741206740751471
# 1 %                = 0.0130027799046692741206740751471

hours = str(utime.localtime()[3])
mins = str(utime.localtime()[4])
secs = str(utime.localtime()[5])
if int(secs) < 10:
	secs = '0' + secs
if int(mins) < 10:
	mins = '0' + mins
timestr = hours + ':' + mins + ':' + secs

variable = (((1 / adc.read())* 1000) / 0.0130027799046692741206740751471) - 101
if variable > 100:
	variable = 100
if variable < 0:
	variable = 0

url = 'http://192.168.1.2:8000/customurl'
headers = {'content-type': 'application/json'}
data = '{"Value": "%s", "Time": "%s"}' % (variable, timestr)
print(url, data, headers)
# resp = urequests.post(url, data=data, headers=headers) # Send the request
print(data)