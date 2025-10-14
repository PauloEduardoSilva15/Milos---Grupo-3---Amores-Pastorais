#ifndef LIFEDISPLAY_H
#define LIFEDISPLAY_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "gameConstants.h"

typedef struct{
    int x, y, width, height;
    ALLEGRO_COLOR color;
}DisplayLife;

DisplayLife displayLifeLoad(int life);
void displayLifeDraw(DisplayLife * displayLife);

#endif // LIFEDISPLAY_H