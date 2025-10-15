#ifndef MINIGAME_H
#define MINIGAME_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "button.h"

typedef struct {
    ALLEGRO_FONT* font;
    button resposta1;
    button resposta2;
    button resposta3;

}minigame;

minigame loadMinigame(ALLEGRO_FONT* font);
void drawMinigame;

#endif // !MINIGAME_H


