// Simple sketch on the ESP8266 to read data sent from ATmega328
//Dip switch 1,2 are set "On" to connect the ATmega and ESP serial TX/RX
// If you want to read the ESP in the serial monitor whilst ATmega and ESP connected then set dip switch 1,2,5,6 to "On"; at this setting any Serial.println will be sent back to the Atmega and confuse the JSON parsing so comment them all out that you do not want sent
// ArduinoJson must be version 5
// Every Serial.println message from ESP gets sent back to the Arduino, this is why all println are commented out soonly data is sent

#include <ArduinoJson.h>

void setup() {
//Serial.begin(115200); // got errors at this rate
  Serial.begin(57600);
  //Serial.begin(9600);
  }

void loop()
{
  bool StringReady;
  String json;

   //ACCEPT DATA FROM THE ARDUINO
         while (Serial.available()){ // listen for serial data from the Arduino Atmega328
         json=Serial.readString();
         StringReady = true;
         }
     
         if (StringReady){
          StaticJsonBuffer<200> jsonBuffer;  // preallocated memory to store the JsonObject max 200 bytes
          JsonObject& root = jsonBuffer.parseObject(json); // turning the string into JSON data
       
            if(!root.success()) {
              //Serial.println("parseObject() failed");
              return ;
            }
       
         String rawTemp = root["temperature"]; //
         String rawHum = root["humidity"]; //
         String temperatureMessage = rawTemp + "oC : temperature recieved from Arduino at ESP"; //
         String humidityMessage = rawHum + "% : humidity recieved from Arduino at ESP"; //
         Serial.println();
         Serial.println(temperatureMessage);
         Serial.println(humidityMessage);
         Serial.println();
         root.remove("temperature");// remove the temp field from the JSON root object so I can reuse the root object to send back data
         root.remove("humidity");
         // if the serial console is open it will print: 22:40:32.989 -> 21oC : temperature recieved from Arduino at ESP



//         // SEND DATA BACK TO THE ARDUINO
//         //delay (5000); // delay the send back by 5 seconds
//         String tempMessageSendToArduino = rawTemp + "oC OK";
//         DynamicJsonBuffer jbuffer;
//         // JsonObject& root = jbuffer.createObject(); // no need as the root object is alreadly made, if I wanted a new one I would put it here
//         //Serial.println("Data sent back to Arduino in next line");
//         root["retMsg"] = tempMessageSendToArduino;  // I am reusing the root object, I could make a new one
//         root.printTo(Serial);
//         Serial.println();

   }
}
