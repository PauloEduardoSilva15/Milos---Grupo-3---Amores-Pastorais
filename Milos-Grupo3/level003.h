#ifndef LEVEL003_H
#define LEVEL003_H

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
    Tileset * tileset;
    Tilemap * map;

    entity player;
    int cameraX;
    int cameraY;
	int playerSpritepositionX, playerSpritepositionY;
	int playerflip;
    bool isDone;
    bool inPause;
    //hud hud;

}levelIII;

levelIII Level_III_load();
void level_III_Update(levelIII* l, ALLEGRO_KEYBOARD_STATE* keystate);
void Level_III_Draw(levelIII l, ALLEGRO_FONT* Font);

#endif // !LEVEL003_H
