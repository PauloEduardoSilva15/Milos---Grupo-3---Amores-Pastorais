#include "level.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "quad.h"
#include "entity.h"
#include "player.h"



level level_Load() {
	level teste;
	teste.p = playerLoad(); //newEntity(PLAYER_X_0, PLAYER_Y_0, PLAYER_VELOCITY_0, 0, PLAYER_NORMAL_COLOR, true);
	return teste;
}


void Level_Draw(level l) {
	
	drawEntity(&l.p);
}