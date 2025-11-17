#include <stdint.h>
#include <stdlib.h>

typedef struct calplayer_type {
	uint64_t position;
	uint8_t tempRoll;
} calp_t;

typedef struct chutesandladders_type {
	uint8_t numPlayers;
	uint64_t numRolls;
	uint64_t goal;
	uint64_t **chutesandladders;
	uint64_t lengthCal;
	calp_t **players;
} cal_t;

constexpr uint8_t ROLLS = 0;
constexpr uint8_t PLAYER = 1;

cal_t *new_chutesandladders(uint8_t, uint64_t, uint64_t **, uint64_t);
calp_t *new_calplayer();
void delete_chutesandladders(cal_t *);
uint8_t roll();
uint64_t *chutesandladders(cal_t *);
void reset_chutesandladders(cal_t *);
