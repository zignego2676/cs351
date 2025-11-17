//Benjamin Zignego
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "craps.h"

/**
 * Usage: craps [OPTIONS] [NUMBER]
 * OPTIONS:
 *   NUMBER         Number of trials to run
 *   -h. --help     Show help
 */

int main(int argc, char **argv){
	if(argc > 2){
		fprintf(stderr, "\terror: too many arguments\n\tusage: ./craps [INTEGER]\n");
		exit(EXIT_FAILURE);
	}else if(argc == 2 && (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help"))){
		printf("Usage: craps [OPTIONS] [<INTEGER>]\n\nSimulate games of craps and view probabilities\n\n");
		printf("Options:\n");
		printf("  %-25s%s\n", "-h, --help", "Show this help message and exit\n");
		printf("Arguments:\n");
		printf("  %-25s%s\n", "INTEGER", "Specify the number of trials to run (INTEGER > 0)");
		return EXIT_SUCCESS;
	}

	srand(time(NULL));
	craps_t *p = new_craps();
	uint64_t arg = 100000;
	uint64_t suc = 0;
	double prob = 0;
	if(argc == 2){
		int ec = atoi(argv[1]); 
		if(!ec || ec < 0){
			fprintf(stderr, "\terror: invalid argument\n\tusage: ./craps [unsigned integer]\n");
			exit(EXIT_FAILURE);
		}
		arg = (uint64_t)ec;
	}
	
	for(uint64_t i = 0 ; i < arg ; i++ ){
		suc += (uint64_t)craps(p);
		p->point = 0;
	}	

	free(p);

	prob = (double)(suc) / (double)(arg);
	printf("Estimated probablity of winning: %lf (%ld trials)\n", prob, arg);
	return EXIT_SUCCESS;
}
