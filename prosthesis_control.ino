#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH       650
#define MID_PULSE_WIDTH       1500
#define MAX_PULSE_WIDTH       2350
#define FREQUENCY             50
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int sensor1 = A0;
int sensor2 = A1; 

int motorRL = 0;   //Ring+Little
int motorMI = 4;   //Middle+Index
int motorT = 8;    //Thumb
int motorW = 12;    //Wrist

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  Serial.begin(9600);

}

void moveMotorFist(int controlIn, int motorOut)
{
  int pulse_wide, pulse_width, emgVal;
  
  // Read values from emg sensor
  emgVal = analogRead(controlIn);
  
  // Convert to pulse width
  pulse_wide = map(emgVal, 0, 1023, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  
  Serial.println(pulse_width);
  
  //Control Motor
  if(pulse_width>200){
    pwm.setPWM(motorOut, 0, 480);  
    }

  else if(pulse_width<100){
    pwm.setPWM(motorOut, 0, 0);
    }
  else{
      pwm.setPWM(motorOut, 0, pulse_width);
    }
  
 
}

void moveMotorWrist(int controlIn, int motorOut)
{
  int pulse_wide, pulse_width, emgVal;
  
  // Read values from emg sensor
  emgVal = analogRead(controlIn);
  
  // Convert to pulse width
  pulse_wide = map(emgVal, 0, 1023, MID_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(pulse_width);
  
  if(pulse_width>350){
    pwm.setPWM(motorOut, 0, 480);  
    }

  else if(pulse_width<100){
    pwm.setPWM(motorOut, 0, 0);
    }
  else{
      pwm.setPWM(motorOut, 0, pulse_width);
    }
    
}

void loop() {
   moveMotorFist(sensor1, motorRL);

   moveMotorFist(sensor1, motorMI);


   moveMotorFist(sensor1, motorT);

   moveMotorWrist(sensor2, motorW);
   



}
