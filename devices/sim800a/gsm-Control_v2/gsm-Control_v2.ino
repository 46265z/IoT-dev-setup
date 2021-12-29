/*
   Програма за Arduino Uno която чете SMS веднага щом той е получен.
   Обработва информацията, запазва САМО съдържанието на съобщението 
   в променлива от тип String и позволява изпълянване на логика при
   наличие на ключова дума в това съдържание.
*/


// The library which makes the software serial connection on pins 2,3
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800A
SoftwareSerial mySerial(3, 2); //SIM800A Tx & Rx is connected to Arduino #3 & #2


const int RelayPin = 7;


void setup() {
  // Set relay as OUTPUT
  pinMode(RelayPin, OUTPUT);

  // By default the relay is off
  digitalWrite(RelayPin, LOW);

  // put your setup code here, to run once:
  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
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
  mySerial.println("AT+CMGF=1"); // Set the modem in TEXT MODE
  updateSerial();

  // To read newly arrived SMS :
  mySerial.println("AT+CNMI=2,2,0,0,0\r");
  updateSerial();
  delay(1000);
}


// put your main code here, to run repeatedly:
void loop() {
  // updateSerial();
  String theMessage = read_sms();
  Serial.println(theMessage);
  if (theMessage.indexOf("relay_off") >= 0)
  {
    Serial.println("THE MSG CONTAINS THE KEYWORD");
    digitalWrite(RelayPin, LOW);
    Serial.println("LOW,OFF");
//    Serial.print("State after action");
//    Serial.println(digitalRead(RelayPin));
  }
  else if (theMessage.indexOf("relay_on") >= 0)
  {
    Serial.println("THE MSG CONTAINS THE KEYWORD");
    digitalWrite(RelayPin, HIGH);
    Serial.println("HIGH,ON");
//    Serial.print("State after action");
//    Serial.println(digitalRead(RelayPin));
  }
}

String read_sms()
{
  int x = 0; // sms character counter

  String sms = ""; //initialize

  unsigned long int prv_millis = millis(); //wait initialization

  while (1)
  {

    if (mySerial.available() > 0)
      // if(Serial.available() >0)
    {
      char incoming_sms = mySerial.read();
      //char incoming_sms=Serial.read();

      sms += incoming_sms; //add up all the characters as string

      prv_millis = millis();

      x++; // increment sms character counter
    }

    unsigned long int new_millis = millis();

    if ((x > 0) && ((new_millis - prv_millis) > 200)) //if a single letter has been received and no character been
      //received since last 200 msec, break
      break;
  }

  //Serial.print("received sms =");
  //Serial.println(sms);

  int m = 1 + sms.lastIndexOf('"');

  // find location of last ' " ' of sms format
  // [ +CMGL: 1,"REC UNREAD","+XXXXXXXXXXXX",,"01/01/21,09:55:16+08"
  // Test message 1 ]

  int n = sms.length(); // find the length of sms

  // Serial.print("actual sms =");
  //Serial.println(sms.substring(m,n)); // sms text lies between the two

  return (sms.substring(m, n)); //return the sms
}

void updateSerial() {
  delay(500);
  while (Serial.available())
  {
    //Forward what Serial received to Software Serial Port
    mySerial.write(Serial.read());
  }

  while (mySerial.available())
  {
    //Forward what Software Serial received to Serial Port
    Serial.write(mySerial.read());
  }
}
