/* Benjamin Zignego */
/* 10/25/2025 */

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include "permutations.h"

int main(int argc, char **argv){
	char *word = "FALL";
	// blank pattern matches everything->will always succeed
	char *pinclude = "";
	// space pattern matches nothing in this case->will always fail
	char *pexclude = " ";
	// ^ allows us to skip some condtionals cause i wanted to ^
	char *perm;
	uint64_t successes = 0;
	uint64_t includes = 0;
	uint64_t excludes = 0;
	uint64_t trials = 10000;
	uint32_t *occurrence;
	int opt;
	while((opt = getopt(argc, argv, "w:i:e:t:h")) != -1){
		switch(opt){
			case 'w':
				word = strdup(optarg);
				break;
			case 'i':
				pinclude = strdup(optarg);
				break;
			case 'e':
				pexclude = strdup(optarg);
				break;
			case 't':
				trials = strtoll(optarg, NULL, 10);
				break;
			case 'h':
			default:
				printf("usage: ./permutations [options]\n"
						"\t-h\tdisplay this message and exit\n"
						"\t-w <string>\tword to use for permutations\n"
						"\t-i <string>\tpattern to match for in the permutation success counter\n"
						"\t-e <string>\tpattern to exclude in permutation success counter\n"
						"\t-t <int>\tnumber of trials to run\n");
				return EXIT_SUCCESS;
		}
	}

	srand(time(NULL));
	perm_t *p = permutations(word);

	printf("Base word: %s\nNumber of unique permutations: %ld\n", p->word, p->num_permutations);

	if(strcmp(pinclude, "") || strcmp(pexclude, " ")){
		// if there is either a non-default value for pinclude or strcmp
		for(uint64_t i = 0 ; i < trials ; i++){
			perm = permutate(p->word);
			successes += strstr(perm, pinclude) && !strstr(perm, pexclude);
			if(strstr(perm, pinclude)){
				includes++;
			}
			if(!strstr(perm, pexclude)){
				excludes++;
			}
		}

		if(strcmp(pinclude, "") && strcmp(pexclude, " ")){
			printf("Estimated number of permutations that include %s and exclude %s: %lu\n", pinclude, pexclude, successes);
		} else if(strcmp(pexclude, " ")){
			printf("Estimated number of permutations that exclude %s: %lu\n", pexclude, excludes);
			successes = trials - successes;
		} else if(strcmp(pinclude, "")){
			printf("Estimated number of permutations that include %s: %lu\n", pinclude, includes);
		}
		printf("(%lu successes in %lu trials; proportion: %.4f)\n", successes, trials, (double)successes/(double)trials);
	} else{
		occurrence = malloc(sizeof(uint32_t) * p->num_permutations);
		for(uint64_t i = 0 ; i < trials ; i++){
			perm = permutate(p->word);
			for(uint64_t j = 0 ; j < p->num_permutations ; j++){
				if(!strcmp(perm, p->permutations[j])){
					occurrence[j]++;
					break;
				}
			}
		}
		printf("Results from %ld trials:\n", trials);
		for(uint64_t i = 0 ; i < p->num_permutations ; i++){
			if(occurrence[i]){
				printf("\t%s\t:\t%u\n", p->permutations[i], occurrence[i]);
			}
		}
	}

	return EXIT_SUCCESS;
}
