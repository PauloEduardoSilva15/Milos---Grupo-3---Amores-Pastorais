#include "enemy.h"



entity enemyLoad() {


	entity enemy = newEntity(ENEMY_X_0 - QUAD_SIZE, ENEMY_Y_0, ENEMY_VELOCITY_0, 0, ENEMY_COLOR, true);
	return enemy;
}

