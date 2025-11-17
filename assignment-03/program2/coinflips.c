/* Benjamin Zignego */
/* 10/14/2025 */

#include <stdint.h>
#include <stdlib.h>
#include "coinflips.h"

uint8_t coinflip(double prob){
	return (double)rand() / RAND_MAX < prob ? HEADS : TAILS; 
}
