#include "player.h"


quad playerQuad(){
	return quad_create((SCREEN_WIDTH / 2) - 32, 300, 5, 32, 32, 100, al_map_rgb(0, 0, 255));
}



entity player_load() {
	quad player_quad = playerQuad();
	newEntity(&player_quad, 100);
}