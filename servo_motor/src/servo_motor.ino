#include <Servo.h>

#define SERVO 9 // Porta Digital 6 PWM
#define ANALOG_POT A0
#define PinR 7
#define PinB 6
#define PinG 5

Servo servo; // Servo variable
int position; // Servo position

void setup ()
{
  servo.attach(SERVO);
  Serial.begin(9600);
  servo.write(0); // Init position 0 
}

void loop()
{
  int value = analogRead(ANALOG_POT);
  int valueMap = map(value, 0, 1023, 0, 179);
  
  for(position = 0; position < valueMap; position++)
  {
    servo.write(position);
    if(position >= 45 && position < 90)
    	setColor(0, 255, 0); // Set color on led 
    else if(position >= 90 && position < 120)
    	setColor(255, 255, 0);
    else 
      	setColor(255, 0, 0);
    delay(15);
  }
	
  for(position = 90; position >= valueMap; position--)
  {
    if(position >= 45 && position < 90)
    	setColor(0, 255, 0);
    else if(position >= 90 && position < 120)
    	setColor(255, 255, 0);
    else 
      	setColor(255, 0, 0);
    servo.write(position);
    delay(15);
  }
  
  
  delay(1000);
}

void setColor(int red, int green, int blue){
  analogWrite(PinR, red); 
  analogWrite(PinG, green); 
  analogWrite(PinB, blue); 
}