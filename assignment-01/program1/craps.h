// Benjamin Zignego
#include <stdint.h>

typedef struct craps_type {
	uint8_t point;
	uint8_t tempRoll;
} craps_t;

craps_t *new_craps();
uint8_t roll();
uint8_t craps(craps_t *);
