// Simple sketch on Arduino ATmega328 to send preset data in a "temp" JSON field to the ESP8266
// Upload to ATmega328 with dip switch 3,4 set ON
// To read the serial monitor for messages sent and returning message set dip switch 1,2,3,4 ON
// ArduinoJson must be version 5 https://arduinojson.org/v5/doc/ , in the future need to change code in this sketch for Ver 6

#include <ArduinoJson.h>
//Libraries
#include <DHT.h>;

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
  //Serial.begin(115200);
  Serial.begin(57600); // more reliable results at this baud rate than at 115200
  //Serial.begin(9600);
  dht.begin();
}

void loop() {
  //SEND DATA TO THE ESP8266
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  delay(3000); // wait 10 sec between each send to the ESP  - when changed to 5 seconds did not work properly
  DynamicJsonBuffer jbuffer;
  JsonObject& root = jbuffer.createObject();
  root["temperature"] = temp; // setting up the variable temp to hold 21 in the JSON object root]
  root["humidity"] = hum;
  root.printTo(Serial); // sending the numeral 21 to the ESP
  root.remove("temperature");// remove the temp field from the JSON root object so I can reuse the root object to read data from ESP
  // if the serial console is open it will print: 22:31:03.228 -> {"temp":"21"}
  Serial.println();


  // RECEIVE DATA FROM THE ESP

  bool StringReady;
  String jsonString = "";
  StringReady = false;

  if (!Serial.available())
    return ;  // if there is no serial data detected ten it bypasses all code folloing this point

  while (Serial.available()) { //listening for any data returned from the ESP
    jsonString = Serial.readString(); // putting all of the data into a string
    //if (jsonString.charAt(0) == '{') Serial.println("JSON } in data detected."); // checks if the data starts with a { and therefor is a JSON data  https://www.arduino.cc/en/Tutorial/StringCharacters
    //Serial.println("JSON data detected at Arduino.");
    //Serial.println(jsonString);
    //Serial.println();
    StringReady = true;
  }
  if (StringReady) { // checking if the string has data
    Serial.print(jsonString); // printing out the returning raw string data to the serial console
    StaticJsonBuffer<200> jsonBuffer;  // preallocated memory to store the JsonObject max 200 bytes
    JsonObject& root = jsonBuffer.parseObject(jsonString); // turning the string into JSON data

    if (!root.success()) {
      Serial.println("Failed to parse config file");
      return ;
    }

    //read the JSON data and put it ito a variable, this should read data back from the ESP 5 seconds after the data is sent
    String acceptedTempMessage = root["retMsg"];  //putting the temperature data returned from the ESP into a varialbe
    Serial.print(acceptedTempMessage); //prinitng the temperature data returned from the ESP to the serial console
    Serial.println(" - successful return");
    root.remove("retMsg");// remove the retMsg field from the JSON rtn object
    Serial.println();
  }

}
