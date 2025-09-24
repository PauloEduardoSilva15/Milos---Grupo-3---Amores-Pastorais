#ifndef LEVEL_H
#define LEVEL_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "quad.h"
#include "entity.h"
#include "player.h"

typedef struct {
	entity p;
}level;


level level_Load();

void Level_Draw(level l);


#endif // !1


