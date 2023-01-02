#include <Servo.h>

#define TRIGGER 11 // trigger ultrasonic port
#define ECHO 10 // echo ultrasonic port 
#define SERVO 8
#define PinR 7
#define PinB 6
#define PinG 5
#define SIZEOF(val) sizeof(val) / sizeof(val[0])

Servo servo; 

typedef float decimal;

const decimal VELOCITY = 0.01723;  // sound velocity in centimeters
const int Pins[] = { PinR, PinG, PinB }; 

struct Ultrasonic {
    decimal DISTANCE;
    decimal DURATION;  
};

void setup()
{
   	pinMode(ECHO, INPUT);
  	pinMode(TRIGGER, OUTPUT);	
 	
    for(int i = 0; i < SIZEOF   (Pins); i++)
    {
	   pinMode(Pins[i], OUTPUT);
    }
  	
  	servo.attach(SERVO);
  	servo.write(0); // Init motor position 0 
  	Serial.begin(9600);
}

void loop()
{
    Ultrasonic sound;

    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);

   	sound.DURATION = pulseIn(ECHO, HIGH);
    sound.DISTANCE = sound.DURATION * VELOCITY; 
  	
    Serial.print("Distance: ");
  	Serial.println(sound.DISTANCE);
 	
	if(sound.DISTANCE >= 40 && sound.DISTANCE < 75){
    	setPosition(45);	
      	setColor(0, 255, 0);
    } else if(sound.DISTANCE >= 25 && sound.DISTANCE < 50) {
    	setPosition(90);
        setColor(0, 0, 255);
    } else if(sound.DISTANCE >= 15 && sound.DISTANCE < 25) {
      	setPosition(120);
      	setColor(255, 255, 0);
    } else if(sound.DISTANCE >= 5 && sound.DISTANCE < 10){
      	setPosition(180);
        setColor(255, 0, 0);
    }
}

int setColor(int red, int green, int blue)
{
    analogWrite(PinR, red);
    analogWrite(PinG, green);
    analogWrite(PinB, blue);
}

void setPosition(float pos) 
{
	for(int i = 0; i < pos; i++)
    {
       servo.write(pos);
    }
}


