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

_Снимка, а най-добре гиф който да показва как_


#### Софтуер
Трябва да имате инсталиран VSCode и екстеншъна Pymakr. Вижте как [тук](https://docs.pycom.io/gettingstarted/software/vscode/)



### Програмиране на модула
За начало ще използваме Python REPL-а за да изпълним няколко команди. След като сме свързали платката към PC, пуснете Putty и установете серийна връзка към съответния COM порт. Ако не виждате `>>>` просто цъкнете Enter веднъж.




## Работа с у-вото през PyBytes


## LoPy +

Ще разгледаме използването й с няколко различни разширителни платки.


### Expansion Board

### PySense2x

### PyScan

### PyTrack2x
