#include "enemy.h"



entity enemyLoad(int x, int y) {


	entity enemy = newEntity(x - QUAD_SIZE, y, ENEMY_VELOCITY_0, 0, ENEMY_COLOR, "./imgs/sprites/guard.png", true);
	return enemy;
}

void enemyDraw(entity * enemy, int Camerax, int flip, int sX, int sY){
	
	al_draw_bitmap_region(enemy->sprite, sX, sY, enemy->width, enemy->height, enemy->x +Camerax, enemy->y, flip);
}