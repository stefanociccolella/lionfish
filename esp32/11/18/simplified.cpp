#include <stdlib.h>
#include <ESP32Servo.h>
Servo myservo;        // create servo object to control a servo
                      // 16 servo objects can be created on the ESP32
int incomingByte = 0; // for incoming serial data
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42

int ledPin = 2;   // LED
int leakPin = 13; // Leak Signal Pin
int leak = 0;     // 0 = Dry , 1 = Leak

int servoPin1 = 27; // 5
int servoPin2 = 14; // 9
int servoPin3 = 32; // 6
int servoPin4 = 25; // 3
int servoPin5 = 26; // 10
int servoPin6 = 33; // 11 change idle`

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int CCW = 1400;
int CW = 1520;
int Idle = 1480;   // 1480
int IdleTB = 1485; // 1475
const int numChars = 6;
char receivedChars[numChars];
float motorinstructions[numChars];
double sensorArray[12];
boolean printData = false;
char *string, *stopstring;

char startMarker = '[';
char endMarker = ']';
char delimiter = ',';

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(leakPin, INPUT);

    Serial.begin(115200);
    Serial.println("<Arduino is ready>");
    // Allow allocation of all timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    servo1.setPeriodHertz(50); // standard 50 hz servo
    servo2.setPeriodHertz(50); // standard 50 hz servo
    servo3.setPeriodHertz(50); // standard 50 hz servo
    servo4.setPeriodHertz(50); // standard 50 hz servo
    servo5.setPeriodHertz(50); // standard 50 hz servo
    servo6.setPeriodHertz(50); // standard 50 hz servo

    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    servo4.attach(servoPin4);
    servo5.attach(servoPin5);
    servo6.attach(servoPin6);

    servo1.writeMicroseconds(Idle);
    servo2.writeMicroseconds(Idle);
    servo3.writeMicroseconds(Idle);
    servo4.writeMicroseconds(Idle);
    servo5.writeMicroseconds(Idle);
    servo6.writeMicroseconds(IdleTB);
}

void loop()
{
    static boolean recvInProgress = false;
    int ndx = 0;
    char rc;
    int i = 0;
    // sensorArray = 
    readSensors();

    // incoming instructions
    while (Serial.available() > 0 && printData == false)
    {
        rc = Serial.read();
        if (recvInProgress == true)
        {
            if (rc == endMarker)
            {
                motorinstructions[i] = strtof(receivedChars, &stopstring); // cast whole array to float
                recvInProgress = false;
                ndx = 0;
                printData = true;
            }
            if (rc == delimiter)
            {
                motorinstructions[i] = strtof(receivedChars, &stopstring); // cast whole array to float
                memset(receivedChars, 0, sizeof receivedChars);
                i = i + 1;
                ndx = 0;
            }
            else
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars)
                {
                    ndx = numChars - 1;
                }
            }
        }
        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }
    if (Serial.available() > 0 ){
        Serial.write(lead);
    }

    servo1.writeMicroseconds(190 * motorinstructions[0] + Idle);
    servo2.writeMicroseconds(190 * motorinstructions[1] + Idle);
    servo3.writeMicroseconds(190 * motorinstructions[2] + Idle);
    servo4.writeMicroseconds(190 * motorinstructions[3] + Idle);
    servo5.writeMicroseconds(190 * motorinstructions[4] + Idle);
    servo6.writeMicroseconds(190 * motorinstructions[5] + IdleTB);
}

void readSensors()
{
    leak = digitalRead(leakPin); // Read the Leak Sensor Pin
    digitalWrite(ledPin, leak);  // Sets the LED to the Leak Sensor's Value
}