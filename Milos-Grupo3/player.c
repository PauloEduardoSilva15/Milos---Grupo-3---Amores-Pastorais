#include "player.h"


entity playerLoad() {
	
	
	entity player = newEntity(PLAYER_X_0, PLAYER_Y_0, PLAYER_VELOCITY_0, PLAYER_VELOCITY_Y_0, PLAYER_NORMAL_COLOR, "./imgs/sprites/player.png", true);
	return player;
}


void playerDraw(entity * player, int Camerax, int flip){
	
	al_draw_bitmap_region(player->sprite, 0, 0, player->width, player->height, player->x +Camerax, player->y, flip);
}