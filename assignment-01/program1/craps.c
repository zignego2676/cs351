// Benjamin Zignego
#include <stdlib.h>
#include <stdint.h>
#include "craps.h"

craps_t *new_craps(){
	craps_t *p = malloc(sizeof(craps_t));	
	p->point = 0;
	p->tempRoll = 0;
	return p;
}

uint8_t roll(){
	// not a uniform generation
	return (uint8_t)((rand() % 6) + 1);
}

uint8_t craps(craps_t *p){
	p->tempRoll = roll() + roll();
	if(!p->point){
		if(p->tempRoll == 7 || p->tempRoll == 11){
			return 1;
		} else if(p->tempRoll == 2 || p->tempRoll == 3 || p->tempRoll == 12){
			return 0;
		}
		p->point = p->tempRoll;
	} else{
		if(p->tempRoll == 7){
			return 0;
		} else if(p->tempRoll == p->point){
			return 1;
		}
	}
	return craps(p);
}
