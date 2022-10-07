#include <ESP32Servo.h>
Servo myservo;  // create servo object to control a servo
                // 16 servo objects can be created on the ESP32
int pos = 0;    // variable to store the servo position
int incomingByte = 0; // for incoming serial data
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
int servoPin = 18;

// function that writes position to servo
void moveServo(int position){
  myservo.write(position);
}

void setup() {
  Serial.begin(115200);

	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 0, 2400); // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if( incomingByte != 10){
      Serial.print("ESP32 received: ");
      Serial.println(incomingByte);
      moveServo(incomingByte);
    }
  }

}

