#ifndef LEVEL001_H
#define LEVEL001_H

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

typedef struct {
    Tileset * tileset;
    Tilemap * map;
    entity player;
    entity npc;
    bool inDialogue;
    int dialogueOption;
    textBox dialogue;
    int cameraX;
    int cameraY;

}levelI;

levelI Level_I_load();
//void setColisionsOnMap(levelI l);
void level_I_Update(levelI * l, ALLEGRO_KEYBOARD_STATE * keystate);
void Level_I_Draw(levelI l, ALLEGRO_FONT* Font);

#endif // !LEVEL001_H
