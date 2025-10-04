
#ifndef TITLEMENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include "quad.h"
#include "gameConstants.h"


typedef struct TitleMenu {
    ALLEGRO_BITMAP* bg;
    ALLEGRO_BITMAP* logo;

    //quad logo;
    ALLEGRO_FONT* font;
    quad startGameButton;
    quad exitButton;
    quad* selectedButton;
    int selectedOption; // 1 = Start Game, 2 = Exit
    bool runningLevel;
} TitleMenu;

TitleMenu createTitleMenu(ALLEGRO_FONT *font);



void drawTitleMenu(TitleMenu* menu, ALLEGRO_MOUSE_STATE* mouseState);


#endif // !TITLEMENU_H
