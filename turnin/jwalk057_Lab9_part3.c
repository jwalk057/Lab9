/*	Author: lab
 *  Partner(s) Name: Jeremy Walker
 *	Lab Section:
 *	Assignment: Lab # 9  Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://youtu.be/tcO8rLjUDeo
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

char threeLEDs = 0x00;
char blinkingLED = 0x00;
char speaker =0x00;
enum SPEAKER {Mute, Sound, Sound2} SpeakerSM;
enum BLINK {Off, B3} BlinkingLEDSM;
enum THREELED {Wait, B0,B1,B2} ThreeLEDsSM;
enum COMBINE {On} CombineLEDsSM;
void TickSpeaker(button){
	switch(SpeakerSM){
	case Mute:
		if(button){speaker = 0x10; SpeakerSM = Sound;}
		break;
	case Sound:
		if(!button){speaker = 0x00; SpeakerSM = Mute;}
		else{speaker = 0x00; SpeakerSM = Sound2;}
		break;
		
	case Sound2:
                if(!button){speaker = 0x00; SpeakerSM = Mute;}
                else{speaker = 0x10; SpeakerSM = Sound;}
                break;
                }

}
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
			PORTB = threeLEDs | blinkingLED | speaker;
			break;
	}
}


int main(void) {
	unsigned int speakerTime = 2;
	unsigned int threeLEDTime = 300;
	unsigned int blinkLEDTime = 1000;
	unsigned int period = 1;
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	TimerSet(period);
	TimerOn();
	BlinkingLEDSM = Off;
	ThreeLEDsSM = B0;
	SpeakerSM = Mute;
	char button  = 0x00;
    /* Insert your solution below */
    while (1) {
	    button = ~PINA;
	if(speakerTime >=2){
		TickSpeaker(button);
		speakerTime = 0;
	}
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
	speakerTime += period;
	blinkLEDTime += period;
	threeLEDTime += period;
    }
    return 1;
}
