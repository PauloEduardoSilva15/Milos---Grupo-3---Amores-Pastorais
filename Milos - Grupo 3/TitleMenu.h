
#ifndef TITLEMENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "quad.h"
#include "gameConstants.h"


typedef struct TitleMenu {
    //ALLEGRO_BITMAP* background;
    //quad logo;
    ALLEGRO_FONT* font;
    quad startGameButton;
    quad exitButton;
    int selectedOption; // 0 = Start Game, 1 = Exit
    bool runningLevel;
} TitleMenu;

TitleMenu createTitleMenu(ALLEGRO_FONT *font);

void leverlReturn(TitleMenu menu, ALLEGRO_MOUSE_STATE * mouseState);

void drawTitleMenu(TitleMenu* menu);


#endif // !TITLEMENU_H
