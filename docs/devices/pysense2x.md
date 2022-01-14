# Pysense 2.0X

Pysense 2.0 X е нов сензорен разширител, съвместим с всички многомрежови модули на Pycom. Той пасва на всички платки Pycom и съдържа редица сензори, като околна светлина, налягане и влажност. Има много нови функции, включително 6-пинов конектор за новата гама сензори Pynode.

[Product page](https://docs.pycom.io/datasheets/expansionboards/pysense2/)
[Datasheet](https://docs.pycom.io/gitbook/assets/PySense2X_specsheet.pdf)
[Pinout](https://docs.pycom.io/gitbook/assets/pysense2-pinout.pdf)

![](https://pycom.io/wp-content/uploads/2020/05/BFB77E75-96AE-4401-B6A2-0DDDC2271464.png)

---
!!! type danger "Когато преместите LoPy модула върху PySense, трябва да създадем и активираме у-вото отново като посочим, че използваме PySense2.0X."


## Нужни

За работя със сензорния разширител ни трябват съответните библиотеки:

- Основната библиотека на платката - https://github.com/pycom/pycom-libraries/blob/master/shields/pysense_2.py
- Accelerometer ([LIS2HH12](https://github.com/pycom/pycom-libraries/blob/master/shields/lib/LIS2HH12.py))
- Light Sensor ([LTR329ALS01](https://github.com/pycom/pycom-libraries/blob/master/shields/lib/LTR329ALS01.py))
- Pressure Sensor ([MPL3115A2](https://github.com/pycom/pycom-libraries/blob/master/shields/lib/MPL3115A2.py))
- Temperature / Humidity Sensor ([SI7006A20](https://github.com/pycom/pycom-libraries/blob/master/shields/lib/SI7006A20.py))
- MQTT с променено име на класа (включена е в сорс кода в края на документа)


## Програмиране на модула

!!! type danger "Ако при качване на код, получавате грешка `Firmware for Shield2 out of date`, трябва да обновите фирмуера на разширителната платка."

Firmware for Shield2 out of date error:
```python
Traceback (most recent call last):
  File "main.py", line 26, in <module>
  File "/flash/lib/pycoproc_2.py", line 155, in __init__
ValueError: ('Firmware for Shield2 out of date', 15)
```
**Как да ъпдейтнем:**
Въпреки, че има официален урок как да направите това, може да следвате и [този](https://core-electronics.com.au/tutorials/pycom-pysense-pytrack-firmware-update.html).

---

Тъй като използваме PyBytes за конфигурация, `boot.py` файла може да остане празен, модула ще вземе настройки за мрежа към която да се свърже от проекта в pyBYtes.

### Accelerometer sensor
Three-axis linear accelerometer. https://www.st.com/en/mems-and-sensors/lis2hh12.html

#### Roll mode

**<p style="text-align: center;"> <img src="https://lastminuteengineers.b-cdn.net/wp-content/uploads/arduino/MPU6050-Accel-Gyro-Working-Roll-Mode-Output.gif" style="zoom: 100%;" /> </p>** **<p style="text-align: center;"></p>**

#### Pitch mode

**<p style="text-align: center;"> <img src="https://lastminuteengineers.b-cdn.net/wp-content/uploads/arduino/MPU6050-Accel-Gyro-Working-Pitch-Mode-Output.gif" style="zoom: 100%;" /> </p>** **<p style="text-align: center;">**

#### Acceleration measurement


http://web.uni-plovdiv.bg/marudova/Mechanics/tvardo_tyalo.pdf

https://en.wikipedia.org/wiki/Coriolis_force

https://lastminuteengineers.com/mpu6050-accel-gyro-arduino-tutorial/

https://www.nationalgeographic.org/encyclopedia/coriolis-effect/