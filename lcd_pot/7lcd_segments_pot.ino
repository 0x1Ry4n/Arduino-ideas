#define ANALOG A0 //porta analógica do potênciometro
#define pinA 4 //pino A do led
#define pinB 5 //pino B do led
#define pinC 6 //pino C do led
#define pinD 7 //pino D do led
#define pinE 8 //pino E do led
#define pinF 9 //pino F do led
#define pinG 10 //pino G do led
#define PUSH_BUTTON 13 //porta digital do push_button
typedef unsigned int u_int; // Apelido para o unsigned int -> números inteiros positivos

const u_int LedPins[] ={pinA, pinB, pinC, pinD, pinE, pinF, pinG}; // Pinos do led em um vetor

class LCD { 
	private: 
  		u_int values[7]; // Temos 7 pinos do led, então são 7 valores para cada pino
	public: 
		void Padrao(u_int a, u_int b, u_int c, u_int d, u_int e, u_int f, u_int g);	 // Função para criar padrões no led
};


void setup() {
	for(int i = 0; i < sizeof(LedPins); i++)
		pinMode(LedPins[i], OUTPUT); // pinMode's automatizados para não ficar digitando um pra cada pino do led
	
	pinMode(PUSH_BUTTON, INPUT);
}

void loop() {
	LCD lcd;  //  "Instância" da classe LCD
	
	int valorPotenciometro =  analogRead(ANALOG); // Inicializei o valor do potênciometro
  	int valorMapeado = map(valorPotenciometro, 0, 1023, 0, 9); // Coleto o valor que está sendo inputado no potênciometro
	
	if(digitalRead(PUSH_BUTTON) == HIGH){
		lcd.Padrao(0, 0, 0, 0, 0, 0, 0);
	}else{
		switch(valorMapeado) {
			case 1: lcd.Padrao(1, 1, 0, 1, 0, 1, 1);break; // If's para cada valor escolhido, atribuindo assim um padrão para o led
			case 2: lcd.Padrao(0, 1, 1, 1, 1, 1, 0);break;
			case 3: lcd.Padrao(1, 1, 1, 1, 1, 0, 0);break;
			case 4: lcd.Padrao(0, 0, 0, 0, 1, 1, 1);break;
			case 5: lcd.Padrao(1, 0, 1, 0, 1, 0, 1);break;
			case 6: lcd.Padrao(0, 0, 0, 0, 0, 1, 1);break;
			case 7: lcd.Padrao(0, 1, 1, 1, 1, 1, 1);break;
			case 8: lcd.Padrao(1, 1, 1, 1, 1, 0, 0);break;
			case 9: lcd.Padrao(0, 1, 1, 0, 0, 1, 1);break;
				
		}
	}
}

void LCD :: Padrao(u_int a, u_int b, u_int c, u_int d, u_int e, u_int f, u_int g) { // Aqui é onde a mágica acontece
	u_int tempValues[7] = {a, b, c, d, e, f, g}; // Recebo os valores como parâmetro e os guardo em uma variável temporária, "tempValues"

	for(int j = 0; j < 7; j++) // Loop para guardar os valores recebidos como parâmetro para dentro da variável "values" privada da classe LCD
		this->values[j] = tempValues[j]; 
	
	for(int i = 0; i < sizeof(values); i++) // Loop para percorrer os pinos do led e os valores da variável "values" privada da classe LCD
		digitalWrite(LedPins[i], this->values[i]); // Ligo os pinos para cada valor percorrido
}
