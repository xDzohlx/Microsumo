/*
 * uSumo.cpp
 *
 * Created: 13/05/2016 10:43:14
 * Author : xDzohlx
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/iotn828.h>
//#include <../../../../../toolchain/avr8/avr8-gnu-toolchain/avr/include/avr/iotn1634.h>

volatile static uint16_t contador = 0x00;
volatile static uint16_t contador2 = 0x00;
volatile static uint8_t leds = 0x00;
volatile static uint8_t cont = 0x00;
volatile static uint16_t valor = 0x00;
int rutina = 0;
bool button = false;
bool superbutton = false;
bool proa;
bool popa;
bool babor;
bool estribor;

volatile static uint16_t sensor1;
volatile static uint16_t sensor2;
volatile static uint16_t sensor3;
volatile static uint16_t sensor4;


void setup(){
		DDRA = (0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
		PORTA = (0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
		PUEB |= (1<<1);

		DDRB = 0x00;

		PORTB = 0x00;

		//PUEC= (1<<1);

		DDRC = (1<<DDC7) | (1<<DDC6) | (0<<DDC5) | (0<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (0<<DDC0);

		PORTC = 0x00;

		DDRD=(0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);

		PORTD=(0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
		//TIMER 0 PWM
		TCCR0A=(1<<COM0A1) | (1<<COM0A0) | (1<<COM0B1) | (1<<COM0B0) | (1<<WGM01) | (1<<WGM00);
		TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (1<<CS00);
		TCNT0=0x00;
			OCR0A = 0x80;
			OCR0B = 0x80;
		TOCPMSA0=(0<<TOCC3S1) | (0<<TOCC3S0) | (0<<TOCC2S1) | (0<<TOCC2S0) | (0<<TOCC1S1) | (0<<TOCC1S0) | (0<<TOCC0S1) | (0<<TOCC0S0);
		TOCPMSA1=(0<<TOCC7S1) | (1<<TOCC7S0) | (0<<TOCC6S1) | (1<<TOCC6S0) | (0<<TOCC5S1) | (0<<TOCC5S0) | (0<<TOCC4S1) | (0<<TOCC4S0);
		TOCPMCOE=(1<<TOCC7OE) | (1<<TOCC6OE) | (0<<TOCC5OE) | (0<<TOCC4OE) | (1<<TOCC3OE) | (1<<TOCC2OE) | (0<<TOCC1OE) | (0<<TOCC0OE);
		
		TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);
		
		//TIMER1 16 BIT TIEMPOS
		TCCR1A = 0x00;
		TCCR1B = (1<<WGM12)|(1<<CS11);//|(1<<CS10);
		
		OCR1A = 0x03E8;
		OCR1B = 0x00FF;
		TCNT1 = 0x0000;
		TIMSK1 = (1<<TOIE1)|(1<<OCIE1A)|(1<<OCIE1B);
		//adc--------------------
		DIDR0 = (1<<ADC0D)|(1<<ADC1D)|(1<<ADC2D)|(1<<ADC3D)|(1<<ADC7D);
		ADMUXA = (0<<MUX2)|(0<<MUX1)|(0<<MUX0);//que canal
		ADMUXB = (0<<REFS)|(0<<MUX5);
		ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0)|(1<<ADATE);
		ADCSRA |= (1<<ADSC);//START ADC
		
		// Globally enable interrupts
		
		//PCMSK1 |= (1<<PCINT8);//|(1<<PCINT1)|(1<<PCINT3);
		//PCICR |= (1<<PCIE1);
		sei();

}
void arribabajo(){
	contador = 0x00;
	while(contador < 100){
		DDRA &= ~(1<<PORTA4);
		DDRA &= ~(1<<PORTA5);
		DDRA &= ~(1<<PORTA6);
	}
	contador = 0x00;
	while(contador < 100){
		DDRA |= (1<<PORTA4);
		DDRA |= (1<<PORTA5);
		DDRA |= (1<<PORTA6);
	}
	contador = 0x00;
	while(contador<= 100){
				DDRA &= ~(1<<PORTA4);
				DDRA &= ~(1<<PORTA5);
				DDRA &= ~(1<<PORTA6);
	}
	contador = 0x00;
	while(contador<= 100){
		DDRA |= (1<<PORTA5);
		DDRA |= (1<<PORTA4);
		DDRA |= (1<<PORTA6);
	}

contador = 0x00;
while(contador < 100){
	DDRA &= ~(1<<PORTA4);
	DDRA &= ~(1<<PORTA5);
	DDRA &= ~(1<<PORTA6);
}
contador = 0x00;
while(contador < 100){
	DDRA |= (1<<PORTA5);
	DDRA |= (1<<PORTA4);
	DDRA |= (1<<PORTA6);
}
contador = 0x00;
while(contador<= 100){
	DDRA &= ~(1<<PORTA4);
	DDRA &= ~(1<<PORTA5);
	DDRA &= ~(1<<PORTA6);}
contador = 0x00;
while(contador<= 100){
	DDRA |= (1<<PORTA4);
	DDRA |= (1<<PORTA5);
	DDRA |= (1<<PORTA6);
}
DDRA &= ~(1<<PORTA4);
DDRA &= ~(1<<PORTA5);
DDRA &= ~(1<<PORTA6);

}
void inicio(){
	arribabajo();
	PORTC |= (1<<PORTC1);
}
void seleccionrutinas(){
	bool select = false;
	volatile static uint8_t cont = 0x00;
	//unsigned char valoreeprom = 0x00;
	arribabajo();
	while(select == false){

	if(!(PINB & 0x02)){
		contador = 0x00;
		while(!(PINB & 0x02)){
					if (contador >= 10){
						button = true;
					}
					if (contador >= 500){
						superbutton = true;
						button = false;
						inicio();
					}
		}
		if(button){
			button = false;
			cont++;
			rutina++;
			switch(cont){
				case 1:
				//motor1on();
				DDRA |= (1<<PORTA4);
				DDRA &= ~(1<<PORTA6);
				DDRA &= ~(1<<PORTA5);
				break;
				case 2:
				//motor1off();
				DDRA &= ~(1<<PORTA4);
				DDRA |= (1<<PORTA6);
				DDRA &= ~(1<<PORTA5);
				break;
				case 3:
				DDRA &= ~(1<<PORTA4);
				DDRA &= ~(1<<PORTA6);
				DDRA |= (1<<PORTA5);
				
				break;
				case 4:
				DDRA &= ~(1<<PORTA4);
				DDRA &= ~(1<<PORTA6);
				DDRA &= ~(1<<PORTA5);
				cont = 0x00;
				rutina = 0x00;
				
				break;
				
				default:
				cont = 0x00;
				break;
			}//switch
			}else{
				if(superbutton){
					select = true;
					//cont--;
					//rutina--;
					//cuenta = true;					
				}
			
		}
	}
		}
}
void adelante(){
		OCR0A = 0x00;
		OCR0B = 0x00;
	TOCPMCOE=(1<<TOCC7OE) | (0<<TOCC6OE) | (1<<TOCC3OE) | (0<<TOCC2OE);//TOCC3OE
}
void stop(){
	TOCPMCOE=(1<<TOCC7OE) | (1<<TOCC6OE) | (0<<TOCC5OE) | (0<<TOCC4OE) | (1<<TOCC3OE) | (1<<TOCC2OE) | (0<<TOCC1OE) | (0<<TOCC0OE);
}
void izq(){
	adelante();
	TOCPMCOE=(0<<TOCC7OE) | (1<<TOCC6OE)| (1<<TOCC3OE) | (0<<TOCC2OE);
}
void derecha(){
	adelante();
	TOCPMCOE=(1<<TOCC7OE) | (0<<TOCC6OE)| (0<<TOCC3OE) | (1<<TOCC2OE);//TOCC3OE
}
void hardstop(){
	PORTC |= (1<<PORTC2)|(1<<PORTC3)|(1<<PORTC6)|(1<<PORTC7);
}
void superadelante(){
	
	adelante();
	contador = 0x00;
	while(contador <= 125){
		if (proa){
			OCR0A = 0x30;
			OCR0B = 0x30;
			}else{
			if (babor){
				OCR0B = 0x50;
			}
			if (estribor){
				OCR0A = 0x50;
			}
		}
	}
	if (proa){
		contador = 0x00;
		while(contador <= 300);
		DDRA &= ~(1<<PORTA5);
		if(proa){
			DDRA &= ~(1<<PORTA6);
			while((!(PINA & 0x01))||(!(PINA & 0x02))){
				if (proa){
					OCR0A = 0x30;
					OCR0B = 0x30;
					}else{
					if (babor){
						OCR0B = 0x50;
					}
					if (estribor){
						OCR0A = 0x50;
					}
				}
			}
			DDRA &= ~(1<<PORTA4);
			//buscar();
		}else
		DDRA &= ~(1<<PORTA4);
		//buscar();
	}else
	DDRA &= ~(1<<PORTA4);
	//buscar();
}
void buscar(){
		OCR0A = 0xFC;
		OCR0B = 0xFC;
		//TOCPMSA0=(0<<TOCC3S1) | (0<<TOCC3S0) | (0<<TOCC2S1) | (0<<TOCC2S0) | (0<<TOCC1S1) | (0<<TOCC1S0) | (0<<TOCC0S1) | (0<<TOCC0S0);
		//TOCPMSA1=(0<<TOCC7S1) | (1<<TOCC7S0) | (0<<TOCC6S1) | (1<<TOCC6S0) | (0<<TOCC5S1) | (0<<TOCC5S0) | (0<<TOCC4S1) | (0<<TOCC4S0);
		//TOCPMCOE=(1<<TOCC7OE) | (1<<TOCC6OE) | (0<<TOCC5OE) | (0<<TOCC4OE) | (1<<TOCC3OE) | (1<<TOCC2OE) | (0<<TOCC1OE) | (0<<TOCC0OE);
	izq();while(true){
	if((!(PINA & 0x01))){
			OCR0A = 0x50;
			OCR0B = 0x50;
		
		adelante();
		contador = 0x00;
		while(contador <= 150){
			if (proa){
				OCR0A = 0x80;
				OCR0B = 0x80;
				}else{
				if (babor){
					OCR0B = 0x50;
				}
				if (estribor){
					OCR0A = 0x50;
				}
			}
		}
		if (proa){
			contador = 0x00;
			while(contador <= 300);
			DDRA &= ~(1<<PORTA5);
			if(proa){
				DDRA &= ~(1<<PORTA6);
				while((!(PINA & 0x01))||(!(PINA & 0x02))){
					if (proa){
						OCR0A = 0x30;
						OCR0B = 0x30;
						}else{
						if (babor){
							OCR0B = 0x50;
						}
						if (estribor){
							OCR0A = 0x50;
						}
					}
				}
				//DDRA &= ~(1<<PORTA4);
				OCR0A = 0xFC;
				OCR0B = 0xFC;
				derecha();
			}else{
			OCR0A = 0xFC;
			OCR0B = 0xFC;
			derecha();
			}
		}else{
		OCR0A = 0xFC;
		OCR0B = 0xFC;
		derecha();
		}
		//contador = 0x00;
		//while(contador <= 10);
	}
	if((!(PINA & 0x02))){
		OCR0A = 0x03;
		OCR0B = 0x03;
		
		adelante();
		contador = 0x00;
		while(contador <= 150){
			if (proa){
				OCR0A = 0x30;
				OCR0B = 0x30;
				}else{
				if (babor){
					OCR0B = 0x50;
				}
				if (estribor){
					OCR0A = 0x50;
				}
			}
		}
		if (proa){
			contador = 0x00;
			while(contador <= 300);
			DDRA &= ~(1<<PORTA5);
			if(proa){
				DDRA &= ~(1<<PORTA6);
				while((!(PINA & 0x01))||(!(PINA & 0x02))){
					if (proa){
						OCR0A = 0x30;
						OCR0B = 0x30;
						}else{
						if (babor){
							OCR0B = 0x50;
						}
						if (estribor){
							OCR0A = 0x50;
						}
					}
				}
				//DDRA &= ~(1<<PORTA4);
						OCR0A = 0xFC;
						OCR0B = 0xFC;
				izq();
			}else{
					OCR0A = 0xFC;
					OCR0B = 0xFC;
					izq();	
			}
		}else{
							OCR0A = 0xFC;
							OCR0B = 0xFC;
							izq();	
		}
		//contador = 0x00;
		//while(contador <= 10);
	}
}
}
void atras(){
	TOCPMCOE=(0<<TOCC7OE) | (1<<TOCC6OE) | (0<<TOCC5OE) | (0<<TOCC4OE) | (0<<TOCC3OE) | (1<<TOCC2OE) | (0<<TOCC1OE) | (0<<TOCC0OE); //TOCC2OE Cmbio de sentido
}
void rutina1(){

adelante();	
contador = 0x00;
while(contador <= 150){
if (proa){
OCR0A = 0x30;
OCR0B = 0x30;
}else{
if (babor){
	OCR0B = 0x50;
}
if (estribor){
	OCR0A = 0x50;
}
}
	}
	if (proa){
		contador = 0x00;
		while(contador <= 300);
			DDRA &= ~(1<<PORTA5);
			if(proa){
				DDRA &= ~(1<<PORTA6);
				while((!(PINA & 0x01))||(!(PINA & 0x02))){
					if (proa){
						OCR0A = 0x30;
						OCR0B = 0x30;
						}else{
						if (babor){
							OCR0B = 0x50;
						}
						if (estribor){
							OCR0A = 0x50;
						}
						}
				}
				DDRA &= ~(1<<PORTA4);
				buscar();
			}else
			buscar();
	}else
		//DDRA &= ~(1<<PORTA6);
	buscar();
}
void rutina2(){
	while(1){
		derecha();
		contador = 0x00;
		while(contador <= 12);
		superadelante();
		while(true);
	}//sirve
}
void rutina3(){
	while(1){
	izq();
	contador = 0x00;
	while(contador <= 20);
	superadelante();
	while(true);
	}//sirve
	}
void rutina4(){
	while(1){
		izq();
		contador = 0x00;
		while(contador <= 30);
		superadelante();
		while(true);
	}
}	

ISR(TIMER1_COMPA_vect){
	contador++;
}

ISR(TIMER1_COMPB_vect){
leds++;	
//contador2++;
	if(leds <5){
		PORTA &= ~(1<<PORTA4);
		PORTA &= ~(1<<PORTA5);
		PORTA &= ~(1<<PORTA6);
	}
	if (leds >= 5){
		PORTA |= (1<<PORTA4);
		PORTA |= (1<<PORTA5);
		PORTA |= (1<<PORTA6);
		leds = 0x00;
	}
}

ISR(ADC_vect){
	if (cont == 0){
		cont++;
		sensor1 = ADC;	
		//ADMUXA = ()	//sensor 2
	}
	if (cont == 1){
		cont = 0;
		sensor2 = ADC;
	}
	//
	//if (cont == 0){
		//cont++;
		//sensor1 = ADC;
	//}
	//if (cont == 0){
		//cont++;
		//sensor1 = ADC;
	//}
}
ISR(PCINT1_vect){
		while(!(PINB & 0x01)){
		}
}
int main(void){
		setup();
		seleccionrutinas();
				while(!(PINB & 0x01)){
				DDRA |= (1<<PORTA4);
				DDRA |= (1<<PORTA6);
				DDRA |= (1<<PORTA5);
				}
		if (rutina == 0){
		rutina1();
		}
		if (rutina == 1){
		rutina2();
		}
		if (rutina == 2){
			rutina3();
		}
		if (rutina == 3){
			rutina4();
		}
}//main

