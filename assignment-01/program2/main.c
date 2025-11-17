#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "chutesandladders.h"
/**
 * Usage: craps [OPTIONS] [NUMBER]
 * OPTIONS:
 *   NUMBER         Number of trials to run
 *   -h. --help     Show help
 */

int main(int argc, char **argv){

	if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")){
		printf("Usage: chutesandladders [OPTIONS] <FILEPATH>\n\nSimulate games of chutes and ladders and view probabilities\n\n");
		printf("Options:\n");
		printf("  %-25s%s\n", "-h, --help", "Show this help message and exit");
		printf("  %-25s%s\n", "-t, --trials <NUMBER>", "Specify the number of trials to run (NUMBER > 0)");
		printf("  %-25s%s\n", "-p, --players <NUMBER>", "Specify the number of players (0 < NUMBER < 10)");
		printf("\n");
		printf("Arguments:\n");
		printf("  %-25s%s\n", "<FILEPATH>", "Specify the file to be used for the board specifications");
		return EXIT_SUCCESS;
	}

	if(argc < 2 || argc > 7){
		fprintf(stderr, "error: invalid number of arguments.\nusage:\t./chutesandladders -f <filepath> [-t] [int] [-p] [int]\n");
		exit(EXIT_FAILURE);
	}
	uint8_t players = 1; 
	uint64_t trials = 10000;
	char *file = NULL;
	srand(time(NULL));

	// i realize now that getopt exists, i'll use it in the future i don't wanna change this now
	for(uint8_t i = 0 ; i < argc ; i++){
		if(!strcmp(argv[i], "-t") || !strcmp(argv[i], "--trials")){
			trials = (uint32_t)atoi(argv[i + 1]);
			if(!trials){
				fprintf(stderr, "error: invalid trial value.\nusage:\t-q <int > 0>\n");
				exit(EXIT_FAILURE);
			}
		} else if(!strcmp(argv[i], "-p") || !strcmp(argv[i], "--players")){
			players = (uint8_t)atoi(argv[i + 1]);
			if(!players || players > 10 || players < 1){
				fprintf(stderr, "error: invalid players value.\nusage:\t-p <1-10>\n");
				exit(EXIT_FAILURE);
			}
		} else if (!atoi(argv[i])){
			file = argv[i];
		}
	}

	FILE *fp = fopen(file, "r");
	if(fp == NULL){
		fprintf(stderr, "error: invalid filepath.\n");
		exit(EXIT_FAILURE);
	}
	uint64_t boardsize = 0;
	// slow ass way to do this file i/o
	// should probably use a buffer
	char *readline = malloc(sizeof(char) * 41);
	if(readline == NULL){
		fprintf(stderr, "error: main.c readline malloc failed.\n");
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_SET);
	fgets(readline, 20, fp);
	boardsize = (uint64_t)atoi(readline);
	if(!boardsize){
		fprintf(stderr, "error: invalid boardsize.\n");
		exit(EXIT_FAILURE);
	}

	uint64_t numcal = 0;
	char c;
	for (c = getc(fp) ; c != EOF ; c = getc(fp)){
		if (c == '\n'){ 
			numcal++;
		}
	}

	uint64_t **cal = malloc(sizeof(uint64_t) * numcal);
	if(cal == NULL){
		fprintf(stderr, "error: main.c initial cal list malloc failed.\n");
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_SET);
	fgets(readline, 20, fp);
	uint64_t i = 0;
	while(i < numcal && fgets(readline, 41, fp) != NULL){
		cal[i] = malloc(sizeof(uint64_t *) * 2);
		sscanf(readline, "%" SCNu64 " %" SCNu64, &cal[i][0], &cal[i][1]);
		i++;
	}

	cal_t *calg = new_chutesandladders(players, boardsize, cal, numcal);
	free(cal);	
	free(readline);

	double *winProb = malloc(sizeof(double) * calg->numPlayers);
	double rollsNeeded = 0;
	for(i = 0 ; i < trials ; i++){	
		uint64_t *result = chutesandladders(calg);
		winProb[result[PLAYER]]++;
		rollsNeeded += result[ROLLS];
		reset_chutesandladders(calg);
	}

	rollsNeeded /= trials;
	printf("Average number of die rolls in a game: %f (%ld trials)\n", rollsNeeded, trials);
	for(i = 0 ; i < calg->numPlayers ; i++){
		winProb[i] /= trials;
		printf("Estimated probability of player %d winning: %f\n", (uint8_t)i + 1, winProb[i]);
	}
	delete_chutesandladders(calg);

	return EXIT_SUCCESS;
}
