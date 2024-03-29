# LoPy<sup>4</sup>

LoPy<sup>4</sup> е програмируема платка поддържаща 4 различни вида мрежи за пренос на данни. Работи с LoRa, Sigfox, WiFi и Bluetooth __(BLE?)__. Поради това тя е особено подходяща за IoT проекти от висок клас (enterprise-grade). Програмира се с MicroPython.

[Product page](https://docs.pycom.io/datasheets/development/lopy4/)
[Datasheet](https://docs.pycom.io/gitbook/assets/specsheets/Pycom_002_Specsheets_LoPy4_v2.pdf)
[Pinout](https://docs.pycom.io/gitbook/assets/lopy4-pinout.pdf)


![lopy4-resized-removebg-preview](https://user-images.githubusercontent.com/47386361/148212731-c2cac252-3958-4a18-be67-c3dd899a0563.png)


---

!!! type danger "Когато използвате безжична връзка LoRa или Sigfox, винаги поставяйте подходяща антена!"

!!! type info "При използване на WiFi или Bluetooth използването на външна антена не е задължително, освен когато изрично посочим това в кода."


## Работа с у-вото през USB
Ако не разполагаме с разширителна платка е възможно да достъпим модула чрез USB-Serial конвертор ([вижте как](https://docs.pycom.io/gettingstarted/programming/usbserial/)).

### Нужни
<!-- - [Atom](https://atom.io/) -->
 - Putty
 - Visual Studio Code
 - Pymakr VSCode Extension
 - Прочете [официалния урок](https://docs.pycom.io/gettingstarted/software/) за настройване на работна среда
 - LoPy<sup>4</sup>
 - Expansion Board
 - USB кабел тип Micro-B



### Подготовка
Преди да започнем да програмиране модула, трябва да подготвим средата за работа и хардуера с който ще работим.


#### Хардуер
Свързваме модула към разширителната платка (в случая ще използваме Expansion Board 3.0), като LED на модула трябва да застане над USB буксата на разширителнат.
След това просто включваме USB кабела към PC.
!!! type info "Когато включите модула, вграденият светодиод мига на равни интервали в синьо. Този "сърдечен ритъм" (heartbeat) се използва като начин да се разбере, че модулът е заредил и е стартирал правилно."

_Снимка, а най-добре гиф който да показва как_


#### Софтуер
Трябва да имате инсталиран VSCode и екстеншъна Pymakr. Вижте как [тук](https://docs.pycom.io/gettingstarted/software/vscode/)


### Програмиране на модула
За начало ще използваме Python REPL-а за да изпълним няколко команди. След като сме свързали платката към PC, пуснете Putty и установете серийна връзка към съответния COM порт. Ако не виждате `>>>` просто цъкнете Enter веднъж.

Командите които ще изпълним са следните
```python
import pycom
pycom.heartbeat(False)
pycom.rgbled(0x330033)
```
![lopy4-putty-repl](https://user-images.githubusercontent.com/47386361/148545282-01135d1a-98c3-450b-81ce-91fdf0ba3b6e.png)

В резултат, LED на у-вото трябва да светне в лилав цвят.

Същото можем да постигнем изплзвайки REPL-a който ще намерим във VSCode.

![lopy4-vscode-repl](https://user-images.githubusercontent.com/47386361/148545302-0a86f1ae-b157-45eb-813b-990d08dff201.png)

---
За да бъде работата с устройството по-приятна, а разбира се и по-продуктивна, **трябва** да използваме разширението за VSCode - Pymakr. То позволява да направим проект представен от директория, в която има конфигурационен файл за серийната връзка и кода който искаме да има на устройството. Освен това, чрез него можем да качим целия си проект чрез цъкване на 1 единствен бутон, ако се чудите как става в противен случай провете в интернет ("ръчното" качване на код е времеотнемащ процес).

#### Създаване на MicroPython проект с Pymakr
Обикновено един такъв проект съдържа поддиректория `lib` която съдържа допълнителни библиотеки написани от нас или от някой друг и два `.py` файла - `boot.py`и `main.py`. Както името подсказва, първият се изпълянва в момента в който платката бъде пусната, а `main.py` файла е мястото къде се изпълнява основния код.

Стъпките при създаване на проект са следните:

1. Създаваме нова директория. Моята се казва RGBLED-Blink. Това е главната директория на проекта.

2. В нея създайте папка `lib`, може да бъде празна.

3. Създйате създайте двата `.py` файла.

4. Отворете главната директория във VSCode.

Задачата която ще осъществим чрез този проект е да контролираме вградения LED.

Кодът за този пример ще пишем в `main.py`:

```python
import pycom
import time
```

`Pycom` библиотеката отговаря за специфични за тези у-ва възможности. Начина по който контролираме вградения LED е една от тях. Библиотеката `time` е стандартната за `Python` - отговаря за тайминга и времеви забавяния (timing and delays).

!!! type info "Преди да променяме цвета на светодиода трябва да изключим heartbeat-а."

```python
pycom.heartbeat(False)
```

Нека тестваме кода който написахме до тук. В най-долната синя лента на VSCode има бутон `Run`, както и бутон `Upload`, ще използваме бутона `run`. Разликата е в това, че `run` компилира кода и го изпълнява на у-вото **без да го запазва** във flash паметта, докато `upload` го запазва (качва го на у-вото).

_Снимка lopy-vscode-run-upload_

След като цъкнем `run` "сърдечния ритъм" на устройството ще спре.

Нека довършим скрипта като `while` loop в който променяме цвета на светодиода. Следва цялостния код за примера:

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

За да спрете изпълнението на скрипта, фокусирайте терминала и натиснете `Ctrl+C`.

Ако рестартирате у-вото от бутона му, ще видите, че "сърдечния ритъм" отново е на лице, а цветовете които зададохме ние ги няма.
За да променим това трябва просто да използваме бутона `upload`. След това дори след рестарт кода ще е в устройството и ще бъде изпълнен.

_Snimka lopy-vscode-upload-cpde_

## Работа с у-вото през PyBytes

### Нужни
- LoPy<sup>4</sup>
- Expansion Board
- USB кабел тип Micro-B
- Регистрация в [PyBytes](https://pybytes.pycom.io/)
- 2.4GHz безжична мрежа (препоръчително е да не е основната която използвате, тъй като паролата е видима в някои моменти)
- [PyCom Firmware Update Tool](https://pycom.io/downloads/#firmware)

Аналогично на проекта който създадохме локално във VSCode, ще създадем проект в PyBytes.

### Стъпки за създаване на проект

- В уеб интерфейса конфигурираме безжичната мрежа към която у-вото ще бъде свързвано.
- Добавяме(създаваме) у-во към (в) PyBytes.
	- Избираме метод за активация. Най-често аз избирам offline activation.
- Отново от уеб интерфейса избираме **Create project**. Посочете мрежата която конфигурирахте по-рано.
- Добавяме у-вото към проекта.

![pybytes-add-device-create-project-how-to](https://user-images.githubusercontent.com/47386361/148545380-95a8a684-5bcc-4973-ad75-e027665d7f4f.gif)


От сега нататък можем да променяме конфигурацията на у-вото, да качваме нов код както и да обновяваме фирмуера изцяло Over-The-Air.


## Безжична свързаност

В почти всеки случай кода за свързване към мрежата трябва да бъде в `boot.py`.


### Access point mode

### Station mode

### Сканиране и свъзване към мрежа
В `boot.py`:

```python
from network import WLAN
import machine
wlan = WLAN(mode=WLAN.STA)

nets = wlan.scan()
for net in nets:
    if net.ssid == '<Your-Wifi-SSID>': # <Your-Wifi-SSID> е името на вашата мрежа
        print('[INFO]\tNetwork found!')
        wlan.connect(net.ssid, auth=(net.sec, '<yourWifiKey>'), timeout=5000) # <yourWifiKey> Трябва да бъде паролата за вашата мрежа
        while not wlan.isconnected():
            machine.idle() # save power while waiting
        print('[INFO]\tWLAN connection succeeded!')
        break
    else:
        print('[WARNING]\tThe network you are searching for could not be found.')
		break
```

Резултата наблюдаван в `Pymakr Console` във `VSCode`:

![lopy-scan-and-connect-to-network](https://user-images.githubusercontent.com/47386361/148642807-7c33d6cf-94c8-4fe0-a501-6e4e0eafa303.png)

Импортваме нужните библиотеки
```python
from network import WLAN
import machine
```

Инстанциираме класа `WLAN` в режим на клиент
```python
wlan = WLAN(mode=WLAN.STA)
```

Сканираме наличните мрежи и запазваме резултата от сканирането в `list`
```python
nets = wlan.scan()
```

За всяка от намерените мрежи извършваме проверка търсейки мрежа със `SSID` което ни интересува.
Ако мрежата е налична принтим информационно съобщение за това и инициализираме свързване към нея.

```python
for net in nets:
    if net.ssid == '<Your-Wifi-SSID>': # <Your-Wifi-SSID> е името на вашата мрежа
        print('[INFO]\tNetwork found!')
        wlan.connect(net.ssid, auth=(net.sec, '<yourWifiKey>'), timeout=5000) # <yourWifiKey> Трябва да бъде паролата за вашата мрежа
```

Проверяваме състоянието, като докато НЕ е свързвано задаваме състояние на процесора `idle` за да пестим енергия. При успешно свързване принтим `[INFO]` съобщение и излизаме от проверката.
```python
        while not wlan.isconnected():
            machine.idle() # save power while waiting
        print('[INFO]\tWLAN connection succeeded!')
        break
```

Ако мрежата не е открита се отразява в терминала чрез съобщение от тип `[WARNING]`.
```python
    else:
        print('[WARNING]\tThe network you are searching for could not be found.')
		break
```

Понеже използвам вторична мрежа за у-вата, ще мога да видя устройство в интерфейса на рутера свързано към `Wireless interface - wlan2`.

![snimka-ot-WinBox-na-ustroistvoto-svurzano-kym-mrejata](https://user-images.githubusercontent.com/47386361/148642817-ce43a035-9f76-4e0e-b550-ebaaf598c61b.png)

### Задаване на статичен IP адрес
Ако искате да достъпвате у-вото чрез някакъв отдалечен достъп различен от pyBytes, ще е по-лесно да има статично ИП.

!!! type danger "Обърнете внимание как проверяваме причината за рестартиране и състоянието на връзката - това е от решаващо значение, за да можем да рестартираме LoPy програмно по време на Telnet сесия, без да прекъсваме връзката."

В `boot.py`:
```python
import machine
import time
from network import WLAN

wlan = WLAN() # get current object, without changing the mode
if machine.reset_cause() != machine.SOFT_RESET:
    wlan.init(mode=WLAN.STA)
    # configuration below MUST match your home router settings!!
    wlan.ifconfig(config=('192.168.88.250', '255.255.255.0', '192.168.88.1', '192.168.88.1')) # (ip, subnet_mask, gateway, DNS_server)

if not wlan.isconnected():
    # change the line below to match your network ssid, security and password
    wlan.connect('IoT-dev-env', auth=(WLAN.WPA2, '12345678'), timeout=5000)
    print("[INFO]\tconnecting",end='')
    while not wlan.isconnected():
        time.sleep(1)
        print(".",end='')
    print()
    print("[INFO]\tconnected")

```

Резултата наблюдаван в `Pymakr Console` във `VSCode`:

![upload-static-up-result](https://user-images.githubusercontent.com/47386361/148642828-dc091feb-0a09-498b-b0e9-ec34f1e59d58.png)

Ping резултат:

![PING_RESULT-upload-static-up-result](https://user-images.githubusercontent.com/47386361/148642833-774abf37-a222-491c-ac0f-6701d540c56e.png)

## Изпращане на данни към PyBytes
!!! type info "Устройстовто трябва да бъде активирано в платформата."
!!! type info "Трябва да дефинирате канала на който очаквате данни, тоест отидете в уеб интерфейса и отворете у-вото, в секция Signals -> дефинирайте."
Тъй като за това отново се използва MQTT логиката е същата, но методите в кода са различни.

В този пример ще изпращаме данни към PyBytes на всеки 5 секунди, тъй като все още използваме Expansion board-a, ще изпращаме синтетични данни.
В следващи примери когато използваме някоя от сензорните разширителни платки ще изпратим реални данни.


`boot.py`:
Свързваме се към мрежата.

В `main.py`:
```python
# Import what is necessary to create a thread
import time
import math

# Send data continuously to Pybytes
while True:
    for i in range(0,20):
        pybytes.send_signal(1, math.sin(i/10*math.pi))
        print('sent signal {}'.format(i))
        time.sleep(10)
```

Импортваме нужните библиотеки, Ще използваме няколко метода от `math` за да синтезираме данни.
```python
import time
import math
```

Продължително изпращаме данни към PyBytes на канал 1, съдържанието се пресмята всеки път.
```python
# Send data continuously to Pybytes
while True:
    for i in range(0,20):
		# Това е реда който изпраща данните към платформата	
        pybytes.send_signal(1, math.sin(i/10*math.pi))
        print('sent signal {}'.format(i))
        time.sleep(10)
```

Резултат:

<iframe width="600" height="315"
  src="https://user-images.githubusercontent.com/47386361/148675867-a5665c5b-57ab-4841-b71e-44748cbe0d5f.mp4">
</iframe>

## Свързване към MQTT

!!! type info "При този пример у-вото НЕ е активирано в платформата на PyBytes, тоест при флашване с Pycom Firmware update tool опцията Force pybytes activation и SmartConfig НЕ са отметнати"

Сваляме сорс кода на MQTT клиента от [тук](https://github.com/pycom/pycom-libraries/blob/master/lib/mqtt/mqtt.py). Запазваме го в директория `lib` на проекта.

`boot.py` ще съдържа кода за свързване с мрежата:
Това е кода от първия пример.

```python
from network import WLAN
import machine
wlan = WLAN(mode=WLAN.STA)

nets = wlan.scan()
for net in nets:
    if net.ssid == 'IoT-dev-env': # <Your-Wifi-SSID> е името на вашата мрежа
        print('[INFO]\tNetwork found!')
        wlan.connect(net.ssid, auth=(net.sec, '12345678'), timeout=5000) # <yourWifiKey> Трябва да бъде паролата за вашата мрежа
        while not wlan.isconnected():
            machine.idle() # save power while waiting
        print('[INFO]\tWLAN connection succeeded!')
        break
    else:
        print('[WARNING]\tThe network you are searching for could not be found.')
		break
```

В `main.py` ще пишем кода който отговаря за свързването към брокера и изпращане и получване на съобщения. Коментари в кода:


```python
from mqtt import MQTTClient # this will be found in /lib directory

import time

def sub_cb(topic, msg):
    """
    This function is executed everytime a new message
    arrives on the topic we have subscribed to.
    It prints the topic and the content of the message.
    """
    print("New message arrived in topic ",topic," with content ", msg, end ='')
    print()

# Create an instnace of the client, assigning the required
# credentials for connecting to the broker. With flespi,
# the password can be empty and the token is entered in
# the username field.
client = MQTTClient("DeviceID-LoPy4", "mqtt.flespi.io",user="<YourFlespiToken>",password="",port=1883)

# Register the callback function
client.set_callback(sub_cb)

# connect to the broker
client.connect()

# subcribe to the topic we want to listen for new messages
client.subscribe(topic="lopy4/test")

while True:
    print("Sending message to the broker")
    # Publish a message to the broker and all clients listening on this topic
    client.publish(topic="lopy4/test", msg="Hi from lopy4")
    # sleep for 1 ms
    time.sleep(1)
    # Check for new messages, if there are any the callback function will be executed.
    client.check_msg()

    # sleep again for a milisecond
    time.sleep(10)
```

Видео на резултата:

<iframe width="600" height="315"
  src="https://user-images.githubusercontent.com/47386361/148644229-dc6f1e57-f83b-4bf8-90c8-7812dd4278bc.mp4">
</iframe>

## PyBytes + third party MQTT Broker
!!! type info "За да бъдем свързани към PyBytes и да можем да изпращаме данни към платформата, у-вото трябва да е активирано по съответния начин"

Тъй като Pybytes също използва MQTT, ако искаме да използваме отделна MQTT връзка докато същевременно сме във връзка с Pybytes, ще трябва да преименуваме класа MQTTCLient във файла mqtt.py, на (например) клас MQTTClient_lib, и да импортнем, като използваме новото име на класа (_from X import Z as Y_), за да избегнем конфликт на имената на класовете.

`boot.py`:
Свързваме се към мрежата.

В `main.py`:
```python
from mqtt import MQTTClient_lib as MQTTClient # this will be found in /lib directory
import math
import time

# Create an instnace of the client, assigning the required
# credentials for connecting to the broker. With flespi,
# the password can be empty and the token is entered in
# the username field.
client = MQTTClient("DeviceID-LoPy4", "mqtt.flespi.io",user="<YourFlespiToken>",password="",port=1883)

# connect to the broker
client.connect()

while True:
    for i in range(0,20):
        print("Generating synthetic data")
        synth_data = math.sin(i/10*math.pi)

        print("Sending message to MQTT broker")

        # Publish a message to the broker and all clients listening on this topic
        client.publish(topic="lopy4/test", msg=str(synth_data))

        # Seng signal to PyBytes on channel 1 with the same data
        pybytes.send_signal(1, synth_data)

        # sleep for 1 ms
        time.sleep(1)

        # sleep for 10 miliseconds before iterating again
        time.sleep(10)

```

Резултатът наблюдаван и в двете платформи:

<iframe width="600" height="315"
  src="https://user-images.githubusercontent.com/47386361/148676811-8f9f1f17-218b-493d-9e79-0caa5dcceece.mp4">
</iframe>

## Приемане на данни в Python скрипта

Ще напишем Python скрипт който ще слуша на посочените теми и ще обработва получените данни.
Ще използваме имплементацията [gmqtt](https://github.com/wialon/gmqtt). Предимството е, че е асинхронна по природа което олеснява работата.

Създаваме виртуална Python среда и инсталираме gmqtt с pip. Аз работя с python версия 3.8.9, не би трябвало да има проблем с по-нови версии.

В MS Win 10 powershell:

Създаване на python virtual environment:

`python -m venv .venv`

Активиране на средата:

`.\.venv\Scripts\Activate.ps1`

Инсталиране на нужните библиотеки:

`python -m pip install gmqtt asyncio`


Код:
```python
import asyncio
import os
import signal
import time

from gmqtt import Client as MQTTClient

# gmqtt also compatibility with uvloop  
# import uvloop
# asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())


STOP = asyncio.Event()


def on_connect(client, flags, rc, properties):
    print('Connected')
    client.subscribe('lopy4/test', qos=0)


def on_message(client, topic, payload, qos, properties):
    print('RECV MSG:', payload)


def on_disconnect(client, packet, exc=None):
    print('Disconnected')

def on_subscribe(client, mid, qos, properties):
    print('SUBSCRIBED')

def ask_exit(*args):
    STOP.set()

async def main(broker_host, port, token):
    client = MQTTClient("client-id")

    client.on_connect = on_connect
    client.on_message = on_message
    client.on_disconnect = on_disconnect
    client.on_subscribe = on_subscribe

    client.set_auth_credentials(token, None)
    await client.connect(broker_host)

    client.publish('TEST/TIME', str(time.time()), qos=0)

    await STOP.wait()
    await client.disconnect()


if __name__ == '__main__':
    loop = asyncio.get_event_loop()

    broker_host = 'mqtt.flespi.io'
    port = 1883
    token = "<YourFlespiToken>"
    try:
        loop.run_until_complete(main(broker_host, port, token))
    except KeyboardInterrupt:
        print("Received exit, exiting")
```

Обеснение:

Импортваме нужните библиотеки:
```python
import asyncio
import os
import signal
import time

from gmqtt import Client as MQTTClient
```

Дефинираме event handler за да можем да спрем всички изпълнявани задачи и да излезем правилно:
```python
STOP = asyncio.Event()
```

Дефинираме функции за четирите основни момента - on_connect, on_disconnect, on_subscribe, on_message:

Функцията се изпълнява в момента в който клиента ни е свързван към брокера. Тук е мястото да се абонираме към темата на която слушаме за данни:
```python
def on_connect(client, flags, rc, properties):
    print('Connected')
    client.subscribe('lopy4/test', qos=0)
```

Изпълнява се всеки път когато съобщение е получено. Ако не сме абонирани към правилната тема никога няма да се изпълни:

```python
def on_message(client, topic, payload, qos, properties):
    print('RECV MSG:', payload)
```

Изпълнява се в момента в който клиенти ни изгуби връзка с брокера. Тук може да се имплементира логика за last_will функционалност и т.н.:
```python
def on_disconnect(client, packet, exc=None):
    print('Disconnected')
```

изпълнява се в момента в който се абонираме към тема. За момента приложението е основно за дебъг и прегледност:
```python
def on_subscribe(client, mid, qos, properties):
    print('SUBSCRIBED')
```

Дефинираме функция чрез която да кажем на loop-a да "убие" всички процеси. Изпълнява се при `Ctrl+C`:
```python
def ask_exit(*args):
    STOP.set()
```

Основната функция на скрипта. Тук създаваме инстанция на своя MQTT клиент. Регистрираме функциите. Задаваме параметрите нужни за автентификация към брокера. Изпълняваме функциите за спиране на скрипта асинхронно, тоест без да блокират изпълнението на останалата част от кода.
```python
async def main(broker_host, port, token):
    client = MQTTClient("client-id")

    client.on_connect = on_connect
    client.on_message = on_message
    client.on_disconnect = on_disconnect
    client.on_subscribe = on_subscribe

    client.set_auth_credentials(token, None)
    await client.connect(broker_host)

    client.publish('TEST/TIME', str(time.time()), qos=0)

    await STOP.wait()
    await client.disconnect()
```

Данни за MQTT брокера.
Пускаме `loop`-а.
Когато натиснем `Ctrl+C` ще се изпълни `except KeyboardInterrupt` блока и съответно функцията `ask_exit()`
```python
if __name__ == '__main__':
    loop = asyncio.get_event_loop()

    broker_host = 'mqtt.flespi.io'
    port = 1883
    token = "<YourFlespiToken>"
    try:
        loop.run_until_complete(main(broker_host, port, token))
    except KeyboardInterrupt:
        print("Received exit, exiting")
```

### Препращане на данни към БД
Работим върху кода от предишния пример.

#### MongoDB Cloud
В същата виртуална среда на Python която използвхаме в предишната точка трябва да инсталираме изискванията за работа с MongoDB.

`python -m pip install dnspython pymongo` 

В скрипта импортваме `pymongo` и `datetime` за да добавим timestamp към записа:
```python
...
import pymongo
import datetime
```

Запазваме в променливи данните за автентификация към БД.
```python
if __name__ == '__main__':
	DBUSER = "<YourDBUsername>"
	DBPWD = "<YourDBUserPassword>"
```


Инстанциираме обект от класа `MongoClient`, като подаваме `connection string`-а форматирам с парола и потребител.
```python
	# To create instance of the mongo client we need a connection string.
	# Then we pass the connection string formatted with our user credentials as below:
    db_client = pymongo.MongoClient(f'mongodb+srv://{DBUSER}:{DBPWD}@clusterdubnika16.ijloo.mongodb.net/iotDemo?retryWrites=true&w=majority')
	db = db_client.iotDemo	# cursor to our DB
    collection = db.pycomPython # cursor to the collection
	...
```

Логиката за препращане на данни ще имплементираме във функцията `on_message`. Обърнете внимание, че вече е дефинирана с ключовата дума `async`.
В `recvTime` запазваме дата и час от момента на получване на съобщението.
```python
async def on_message(client, topic, payload, qos, properties):
    print('RECV MSG:', payload)
    recvTime = datetime.datetime.now()
```

Създаваме променлива от тип `dict` в която ще запазим `timestamp` и получения `payload` от MQTT съобщението. Тъй като данни получени от MQTT винаги са `binary` трябва да ги преобразуваме преди да ги запазим. Аз ще ги запазя като стринг.
```python
    str_payload = str(payload)
    data = {
        "recvTime": recvTime,
        "payload":str_payload
    }
```

![mongo-records-beforeAfter-string-conv](https://user-images.githubusercontent.com/47386361/148731765-14559381-2fe0-47f4-83ba-0bf9b351d72d.png)

За да запазим в БД използваме курсора към колекцията в баазата данни, тоест `collection` и по-точно `collection.insert_one()`.
```python
	collection.insert_one(data)
```

Крайния код е това:
```python
import asyncio
import os
import signal
import time
from gmqtt import Client as MQTTClient
import pymongo
import datetime

# gmqtt also compatibility with uvloop  
# import uvloop
# asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())


STOP = asyncio.Event()


def on_connect(client, flags, rc, properties):
    print('Connected')
    client.subscribe('lopy4/test', qos=0)


# def on_message(client, topic, payload, qos, properties):

#     print('RECV MSG:', payload)

async def on_message(client, topic, payload, qos, properties):
    print('RECV MSG:', payload)
    recvTime = datetime.datetime.now()
    str_payload = str(payload)
    data = {
        "recvTime": recvTime,
        "payload":str_payload
    }
    collection.insert_one(data)

def on_disconnect(client, packet, exc=None):
    print('Disconnected')

def on_subscribe(client, mid, qos, properties):
    print('SUBSCRIBED')

def ask_exit(*args):
    STOP.set()

async def main(broker_host, port, token):
    
    client = MQTTClient("client-id")

    client.on_connect = on_connect
    client.on_message = on_message
    client.on_disconnect = on_disconnect
    client.on_subscribe = on_subscribe

    client.set_auth_credentials(token, None)
    await client.connect(broker_host)

    client.publish('TEST/TIME', str(time.time()), qos=0)

    await STOP.wait()
    await client.disconnect()


if __name__ == '__main__':
    DBUSER = "<YourDBUsername>"
    DBPWD = "<YourDBUserPassword>"
    # To create instance of the mongo client we need a connection string.
    # Then we pass the connection string formatted with our user credentials as below:
    db_client = pymongo.MongoClient(f'mongodb+srv://{DBUSER}:{DBPWD}@clusterdubnika16.ijloo.mongodb.net/iotDemo?retryWrites=true&w=majority')
    db = db_client.iotDemo	# cursor to our DB
    collection = db.pycomPython # cursor to the collection
    
    loop = asyncio.get_event_loop()
    broker_host = 'mqtt.flespi.io'
    port = 1883
    token = "<YourFlespiToken>"
    try:
        loop.run_until_complete(main(broker_host, port, token))
    except KeyboardInterrupt:
        print("Received exit, exiting")
```

## Интегриране с услуги предоставени от трети страни

 <!--
## LoPy +

Ще разгледаме използването й с няколко различни разширителни платки.


### Expansion Board

### PySense2x

### PyScan

### PyTrack2x
-->
