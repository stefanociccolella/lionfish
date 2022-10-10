#include <stdlib.h>
const int numChars = 6;
char receivedChars[numChars];
float motorinstructions[numChars];
boolean printData = false;
char *string, *stopstring;

void setup() {
  Serial.begin(115200);
  Serial.println("<Arduino is ready>");
}

void loop() {
  static boolean recvInProgress = false;
  int ndx = 0;
  char startMarker = '[';
  char endMarker = ']';
  char delimiter = ',';
  char rc;
  int i = 0;

  while (Serial.available() > 0 && printData == false) {
    rc = Serial.read();
    if (recvInProgress == true) {
      if (rc == endMarker) {
        motorinstructions[i] = strtof(receivedChars, &stopstring);  //cast whole array to float
        recvInProgress = false;
        ndx = 0;
        printData = true;
      }
      if (rc == delimiter) {
        motorinstructions[i] = strtof(receivedChars, &stopstring);  //cast whole array to float
        memset(receivedChars, 0, sizeof receivedChars);
        i = i + 1;
        ndx = 0;
      } else {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
  showPrintData();
}

void showPrintData() {
  if (printData == true) {
    Serial.print("size of motorinstructions is:");
    Serial.print(numChars);
    Serial.print("This just in .../n ");
    for (int i = 0; i < numChars; i++) {
      Serial.print(motorinstructions[i]);
      Serial.print("  ");
    }
    // cast to string
    printData = false;
  }
}