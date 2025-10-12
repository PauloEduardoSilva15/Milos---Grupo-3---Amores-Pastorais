#ifndef GAMEPAUSEMENU_H
#define GAMEPAUSEMENU_H


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "button.h"
#include "gameConstants.h"


typedef struct{

    button ContinuePlaybutton;
    button retriviedbutton;
    button exitButton;
    //int selectedOption; // 1 = Start Game, 2 = Exit
    //bool runningLevel;
} PauseMenu;

PauseMenu createPauseMenu(ALLEGRO_FONT* font);



void drawPauseMenu(PauseMenu* menu, ALLEGRO_MOUSE_STATE* mouseState);


#endif