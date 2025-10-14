#include "enemy.h"



entity enemyLoad(int x, int y) {


	entity enemy = newEntity(x - QUAD_SIZE, y, ENEMY_VELOCITY_0, 0, ENEMY_COLOR, "./imgs/sprites/player.png", true);
	return enemy;
}
