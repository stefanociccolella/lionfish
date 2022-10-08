#include <Servo.h>
byte servoPin1 = 5;
byte servoPin2 = 9;
byte servoPin3 = 6;
byte servoPin4 = 3;
byte servoPin5 = 10;
byte servoPin6 = 11;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int CCW = 1400;
int CW = 1520;
int Idle = 1480; 
int IdleTB = 1475;

void setup() {
  Serial.begin(9600);

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

void loop() {
  
  Serial.println("Enter val"); //"Enter PWM signal value 1100 to 1900, 1480 to stop" (Changing to val 1-10 for ascending, descending, etc...)
  
  while (Serial.available() == 0);
  
  int val = Serial.parseInt(); 
  Serial.println(val);
  
  if(val == 1) // Ascending
  {
    servo1.writeMicroseconds(Idle); 
    servo2.writeMicroseconds(IdleTB);
    servo3.writeMicroseconds(Idle);
    servo4.writeMicroseconds(Idle);
    servo5.writeMicroseconds(Idle);
    servo6.writeMicroseconds(Idle);
    delay(900);


    servo1.writeMicroseconds(CCW);
    servo2.writeMicroseconds(CW);
  }

  else if(val == 2) // Descending
  {

    servo1.writeMicroseconds(Idle); 
    servo2.writeMicroseconds(IdleTB);
    servo3.writeMicroseconds(Idle);
    servo4.writeMicroseconds(Idle);
    servo5.writeMicroseconds(Idle);
    servo6.writeMicroseconds(Idle);
    delay(900);


    servo1.writeMicroseconds(CW);
    servo2.writeMicroseconds(CCW);
  }

  else if(val == 3) // Forward
  {

    servo1.writeMicroseconds(Idle); 
    servo2.writeMicroseconds(IdleTB);
    servo3.writeMicroseconds(Idle);
    servo4.writeMicroseconds(Idle);
    servo5.writeMicroseconds(Idle);
    servo6.writeMicroseconds(Idle);
    delay(900);


    servo3.writeMicroseconds(CW);
    servo4.writeMicroseconds(CCW);
    servo5.writeMicroseconds(CW);
    servo6.writeMicroseconds(CCW);
  }

  else if(val == 4) // Backward
  {
    servo1.writeMicroseconds(Idle); 
    servo2.writeMicroseconds(IdleTB);
    servo3.writeMicroseconds(Idle);
    servo4.writeMicroseconds(Idle);
    servo5.writeMicroseconds(Idle);
    servo6.writeMicroseconds(Idle);
    delay(900);


    servo3.writeMicroseconds(CCW);
    servo4.writeMicroseconds(CW);
    servo5.writeMicroseconds(CCW);
    servo6.writeMicroseconds(CW);
  }

  else if(val == 5) // Lateral Left
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

  else if(val==6) // Lateral Right
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

  else if(val==7) // Rotate Left
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

  else if(val==8) // Rotate Right
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

  else if(val==9) // Pitch Up
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

  else if(val==10) // Pitch Down
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

  else if (val>20)
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