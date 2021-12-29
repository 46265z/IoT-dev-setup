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

  mySerial.println("AT+CMGF=1\r");

  /*
   mySerial.println("AT+CMGR=1\r");//Read SMS at location 1.
                                  // I think this is the oldest message in the storage
   */

  // To read newly arrived SMS replace "AT+CMGR=1\r" from the line above
  // with "AT+CNMI=2,2,0,0,0\r" so it becomes:
  mySerial.println("AT+CNMI=2,2,0,0,0\r");
  delay(1000);
}

void loop()
{
  updateSerial();
  if (mySerial.available() > 0) {
    int c = mySerial.read();
    Serial.write(c);
  }
  delay(100);
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
