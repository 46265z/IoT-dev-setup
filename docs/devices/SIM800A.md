# sim800a

[Product page](#) - Unknown
[Datasheet](#) - Unknown
[Pinout](#) - On board

<img src="https://user-images.githubusercontent.com/47386361/144780422-82cb579c-5db2-4714-8708-d06365506a59.png" width="300" height="300" />

Като цяло работата с GSM модул и ардуино е сравнително лесна, освен тогава когато не е...

На пазара има няколко разновидности модеми (TODO>списък), но по-интересен е броя на различните дизайни (PCB Designs) които се предлагат от различните производители (които също са безброи). Това което имам впредвид е, че два продукта базирани на един и същ модем (например SIM800), и именувани по сходен начин, са до-голяма степен различни в съшността си. (съответно и начина по който можем да ги използваме. )

Тези различия често са достатъчно осезаеми и напълно достатъчни, че да провалят проекта ни, в случай, че не знаем за тях и не ги предвидим в първоначалното планиране на цялостната работа. 

_Следващите редове се базират изцяло на наблюденията ми през последните три години на работа с различни "IoT" устройства (2018-2021)._

Въпросните различния се дължат на това, че: първо - различните производители имплементират (задължителната) периферията на модема по (достатъчно) различен начин, че това да промени крайното(по-нататъшЧното!?!?!?) действеи и/или начин на работа на/със въпросния продукт (за нас-девелопърите), второ - често биват добавяни различни функционалности към крайния (за developer-а е междинен...) продукт, които не са предвидени по начало в основния такъв (в случея това е GSM модема). Най-вероятно си мислите "какво от това? нали това е смисъла на развоините платки, пък и преди да излязат на пазара минават регулационен процес от съответните органи"...; трето-прекалено често крайният продукт съдържа критични грешки в дизайна на схемата (напр. LED в esp8266 платки), съответно и в начина на работа след това и четвърто, но не на последно място - много често липсва каквато и да е документация на продукта (било то схема на I/O или описание на наличните функционалности за следващия разработчик)

Модемът с който ще работим е един от най-известните _(най-често срещаните)_ - SIM800 и по-точно SIM800**A**, а модула (до колкото е възможно да бъде идентифициран) е по дизайн на ___UNV___, конкретно този с който разполагаме е версия _V3.9.3_ от _26-08-2016г._ (предполагам, че годината се отнася към версията, а не дата на производство)

_значението на буквата в края (как се нарича?индекс може би?), и какви други възможности има, ще разгледаме по-късно._

Предстой да разгледаме основни

## Тестване на модула

### Нужни
- USB Type Mini B
- SIM Card with atleast GPRS data
- Few jumper wires
- [Putty](https://www.putty.org/)
- КОНВЕРТОР USB КЪМ UART ![converter-USB-to-UART](https://user-images.githubusercontent.com/47386361/146177393-e995ac82-2ae3-4912-b944-fa8ea13aa371.jpg)

### Свързване
<!-- GSM_USB-UART_diag -->
![GSM_USB-UART_Annotation 2021-12-21](https://user-images.githubusercontent.com/47386361/146909729-1523e3e4-3776-4f60-8d5f-b5b8216aac3f.jpg)


![PINS-USED-ON-CONVERTER](https://user-images.githubusercontent.com/47386361/146182349-fcba18c2-f08c-4967-9919-4674dd1d6b3a.jpg)
![module-connected-to-converter](https://user-images.githubusercontent.com/47386361/146182940-eb4e954b-2b2c-40dc-9e7b-4c6545c84c8f.jpg)

След като модулът е свързан чрез конвертора към компютъра, сме готови да тестваме изправността и функционалността му. За целта отваряме _Device Manager_ и проверяваме номера на COM порта. За връзка ще използваме програмата [_Putty_](https://www.putty.org/)

![Putty-Settings-Annotation_2021-12-15](https://user-images.githubusercontent.com/47386361/146184473-a916e925-aed0-4294-acb4-f30314959751.jpg)

Натискаме _Open_. Трябва да изчакаме няколко секунди докато се осъществи връзка към модула. Разбираме, че връзката е осъществена когато въведем някакъв символ и той се визуализира в командния ред.

### Основни АТ команди за тестване на изправността и функционалността.
В таблицата са събрани основните команди чрез които ще съберем основна информация за версията на фирмуера на устройството и други.

| Команда       | Използва се за                                   |
| ------------- | -------------                                    |
| AT            | handshake test                                   |
| AT+CSQ        | Signal Quality                                   |
| AT+CCID       | Read SIM Information to confirm its plugged in   |
| AT+CREG?      | Check if SIM is registered in the network        |


AT - Това е най-основната AT команда. Тя също така инициализира Auto-baudrate. Ако тя работи, трябва да видите ехото на AT символите и след това OK, което ви казва, че всичко е наред и тя ви разбира правилно! След това можете да изпратите някои команди за запитване към модула и да получите информация за него, като например:

AT+CSQ - Проверете "силата на сигнала" - първото # е силата на сигнала в dB, тя трябва да е по-висока от около 5. По-високата стойност е по-добра. Разбира се, това зависи от вашата антена и местоположение.

AT+CCID - получаване на номера на SIM картата - с тази функция се проверява дали SIM картата е поставена правилно и можете да проверите дали номерът е записан на картата.

AT+CREG? Проверява дали сте регистрирани в мрежата. Вторият # трябва да бъде 1 или 5. 1 означава, че сте регистрирани в домашната мрежа, а 5 - че сте регистрирани в роуминг мрежа. Другите две числа освен тези показват, че не сте регистрирани в никаква мрежа.

![AT-TEST-CMDS-OUTPUT_Annotation_2021-12-15](https://user-images.githubusercontent.com/47386361/146188066-714ddc22-0345-4632-9e69-a648af2e75ad.jpg)

## Интегриране на модула към IoT контролер
Тоест ще използваме GSM модула за да контролираме _I/O_ на _Arduino UNO_ например.

### Нужни
- Всичко от предишната точка.
- Arduino UNO, може и клонинг. ( не забравяйте да дарите някой лев в този случай :) )
- Още няколко джъмпера.
- Нисковолтово реле.

![niskovoltovo-rele-modul](https://user-images.githubusercontent.com/47386361/146189513-ca78a609-9cf1-436e-932c-abe0b637f3af.jpg)

### 1. Изпращане на комнди от Arduino
За начало ще изпълним тестовите АТ команди, които коментирахме по-горе, но ще ги изпратим от Ардуино към модула. Освен, че ще изпратим командите искаме и да прочетем отговора на модула, които да се изпише в серийния монитор на _Arduino IDE_.

#### Стъпка 1
Качваме следния код на _Arduino UNO_.
```C++
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800A
SoftwareSerial mySerial(3, 2); //SIM800A Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800А
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
```

Към момента можете да пуснете сериен монитор, но това което ще видите е просто ред който гласи `Initializing . . . ` и нищо повече. Трябва да свържем контролера към модула и релето.

#### Стъпка 2
**Свързване на GSM Модула към Arduino UNO**
!!! type danger "Преди да започнете да свързвате каквото и да е, моля изключете всичко от захранването."
	Пазете компонентите си! Въпреки, че цената им е сравнително ниска, няма нужда да разхищаваме ресурси.

Дали можем да захранваме модула от ардуиното е спорен въпрос, който се обсъжда из форумите в интернет от години и няма ясен отговор. Според документацията на компонентите - НЕ! Според практиката - да ..
Това което ще направим ние е да свържем модула директно към контролера, при мен няма никакви проблеми ползвайки го по този начин, постъпете по ваше усмотрение. Другият вариянт (който е и по-добрия, в случай, че имате възможност - направете го) е да осигурим отделно захранване за GSM модула и контролера.

Следва ASCII диаграма на свързването между двата компонента.

![ASCII-GSM-Arduino_Annotation_2021-12-15](https://user-images.githubusercontent.com/76831786/146917004-8a875621-e904-4df8-9b27-369a33fe3a11.jpg)


#### Стъпка 3
**Използвване на серийния монитор за наблюдение на работата**

След като свържем GSM модула към Aduino UNO и захраним установката, наблюдаваме следния резултат в серийния монитор (това е успешен резултат):

!!! type danger "Серийният монитор трябва да бъде настроен по следния начин: _Both NL & CR, 9600 Baudrate_"

![ArduinoIDE-SerialMonitor-OUTPUT-v1_Annotation_2021-12-15](https://user-images.githubusercontent.com/47386361/146197952-5c91d80a-91ee-441d-86f0-23d123acf628.jpg)

### 2.Контролиране на реле модул
**Ще използваме Arduino UNO за да имплементираме код разбиращ няколко команди.**

#### Свързане
Следва диаграма на свързките между релето и контролера.

![ArduinoUNO-RelayModule-Control_Annotation_2021-12-21](https://user-images.githubusercontent.com/76831786/146924659-9abd314a-f986-4219-8781-2147018752f0.jpg)

#### Основен код
Следващият код ще изпозлваме като основа за следващите примери, в който ще добавим приемане на команда през серийния порт, т.н. ...

```c++
int RelayPin = 7;

void setup() {
  // Initialize serial connection at 9600 baudrate
  Serial.begin(9600);
  
  // Confirm that serial comm. is established
  Serial.println("Serial communication established.");
  
  // Set RelayPin as an output pin
  Serial.println("Setting RelayPin as output");
  pinMode(RelayPin, OUTPUT);
}

void loop() {
  // Turn on the relay...
  Serial.println("Turning the relay on (digitalWrite)");
  digitalWrite(RelayPin, LOW);
  delay(400);
  Serial.println("Reading pin state with digitalRead and returning the current state.");
  delay(100);
  Serial.println(digitalRead(RelayPin));
  delay(2500);
  
  // Turn off the relay...
  Serial.println("Turning the relay off (digitalWrite)");
  digitalWrite(RelayPin, HIGH);
  delay(400);
  Serial.println("Reading pin state with digitalRead and returning the current state.");
  delay(100);
  Serial.println(digitalRead(RelayPin));
  delay(2500);
}
```

Резултата наблюдаван в серийния монитор:

![image](https://user-images.githubusercontent.com/76831786/146934168-1162ab69-346b-4dc2-9577-6cac856b5b4f.png)

Реални снимки на установката:

![Uno-RelayModule (2)](https://user-images.githubusercontent.com/76831786/146932715-45296b7b-a011-4c4e-babc-be97c8e3e218.jpg)

Кратко видео по време на операция:

![Basic-Uno-RelayModule](https://user-images.githubusercontent.com/76831786/146933599-835186f6-ed41-4611-92a8-04913feaf7b0.gif)

### Стъпка 3 Трябва да бъде отделна точка
Добавяме Реле модула към установката.

Диаграма на свързването

![ArdunoGSM-Relay_Annotation_2021-12-15](https://user-images.githubusercontent.com/47386361/146207437-34cc843c-dfa7-453d-8568-f5d75a0d831e.jpg)

