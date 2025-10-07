#ifndef LEVEL001_H
#define LEVEL001_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "gameConstants.h"
#include "entity.h"
#include "player.h"
#include "systemTileset.h"

typedef struct {
    Tileset * tileset;
    Tilemap * map;
    entity player;
    int cameraX;
    int cameraY;

}levelI;

levelI Level_I_load();
//void setColisionsOnMap(levelI l);
void level_I_Update(levelI * l, ALLEGRO_KEYBOARD_STATE * keystate);
void Level_I_Draw(levelI l);

#endif // !LEVEL001_H
