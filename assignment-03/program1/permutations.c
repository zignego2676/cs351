/* Benjamin Zignego */
/* 10/24/2025 */
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "permutations.h"

perm_t *permutations(char *word){
	if(strlen(word) > MAX_FACTORIAL){
		return NULL;
	}
	perm_t *p = malloc(sizeof(perm_t));
	p->word = strdup(word);
	p->num_permutations = factorial(strlen(p->word));

	// solve duplicate letters
	// 256 for ASCII table length, each index corresponds to the character code
	uint8_t frequency_list[256] = {0};
	for(uint8_t i = 0 ; i < strlen(p->word) ; i++){
		frequency_list[(unsigned char)p->word[i]]++;
	}

	uint64_t denominator = 1;
	for(uint16_t i = 0 ; i < 256 ; i++){
		denominator *= factorial(frequency_list[i]);
	}
	p->num_permutations /= denominator;

	p->permutations = malloc(sizeof(char *) * p->num_permutations);
	for(uint64_t i = 0 ; i < p->num_permutations ; i++){
		p->permutations[i] = malloc(sizeof(char) * strlen(p->word));
	}

	char *temp = NULL;
	uint8_t flag = 0;
	for(uint64_t i = 0 ; i < p->num_permutations ; i++){
		flag = 0;
		temp = permutate(p->word);
		for(uint64_t j = 0 ; j < i ; j++){
			if(!strcmp(temp, p->permutations[j])){
				flag = 1;
				i--;
				break;
			}
		}
		if(!flag){
			p->permutations[i] = strdup(temp);
		}
	}

	return p;
}

char *permutate(char *word){
	char *result = strdup(word);
	uint8_t length = strlen(result);
	for(uint8_t i = 0 ; i < length - 1 ; i++){
		// j is an int that is a random letter position between i and the end of the string
		uint8_t j = i + rand() % (length - i);
		char temp = result[i];
		result[i] = result[j];
		result[j] = temp;
	}
	return result;
	// return strfry(word); RIP strfry: it's not in the c standard string library....
}

uint64_t factorial(uint8_t num){
	if(num > MAX_FACTORIAL){
		// 64 bits can only handle up to 20!
		return 0;
	} else if(num == 0 || num == 1){
		return 1;
	}

	uint64_t result = num;
	for(uint8_t i = num - 1 ; i > 1 ; i--){
		result *= i;
	}

	return result;
}	
