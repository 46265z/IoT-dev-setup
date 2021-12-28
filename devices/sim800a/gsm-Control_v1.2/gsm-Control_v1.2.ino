/*
 * Програма за Arduino Uno която чете SMS от паметта на SIM карта.
 * Поредността на съобщението се въвежда през серийния порт чрез команда.
 * <команда, N sms>
 * <read_sms_number,2>
 */


// The library which makes the software serial connection on pins 2,3 
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800A
SoftwareSerial mySerial(3, 2); //SIM800A Tx & Rx is connected to Arduino #3 & #2

// size of recv buffer
const byte numChars = 32;

// array for storing parsing chars
char receivedChars[numChars];

// temporary array for use when parsing
char tempChars[numChars];


// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

/*
 * variable which hold the state if we are currently
 * receiving or not, i.e. if we already received already
 */
boolean newData = false;

void setup() {
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
  
  /*
   mySerial.println("AT+CMGR=1\r");//Read SMS at location 1.
                                  // I think this is the oldest message in the storage
   */

  // To read newly arrived SMS replace "AT+CMGR=1\r" from the line above
  // with "AT+CNMI=2,2,0,0,0\r" so it becomes:
  // mySerial.println("AT+CNMI=2,2,0,0,0\r");
  // mySerial.println("AT+CMGL=ALL\r");
  delay(1000);
}


// put your main code here, to run repeatedly:
void loop() {

  // this is the function which receive the data from serial monitor
  recvWithStartEndMarkers();
  
  if (newData == true) { // if this is true it means we are currently receiving data
    
    // this temporary copy is necessary to protect the original data
    // because strtok() used in parseData() replaces the commas with \0
    strcpy(tempChars, receivedChars);

    // this function parse the received data and save in to appropriate var
    parseData();
    
    // this function show the saved data from the variables, later i
    // will be used for sending it to mqtt or any different post process
    showParsedData();
    
    newData = false; // after we have finished with any processing of the
                     // data we set the variable to false
  }

}


// This function accept the start end marker data reception.
void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}


// Split the data into its parts.
void parseData() {

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  integerFromPC = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  floatFromPC = atof(strtokIndx);     // convert this part to a float

}


// Here is where we are going to implement our command set
// for controlling whatever we want or have to
void showParsedData() {

  // check the first part if it this string
  if (String(messageFromPC).equals("read_sms_number")) { // Convert to String so we can compare

    // here we have to implement all further logic for controlling the desired appliance
    // i.e. what should the board do when we send this ^ command
    Serial.print("[INFO]\tCommand received ");
    Serial.println(messageFromPC);
    delay(10);

    Serial.println(integerFromPC);
    read_sms_number(integerFromPC);
  }
  else {
    Serial.println("\n\n[WARNING]\tNOT IMPLEMENTED\n\n");
    return;
  }
}


// Function which accept the number of the message which
// should be read from SIM storage.
void read_sms_number(int sms_N) {
  Serial.println("[INFO]\tfrom read_sms_number(int sms_N) function");
  String atCommand = "AT+CMGR="+String(sms_N)+"\r";
  mySerial.println(atCommand);
  updateSerial();
  Serial.println();
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
