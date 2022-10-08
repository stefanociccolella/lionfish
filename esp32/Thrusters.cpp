#include <ESP32Servo.h>
Servo myservo;  // create servo object to control a servo
                // 16 servo objects can be created on the ESP32
int incomingByte = 0; // for incoming serial data
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42

int servoPin1 = 17; //5
int servoPin2 = 18; //9
int servoPin3 = 19; //6
int servoPin4 = 21; //3
int servoPin5 = 22; //10
int servoPin6 = 23; //11

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int CCW = 1400;
int CW = 1520;
int Idle = 0b0000; //1480
int IdleTB = 0b0000; //1475

void setup() {
  Serial.begin(115200);

	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

    servo1.setPeriodHertz(50);    // standard 50 hz servo
    servo2.setPeriodHertz(50);    // standard 50 hz servo
    servo3.setPeriodHertz(50);    // standard 50 hz servo
    servo4.setPeriodHertz(50);    // standard 50 hz servo
    servo5.setPeriodHertz(50);    // standard 50 hz servo
    servo6.setPeriodHertz(50);    // standard 50 hz servo


    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    servo4.attach(servoPin4);
    servo5.attach(servoPin5);
    servo6.attach(servoPin6);

    servo1.writeMicroseconds(Idle); // send "stop" signal to ESC.
    delay(1000); // delay to allow the ESC to recognize the stopped signal

    servo2.writeMicroseconds(IdleTB); // send "stop" signal to ESC.
    delay(1000); // delay to allow the ESC to recognize the stopped signal

    servo3.writeMicroseconds(Idle); // send "stop" signal to ESC.
    delay(1000); // delay to allow the ESC to recognize the stopped signal

    servo4.writeMicroseconds(Idle); // send "stop" signal to ESC.
    delay(1000); // delay to allow the ESC to recognize the stopped signal

    servo5.writeMicroseconds(Idle); // send "stop" signal to ESC.
    delay(1000); // delay to allow the ESC to recognize the stopped signal
    
    servo6.writeMicroseconds(Idle); // send "stop" signal to ESC.
    delay(1000); // delay to allow the ESC to recognize the stopped signal
}
void write_motors(int t1, int t2, int t3, int t4, int t5, int t6){
  servo1.writeMicroseconds(t1); 
  servo2.writeMicroseconds(t2);
  servo3.writeMicroseconds(t3);
  servo4.writeMicroseconds(t4);
  servo5.writeMicroseconds(t5);
  servo6.writeMicroseconds(t6);
}

void loop() {
  
  // Serial.println("Enter 1-9"); //"Enter PWM signal value 1100 to 1900, 1480 to stop" (Changing to val 1-10 for ascending, descending, etc...)
  
  if (Serial.available() > 0) {
      // read the incoming byte:
    incomingByte = Serial.read();
    Serial.print("ESP32 received: ");
    Serial.println(incomingByte);
  
  
    if(incomingByte == 49) // Ascending 1
    {
      write_motors(Idle,IdleTB,Idle,Idle,Idle,Idle)
      delay(900);
      write_motors(CCW,CW,Idle,Idle,Idle,Idle)
    }

    else if(incomingByte == 50) // Descending 2
    {
      write_motors(Idle,IdleTB,Idle,Idle,Idle,Idle)
      delay(900);
      write_motors(CW,CCW,Idle,Idle,Idle,Idle)
    }

    else if(incomingByte == 51) // Forward 3
    {
      write_motors(Idle,IdleTB,Idle,Idle,Idle,Idle)
      delay(900);
      write_motors(Idle,IdleTB,CW,CCW,CW,CCW)
    }

    else if(incomingByte == 52) // Backward 4
    {
      write_motors(Idle,IdleTB,Idle,Idle,Idle,Idle)
      delay(900);
      write_motors(Idle,IdleTB,CCW,CW,CCW,CW)
    }

    else if(incomingByte == 53) // Lateral Left 5
    {
      servo1.writeMicroseconds(Idle); 
      servo2.writeMicroseconds(IdleTB);
      servo3.writeMicroseconds(Idle);
      servo4.writeMicroseconds(Idle);
      servo5.writeMicroseconds(Idle);
      servo6.writeMicroseconds(Idle);
      delay(900);


      servo3.writeMicroseconds(CCW);
      servo4.writeMicroseconds(CCW);
      servo5.writeMicroseconds(CW);
      servo6.writeMicroseconds(CW);
    }

    else if(incomingByte == 54) // Lateral Right 6
    {
      servo1.writeMicroseconds(Idle); 
      servo2.writeMicroseconds(IdleTB);
      servo3.writeMicroseconds(Idle);
      servo4.writeMicroseconds(Idle);
      servo5.writeMicroseconds(Idle);
      servo6.writeMicroseconds(Idle);
      delay(900);


      servo3.writeMicroseconds(CW);
      servo4.writeMicroseconds(CW);
      servo5.writeMicroseconds(CCW);
      servo6.writeMicroseconds(CCW);
    }

    else if(incomingByte == 55) // Rotate Left 7
    {
      servo1.writeMicroseconds(Idle); 
      servo2.writeMicroseconds(IdleTB);
      servo3.writeMicroseconds(Idle);
      servo4.writeMicroseconds(Idle);
      servo5.writeMicroseconds(Idle);
      servo6.writeMicroseconds(Idle);
      delay(900);


      servo3.writeMicroseconds(CCW);
      servo4.writeMicroseconds(CCW);
      servo5.writeMicroseconds(CCW);
      servo6.writeMicroseconds(CCW);
    }

    else if(incomingByte == 56) // Rotate Right 8
    {
      servo1.writeMicroseconds(Idle); 
      servo2.writeMicroseconds(IdleTB);
      servo3.writeMicroseconds(Idle);
      servo4.writeMicroseconds(Idle);
      servo5.writeMicroseconds(Idle);
      servo6.writeMicroseconds(Idle);
      delay(900);


      servo3.writeMicroseconds(CW);
      servo4.writeMicroseconds(CW);
      servo5.writeMicroseconds(CW);
      servo6.writeMicroseconds(CW);
    }

    else if(incomingByte == 57) // Pitch Up 9
    {
      servo1.writeMicroseconds(Idle); 
      servo2.writeMicroseconds(IdleTB);
      servo3.writeMicroseconds(Idle);
      servo4.writeMicroseconds(Idle);
      servo5.writeMicroseconds(Idle);
      servo6.writeMicroseconds(Idle);
      delay(900);


      servo1.writeMicroseconds(CW);
      servo2.writeMicroseconds(CW);
    }

    else if(incomingByte == 48) // Pitch Down 0
    {
      servo1.writeMicroseconds(Idle); 
      servo2.writeMicroseconds(IdleTB);
      servo3.writeMicroseconds(Idle);
      servo4.writeMicroseconds(Idle);
      servo5.writeMicroseconds(Idle);
      servo6.writeMicroseconds(Idle);
      delay(900);

      
      servo1.writeMicroseconds(CCW);
      servo2.writeMicroseconds(CCW);
    }

    else if (incomingByte == 63) //STOP "ENTER ?"
    {
      servo1.writeMicroseconds(Idle); 
      servo2.writeMicroseconds(IdleTB);
      servo3.writeMicroseconds(Idle);
      servo4.writeMicroseconds(Idle);
      servo5.writeMicroseconds(Idle);
      servo6.writeMicroseconds(Idle);
      delay(2000);
      
    }
  }
}