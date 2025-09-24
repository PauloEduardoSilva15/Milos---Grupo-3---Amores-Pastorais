#ifndef LEVEL_H
#define LEVEL_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "quad.h"
#include "entity.h"
#include "obstacle.h"
#include "item.h"
#include "enemy.h"
#include "player.h"


typedef struct {
	entity p;
	entity e;
	quad f;
	quad d;
	item k;
}level;


level level_Load();

void level_Update(level* l, ALLEGRO_KEYBOARD_STATE* keyState);

void Level_Draw(level l);


#endif // !1


