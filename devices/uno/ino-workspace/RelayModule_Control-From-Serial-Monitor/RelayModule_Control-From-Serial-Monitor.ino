int RelayPin = 7;


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
  // Initialize serial connection at 9600 baudrate
  Serial.begin(9600);
  delay(100);

  // Confirm that serial comm. is established
  Serial.println("Serial communication established.");

  // Set RelayPin as an output pin
  Serial.println("Setting RelayPin as output");
  pinMode(RelayPin, OUTPUT);
}


void loop() {
/* v1 Code
  // Turn on the relay...
  Serial.println("Turning the relay on (digitalWrite)");
  digitalWrite(RelayPin, LOW); delay(400);

  // Reading pin state with digitalRead and returning the current state.
  Serial.println("current state"); delay(100);
  Serial.println(digitalRead(RelayPin)); delay(2500);



  // Turn off the relay...
  Serial.println("Turning the relay off (digitalWrite)");
  digitalWrite(RelayPin, HIGH); delay(400);

  // Reading pin state with digitalRead and returning the current state.
  Serial.println("current state"); delay(100);
  Serial.println(digitalRead(RelayPin)); delay(2500);
*/
  // this is the function which receive the data from serial monitor
  recvWithStartEndMarkers();
  if (newData == true) { // if this is true it means we are currently receiving data
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    // because strtok() used in parseData() replaces the commas with \0
    
    // this function parse the received data and save in to appropriate var
    parseData();
    // this function show the saved data from the variables, later i
    // will be used for sending it to mqtt or any different post process
    showParsedData();
    newData = false; // after we have finished with any processing of the
                     // data we set the variable to false
  }
}


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


void parseData() {      // split the data into its parts

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
  if (String(messageFromPC).equals("relay_on")) { // Convert to String so we can compare
    
    // here we have to implement all further logic for controlling the desired appliance
    // i.e. what should the board do when we send this ^ command
    Serial.print("Command received ");
    Serial.println(messageFromPC);
    delay(10);
    
    digitalWrite(RelayPin, LOW);
    delay(10);
    Serial.println(digitalRead(RelayPin));
    
  }
  else if (String(messageFromPC).equals("relay_off")) { // Convert to String so we can compare
    
    // here we have to implement all further logic for controlling the desired appliance
    // i.e. what should the board do when we send this ^ command
    Serial.print("Command received ");
    Serial.println(messageFromPC);
    delay(10);
    
    digitalWrite(RelayPin, HIGH);
    delay(10);
    Serial.println(digitalRead(RelayPin));
    
  }
  else {
    
    Serial.println("\n\nNOT IMPLEMENTED\n\n");
    return;
    
  }
}


//// this function can be used as starter point when u implement ur own logic
//void showParsedData() {
//    Serial.print("Message ");
//    Serial.println(messageFromPC);
//    Serial.print("Integer ");
//    Serial.println(integerFromPC);
//    Serial.print("Float ");
//    Serial.println(floatFromPC);
//}
