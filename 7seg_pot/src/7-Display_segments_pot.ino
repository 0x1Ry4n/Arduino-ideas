#define ANALOG A0 // analog port of the potentiometer
#define pinA 4 // pin A display
#define pinB 5 // pin B display
#define pinC 6 // pin C display
#define pinD 7 // pin D display
#define pinE 8 // pin E display
#define pinF 9 // pin F display
#define pinG 10 // pin G display
#define PUSH_BUTTON 13 // digital port of the push_button
#define _SIZE 7
typedef unsigned int u_int; // alias for unsigned int 

const u_int DisplayPins[] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG}; // pins display in a vector

class Display { 
	private: 
  		u_int values[_SIZE]; // 7 values. "0 or 1" to 7 digital ports
	public: 
		void Pattern(u_int a, u_int b, u_int c, u_int d, u_int e, u_int f, u_int g); 
};


void setup() {
	for(int i = 0; i < sizeof(DisplayPins); i++)
		pinMode(DisplayPins[i], OUTPUT); 
	
	pinMode(PUSH_BUTTON, INPUT);
}

void loop() {
	Display display;  
	
	int potValue =  analogRead(ANALOG); // Collect analogic value of potentiometer
  	int mapValue = map(potValue, 0, 1023, 0, 9); // Map the received analog values to a range between 0 and 9 states 
	
	if(digitalRead(PUSH_BUTTON) == HIGH){ // If push_button switched on, clean 7-seg display
		display.Pattern(0, 0, 0, 0, 0, 0, 0);
	}else{
		switch(mapValue) {
			case 1: display.Pattern(1, 1, 0, 1, 0, 1, 1);break; // Conditions for each value selected on the potentiometer
			case 2: display.Pattern(0, 1, 1, 1, 1, 1, 0);break;
			case 3: display.Pattern(1, 1, 1, 1, 1, 0, 0);break;
			case 4: display.Pattern(0, 0, 0, 0, 1, 1, 1);break;
			case 5: display.Pattern(1, 0, 1, 0, 1, 0, 1);break;
			case 6: display.Pattern(0, 0, 0, 0, 0, 1, 1);break;
			case 7: display.Pattern(0, 1, 1, 1, 1, 1, 1);break;
			case 8: display.Pattern(1, 1, 1, 1, 1, 0, 0);break;
			case 9: display.Pattern(0, 1, 1, 0, 0, 1, 1);break;
				
		}
	}
}

void Display :: Pattern(u_int a, u_int b, u_int c, u_int d, u_int e, u_int f, u_int g) { // Display class member
	u_int tempValues[_SIZE] = {a, b, c, d, e, f, g}; // Receive values as parameter and keep it on a temp array, "tempValues"

	for(int j = 0; j < _SIZE; j++) // Loop to keep temp values as parameter inside on private "values" variable of class Display
		this->values[j] = tempValues[j]; 
	
	for(int i = 0; i < _SIZE; i++) // Loop to cycle through the 7-seg display pins and the values of the private "values" variable of the Display class
		digitalWrite(DisplayPins[i], this->values[i]); // I connect the pins for each value traveled
}
