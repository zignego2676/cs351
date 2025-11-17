#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "chutesandladders.h"

cal_t *new_chutesandladders(uint8_t numPlayers, uint64_t goal, uint64_t **chutesladders, uint64_t lengthCal){
	cal_t *this = malloc(sizeof(cal_t));
	if(this == NULL){
		fprintf(stderr, "error: chutesandladders.c malloc of cal_t struct failed.\n");
		exit(EXIT_FAILURE);
	}
	this->numPlayers = numPlayers;
	this->goal = goal;
	this->lengthCal = lengthCal;
	this->numRolls = 0;

	this->chutesandladders = malloc(sizeof(uint64_t *) * lengthCal);
	if(this->chutesandladders == NULL){
		fprintf(stderr, "error: chutesandladders.c failed malloc of chutesandladders list.\n");
		exit(EXIT_FAILURE);
	}
	for(uint64_t i = 0 ; i < this->lengthCal ; i++){
		this->chutesandladders[i] = malloc(sizeof(uint64_t *) * 2);
		memcpy(this->chutesandladders[i], chutesladders[i], sizeof(uint64_t) * 2);	
	}

	this->players = malloc(sizeof(calp_t *) * numPlayers);
	for(int i = 0 ; i < numPlayers ; i++){
		this->players[i] = new_calplayer();
	}
	return this;
}

calp_t *new_calplayer(){
	calp_t *this = malloc(sizeof(calp_t));
	this->tempRoll = 0;
	this->position = 0;
	return this;
}

void delete_chutesandladders(cal_t *this){
	for(uint64_t i = 0 ; i < this->lengthCal ; i++){
		free(this->chutesandladders[i]);
	}
	free(this->chutesandladders);
	for(uint64_t i = 0 ; i < this->numPlayers ; i++){
		free(this->players[i]);
	}
	free(this->players);
	free(this);
}

uint8_t roll(){
	return (uint8_t)((rand() % 6) + 1);
}

uint64_t *chutesandladders(cal_t *this){
	while(true){
		for(uint8_t i = 0 ; i < this->numPlayers ; i++){
			//printf("It is player %d's turn\n", i);
			this->players[i]->tempRoll = roll();
			//printf("They rolled %d\n", this->players[i]->tempRoll);
			this->numRolls++;
			if(this->players[i]->position + this->players[i]->tempRoll <= this->goal){
				this->players[i]->position += this->players[i]->tempRoll;
			}
			//printf("They are now at postion %ld\n", this->players[i]->position);
			if(this->players[i]->position == this->goal){
				uint64_t *result = malloc(sizeof(uint64_t) * 2);
				result[0] = this->numRolls;
				result[1] = i;
				return result;
			}
			for(uint64_t j = 0; j < this->lengthCal ; j++){
				if(this->chutesandladders[j][0] == this->players[i]->position){
					this->players[i]->position = this->chutesandladders[j][1];
					//printf("They have hit a chute/ladder. New position: %ld\n", this->players[i]->position);
					break;
				}
			}
			//printf("------------------------------------\n");
		}
	}
	// This should be impossible to hit but it'll be here in case
	return 0;
}

void reset_chutesandladders(cal_t *this){
	for(uint8_t i = 0 ; i < this->numPlayers ; i++){
		this->players[i]->position = 0;
		this->players[i]->tempRoll = 0;
		this->numRolls = 0;
	}
}
