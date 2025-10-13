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
#include "gamePauseMenu.h"
#include "hud.h"
#include "marker.h"
#include "obstacle.h"

typedef struct {
    Tileset * tileset;
    Tilemap * map;
    entity player;
    entity npc;
    bool inDialogue;
    int dialogueOption;
    int dirPlayer; //Guarda a direção do player
    int PlayerFlip;
    textBox dialogue;
    //DisplayLife displayLife;
    obstacle door;
    int doorSpritePositionX, doorSpritePositionY;
    bool getKey;
    bool isDone; // verifica se terminou o level
    hud hud;
    Marker maker;
    PauseMenu pauseMenu;
    
    bool inPause;
    int cameraX;
    int cameraY;

}levelI;

levelI Level_I_load();
//void setColisionsOnMap(levelI l);
void level_I_Update(levelI * l, ALLEGRO_KEYBOARD_STATE * keystate);
void Level_I_Draw(levelI l, ALLEGRO_FONT* Font);

#endif // !LEVEL001_H
