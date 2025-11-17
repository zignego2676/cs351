/* Benjamin Zignego */
/* 10/25/2025 */

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "coinflips.h"

int main(int argc, char **argv){
	int opt;
	uint8_t result;
	uint8_t num = 10;
	uint8_t width = 20;
	uint8_t successes = 0;
	uint64_t trials = 10000;
	uint64_t *occurrences;
	double probability = 0.5;
	while((opt = getopt(argc, argv, "n:p:t:w:h")) != -1){
		switch(opt){
			case 'n':
				num = (uint8_t)strtol(optarg, NULL, 10);
				if(num > 99){
					fprintf(stderr, "error: invalid value for num\n usage:\t./coinflips -w <0 < num < 100>\n");
					exit(EXIT_FAILURE);
				}
					break;
			case 'w':
				width = (uint8_t)strtol(optarg, NULL, 10);
				break;
			case 'p':
				probability = strtod(optarg, NULL);
				break;
			case 't':
				trials = strtoll(optarg, NULL, 10);
				break;
			case 'h':
			default:
				printf("usage: ./coinflips [options]\n"
						"\t-h\tdisplay this message and exit\n"
						"\t-w <int>\twidth of the histogram in characters\n"
						"\t-n <int>\tnumber of coin flips per trial\n"
						"\t-p <double>\tprobability of getting heads on a single flip\n"
						"\t-t <int>\tnumber of trials to run\n");
				return EXIT_SUCCESS;
		}
	}

	srand(time(NULL));
	printf("Analyzing runs in sequences of length %hu with p = %.6f\n", num, probability);

	occurrences = malloc(sizeof(uint64_t) * (num + 1));

	for(uint64_t i = 0 ; i < trials ; i++){
		result = coinflip(probability);
		uint8_t max = 1;
		for(uint8_t j = 0 ; j < num ; j++){
			uint8_t temp = coinflip(probability);
			if(result == temp){
				successes++;
			} else{
				if(successes > max){
					max = successes;
				}
				successes = 1;
				result = temp;
			}
		}
		if(successes > max){
			max = successes;
		}
		// you would not believe how long it took me to properly reset successes
		successes = 0;
		occurrences[max]++;
	}

	for (uint8_t i = 1; i <= num; i++) {
		double proportion = (double)occurrences[i] / (double)trials;
		double scale = proportion * width;
		uint8_t num_hashes = (uint8_t)floor(scale);
		double leftover = scale - (double)num_hashes;
		printf("Est.Prob.(MaxRunLength = %hu): %.6f|", i, proportion);
		for(uint8_t j = 0 ; j < num_hashes ; j++){
			printf("#");
		}
		if(leftover >= 0.5){
			printf("=");
		} else if(leftover >= 0.05){
			printf("-");
		}
		printf("\n");
	}	

	return EXIT_SUCCESS;
}
