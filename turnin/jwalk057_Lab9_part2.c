/*	Author: lab
 *  Partner(s) Name: Jeremy Walker
 *	Lab Section:
 *	Assignment: Lab # 9  Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link:
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

char threeLEDs = 0x00;
char blinkingLED = 0x00;
enum BLINK {Off, B3} BlinkingLEDSM;
enum THREELED {Wait, B0,B1,B2} ThreeLEDsSM;
enum COMBINE {On} CombineLEDsSM;
void TickBlink(){
	switch(BlinkingLEDSM){
		case Off:
			BlinkingLEDSM = B3;
			blinkingLED = 0x00;
			break;
		case B3:
			 BlinkingLEDSM = Off;
			 blinkingLED = 0x08;
			break;
	}
}
void TickThree(){
	switch(ThreeLEDsSM){
		case Wait:
			ThreeLEDsSM = B0;
			threeLEDs = 0x00;
			break;
		case B0:
			ThreeLEDsSM = B1;
                        threeLEDs = 0x01;
                        break;
		case B1:
			ThreeLEDsSM = B2;
                        threeLEDs = 0x02;
                        break;
		case B2:
			ThreeLEDsSM = B0;
                        threeLEDs = 0x04;
                        break;

	}
}
void TickCombine(){
	switch(CombineLEDsSM){
		case On:
			PORTB = blinkingLED | threeLEDs;
			break;
	}
}


int main(void) {
	unsigned int threeLEDTime = 300;
	unsigned int blinkLEDTime = 1000;
	unsigned int period = 1;
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(period);
	TimerOn();
	BlinkingLEDSM = Off;
	ThreeLEDsSM = B0;
    /* Insert your solution below */
    while (1) {
	if(blinkLEDTime >= 1000){
		TickBlink();
		blinkLEDTime = 0;
	}
	if(threeLEDTime >= 300){
		TickThree();
		threeLEDTime = 0;
	 }
	TickCombine();
	while(!TimerFlag);
	TimerFlag=0;
	blinkLEDTime += period;
	threeLEDTime += period;
    }
    return 1;
}
