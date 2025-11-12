#ifndef HUD_H
#define HUD_H


#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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

void drawHud(hud * hud, ALLEGRO_FONT * Font);

#endif // HUD_H