#ifndef LEVEL002_H
#define LEVEL002_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "gameConstants.h"
#include "collision.h"
#include "entity.h"
#include "player.h"
#include "systemTileset.h"
#include "textBox.h"
#include "gamePauseMenu.h"
#include "hud.h"
#include "marker.h"
#include "obstacle.h"
#include "enemy.h"

typedef struct {

	entity Player;

}levelII;

levelII Level_II_load();
void level_II_Update(levelII* l, ALLEGRO_KEYBOARD_STATE* keystate);
void Level_II_Draw(levelII l, ALLEGRO_FONT* Font);

#endif // !LEVEL002_H
