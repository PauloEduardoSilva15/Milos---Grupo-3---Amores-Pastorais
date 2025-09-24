#include "player.h"


entity playerLoad() {
	entity player = newEntity(PLAYER_X_0, PLAYER_Y_0, PLAYER_VELOCITY_0, 0, PLAYER_NORMAL_COLOR, true);
	return player;
}