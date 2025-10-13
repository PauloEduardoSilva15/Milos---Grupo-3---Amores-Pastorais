#ifndef HUD_H
#define HUD_H


#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "gameConstants.h"
#include "lifeDisplay.h"

typedef struct{
    DisplayLife displayLife;
}hud;

//void newHud(int x);

// Função para desenhar o HUD
//void drawHud(void);

#endif // HUD_H