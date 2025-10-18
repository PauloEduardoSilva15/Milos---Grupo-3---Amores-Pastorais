#ifndef MINIGAME_H
#define MINIGAME_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "button.h"
#include "gameConstants.h"

typedef struct {
    ALLEGRO_FONT* font;
    ALLEGRO_BITMAP * poema;
    button resposta1;
    button resposta2;
    button resposta3;
    int respostaMarcada;
    bool marcou;
    char texto[100];

}minigame;

minigame loadMinigame(ALLEGRO_FONT* font);
void drawMinigame(minigame * menu,  ALLEGRO_MOUSE_STATE* mouseState);

#endif // !MINIGAME_H


