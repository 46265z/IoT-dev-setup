# MQTT
<!-- ## История
## Основни характеристики
## Приложение -->
Ще изполваме базов IoT безжичен модул ESP8266 за няколко практически примера за приложението на MQTT.
Модулът ще програмираме с Arduino IDE. За телеметрия ще използваме MQTT брокер предоставен от [flespi](https://flespi.com/mqtt-broker).


## Нужни
- **Espressif ESP8266** (Всяка развойна платка ориентирана около този чип върши работа.)
- **USB кабел тип Micro-B** (Някои кабели са предназначени само за захранване. Трябва ни такъв с линия за данни и захранване.)
- **Регистрация във [flespi](https://flespi.com/mqtt-broker)** (Безплатната версия е повече от достатъчна.)
- **Arduino IDE с tool chain-а за ESP8266** (_**TODO** линк към пояснение как да бъде инсталиран tool chain-а_)
- **Arduino Client for MQTT - PubSubClient by knolleary** (Библиотека за Arduino IDE) (_**TODO** линк към пояснение как да бъде исталирана_)


## Регистрация и тестване на връзката
Тъй като автентификацията на устроиствата свързващи се към MQTT брокера е задължителна, преди да преминем към писането на код трябва да създадем токен. Този токен се състои от 64 символа и платформата го генерира автоматично. В най-простия слиучай се задава като име на устройството в неговия код (ще го разгледаме подробно в примера).

### Генериране на токен
След като сте влезли в акаунта си, отидете в меню **Tokens<sub>Access control</sub>** и щракнете върху бутона **Add new token** (зеления +). Резултатът е контекстно меню с няколко полета, като за всяка има пояснение отстрани. Начина по който процедирам аз е да въведа ключова дума в полето **Info**, нещо което ми напомня за какво използвам този токен и на кое у-во, също така попълвам полето **Expire**, обикновено задавам 1 година от момента на създаване.

![p0Y2NEjYkr](https://user-images.githubusercontent.com/47386361/147873092-0450b9fc-0fd5-49cd-9896-8dd0a30c9c84.gif)

### Код
След като имаме токен за автентификация можем да преминем към програмирането на платката.
!!! type info "Не забравяйте, че различните платки разполагат с различен USB интерфейс (напр. CH340, CP21xx). Възможно е драйверите да не се инсталират автоматично (за MS Windows). В случай, че срещнете проблем, това е възможна причина."

```c++
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "IoT-dev-env"; // Enter your WiFi name
const char *password = "12345678";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "mqtt.flespi.io";
const char *topic = "esp8266/test";
const char *mqtt_username = "<YOUR_FLESPI_TOKEN>";
const char *mqtt_password = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("[INFO]\tConnecting to WiFi..");
  }
  Serial.println("[INFO]\tWIFI connection established.");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("[INFO]\tThe client %s is connecting to the MQTT Broker . . .\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("[INFO]\tConnection to MQTT Broker established.");
      } else {
          Serial.print("[WARNING]\tfailed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  // publish and subscribe
  client.publish(topic, "hello");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("[INFO]\tMessage arrived in topic: ");
  Serial.println(topic);
  Serial.print("\t\tMessage:");
  for (int i = 0; i < length; i++) {
      Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
  client.loop();
}
```

### Обеснение към кода

1.Вмъкваме библиотеките **ESP8266WiFi** и **PubSubClient**. Първата отговаря за връзката на платката към WiFi мрежата, а **PubSubClient**, както името подсказва, позволява ESP8266 да се свързва към MQTT Broker, да изпраща и получава съобщения.

```c++
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
```

2.Дефинираме константи в чието съдържание отговаря на името на всяка. Име на мрежата, парола за мрежата и нужната информация за връзка към MQTT брокера.

```c++
// WiFi
const char *ssid = ""; // Enter your WiFi name
const char *password = "";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "mqtt.flespi.io";
const char *topic = "esp8266/test";
const char *mqtt_username = "<TOKEN_FROM_FLESPI>";
const char *mqtt_password = ""; // leave this empty
const int mqtt_port = 1883;
```

3.Инстацийраме WiFi клиент. След това добавяме MQTT клиента.
```c++
WiFiClient espClient;
PubSubClient client(espClient);
```

4.Настройваме серийния порт за да можем да наблюдаваме случващото се в системата по време на операция. Стартираме свързването към мрежата. Само след като връзката е осъществена изпълнението продължава, обелязва се в серийния монитор.
```c++
// Set software serial baud to 115200;
Serial.begin(115200);
// connecting to a WiFi network
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.println("[INFO]\tConnecting to WiFi..");
}
Serial.println("[INFO]\tWIFI connection established.");
```

5.Стартираме свързването с MQTT брокера, задавайки нужната информация на клиента и регистрираме callback функция (изпълнява се при получаване на съобшение като изписва темата на която е получено съобщение както и съдържанието му в серийния монитор)
```c++
//connecting to a mqtt broker
client.setServer(mqtt_broker, mqtt_port);
client.setCallback(callback);
```

6.Изчакваме отговор от брокера за състоянието на връзката (осъществена или не). Своенвременно информацията се изписва в серийния монитор, в случай, че връзката е неуспешна се изписва код за причината.
```c++
while (!client.connected()) {
	String client_id = "esp8266-client-";
	client_id += String(WiFi.macAddress());
	Serial.printf("[INFO]\tThe client %s is connecting to the MQTT Broker . . .\n", client_id.c_str());
	if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
		Serial.println("[INFO]\tConnection to MQTT Broker established.");
	} else {
		Serial.print("[WARNING]\tfailed with state ");
		Serial.print(client.state());
		delay(2000);
	}
}
```

7.При успешно свързване, платката изпраща съобщение на предварително зададената тема със съответното съдържание и се регистрира към същата за получаване на данни.
```c++
// publish and subscribe
client.publish(topic, "hello");
client.subscribe(topic);
```

8.Callback функцията се изпълнява всеки път когато клиента получи съобщение. Следващата функция изписва темата на която е получено съобщението и неговото съдържание в серийния монитор.
```c++
void callback(char *topic, byte *payload, unsigned int length) {
	Serial.print("[INFO]\tMessage arrived in topic: ");
	Serial.println(topic);
	Serial.print("\t\tMessage:");
	for (int i = 0; i < length; i++) {
		Serial.print((char) payload[i]);
	}
	Serial.println();
	Serial.println("-----------------------");
}
```


## Обмен на данни
Всъщност, вече го направихме! В момента в който изпращаме съобщение към брокера за да уведомим, че сме свързвани (когато изпращаме съобщението "hello") обменяме данни с всички други, абонирани към същата тема. Получихме данни когато от уеб интерфейса на flespi изпратихме съобщение и го видяхме в серийния монитор.
За да бъде пълен примера, обаче, ще добавим няколко реда към вече съшествуващия код за да покрием и тази точка.


### От серийния монитор към MQTT
Искаме да въведем някакво съобщение в серийния монитор и то да се изпрати към брокера.

### Код
В основната `loop` функция, след реда `client.loop()` добавяме следния код:

```c++
if (Serial.available() > 0) {
	String serialMon_msg = Serial.readString();
	Serial.print(serialMon_msg);
	client.publish(topic, serialMon_msg.c_str());
}
```
След като компилираме и качим кода на ESP8266 платката, всичко което напишем в серийния монитор ще бъде изпратено към брокера и всеки клиент абониран към правилната тема ще получи данните.
