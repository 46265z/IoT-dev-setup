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

## Свързване към MQTT

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

В `main.py` ще пишем кода който отговаря за свързването към брокера и изпращане и получване на съобщения:

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

https://user-images.githubusercontent.com/47386361/148644229-dc6f1e57-f83b-4bf8-90c8-7812dd4278bc.mp4

## Интегриране с услуги предоставени от трети страни

 <!--
## LoPy +

Ще разгледаме използването й с няколко различни разширителни платки.


### Expansion Board

### PySense2x

### PyScan

### PyTrack2x
-->
