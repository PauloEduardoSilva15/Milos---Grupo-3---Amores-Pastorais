#ifndef HUD_H
#define HUD_H


#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "lifeDisplay.h"
#include "item.h"

typedef struct{
    DisplayLife displayLife;
    bool getKey;
    item key;
   
}hud;

hud newHud(int life, bool getKey);

void drawHud(hud * hud);

#endif // HUD_H