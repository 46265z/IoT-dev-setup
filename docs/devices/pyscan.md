# Pyscan

Pyscan е сензорен разширител, който можем да използваме с всякакви многомрежови платки за разработка (на Pycom). С акселерометър, сензор за светлина и RFID-NFC.

[Product page](https://docs.pycom.io/datasheets/expansionboards/pyscan/)
[Datasheet & Pinout](https://docs.pycom.io/gitbook/assets/pyscan-pinout.pdf)

![](https://pycom.io/wp-content/uploads/2020/03/Website-Product-Shots-Pyscan-front.png)

---

Ще изпратим данните от сензорната платка към pyBytes и към flespi<sub>[[1]](http://localhost:8000/IoT-dev-setup/devices/lopy4/#pybytes-third-party-mqtt-broker)</sub> и ще запазим данните в MongoDB<sub>[[2]](http://localhost:8000/IoT-dev-setup/devices/lopy4/#python)</sub>. Ще използваме модула LoPy<sup>4</sup>



<!-- !!! type danger "Преди да преместите LoPy модула върху PyScan, използвайте PyCom Firmware Update Tool-a за да форматирате паметта, без да активирате у-вото." -->

!!! type danger "Когато преместите LoPy модула върху PyScan, трябва да създадем и активираме у-вото отново като посочим, че използваме PyScan."

## Нужни

За работя със сензорния разширител ни трябват съответните библиотеки за:

- Основната библиотека за разширителната платка - https://github.com/pycom/pycom-libraries/blob/master/shields/pyscan_1.py
- [RFID/NFC reader](https://github.com/pycom/pycom-libraries/blob/master/shields/lib/MFRC630.py)
- [accelerometer](https://github.com/pycom/pycom-libraries/blob/master/shields/lib/LIS2HH12.py)
- [ambient light sensor](https://github.com/pycom/pycom-libraries/blob/master/shields/lib/LTR329ALS01.py)
- MQTT с променено име на класа

## Програмиране на модула
Тъй като използваме PyBytes за конфигурация, `boot.py` файла може да остане празен, модула ще вземе настройки за мрежа към която да се свърже от проекта в pyBYtes.

!!! type danger "При използване на две отделни MQTT връзки (както в случай), ако не осигурите достатъчно време между изпращанията се получава bottleneck и съответно загуба на данни."

### Сканиране на RFID/NFC карта
Не разполагам с подходящ тип карта.

### Сензор за ускорение
**LIS2HH12**

```python
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
```

Наблюдение на работата от 3 страни: терминал, PyBytes и flespi. Следващото видео наблюдава случай в който НЕ сме осигурили достатъчно време между действията. Обърнете внимание на данните във всеки прозорец в един момент - не са еднакви, дори се разминават с няколко съобщения.

_Video bottleneck_

Видео на правилна операция на у-вото:

_Video without bottleneck_
