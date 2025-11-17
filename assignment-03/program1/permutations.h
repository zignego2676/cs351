/* Benjamin Zignego */
/* CS351 Assignment 3 */
/* 10/24/2025 */
#include <stdint.h>
#include <stdlib.h>

#define _GNU_SOURCE

typedef struct permutation_type{
	char *word;
	uint64_t num_permutations;
	char **permutations;
} perm_t;

constexpr uint8_t MAX_FACTORIAL = 20;

/* finds all unique permutations of a single word */
perm_t *permutations(char *word);

/* generate a single random permutation of a word */
/* seed srand before calling this */
char *permutate(char *word);

/* find the factorial of a given number */
/* limited to 20! as 64 bits can't handle any more */
/* returns 0 if num > 20 */
uint64_t factorial(uint8_t num);
