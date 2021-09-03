#define ANALOG A0 // analog port of the potentiometer
#define pinA 4 // pin A lcd
#define pinB 5 // pin B lcd
#define pinC 6 // pin C  lcd
#define pinD 7 // pin D lcd
#define pinE 8 // pin E lcd
#define pinF 9 // pin F lcd
#define pinG 10 // pin G lcd
#define PUSH_BUTTON 13 // digital port of the push_button
typedef unsigned int u_int; // alias for unsigned int 

const u_int LcdPins[] ={pinA, pinB, pinC, pinD, pinE, pinF, pinG}; // pins lcd in a vector

class LCD { 
	private: 
  		u_int values[7]; // 7 values. "0 or 1" to 7 ports
	public: 
		void Standard(u_int a, u_int b, u_int c, u_int d, u_int e, u_int f, u_int g); 
};


void setup() {
	for(int i = 0; i < sizeof(LedPins); i++)
		pinMode(LcdPins[i], OUTPUT); 
	
	pinMode(PUSH_BUTTON, INPUT);
}

void loop() {
	LCD lcd;  
	
	int potValue =  analogRead(ANALOG); // 
  	int mapValue = map(potValue, 0, 1023, 0, 9); // Map the received analog values to a range between 0 and 9 values 
	
	if(digitalRead(PUSH_BUTTON) == HIGH){ // If push_button switched on, clean 7-seg display
		lcd.Standard(0, 0, 0, 0, 0, 0, 0);
	}else{
		switch(mapValue) {
			case 1: lcd.Standard(1, 1, 0, 1, 0, 1, 1);break; // Conditions for each value selected on the potentiometer
			case 2: lcd.Standard(0, 1, 1, 1, 1, 1, 0);break;
			case 3: lcd.Standard(1, 1, 1, 1, 1, 0, 0);break;
			case 4: lcd.Standard(0, 0, 0, 0, 1, 1, 1);break;
			case 5: lcd.Standard(1, 0, 1, 0, 1, 0, 1);break;
			case 6: lcd.Standard(0, 0, 0, 0, 0, 1, 1);break;
			case 7: lcd.Standard(0, 1, 1, 1, 1, 1, 1);break;
			case 8: lcd.Standard(1, 1, 1, 1, 1, 0, 0);break;
			case 9: lcd.Standard(0, 1, 1, 0, 0, 1, 1);break;
				
		}
	}
}

void LCD :: Standard(u_int a, u_int b, u_int c, u_int d, u_int e, u_int f, u_int g) { // LCD class member
	u_int tempValues[7] = {a, b, c, d, e, f, g}; // Receive values as parameter and keep it on a temp array, "tempValues"

	for(int j = 0; j < 7; j++) // Loop to keep temp values as parameter inside on private "values" variable of class LCD
		this->values[j] = tempValues[j]; 
	
	for(int i = 0; i < sizeof(values); i++) // Loop to cycle through the LCD pins and the values of the private "values" variable of the LCD class
		digitalWrite(LcdPins[i], this->values[i]); // I connect the pins for each value traveled
}
