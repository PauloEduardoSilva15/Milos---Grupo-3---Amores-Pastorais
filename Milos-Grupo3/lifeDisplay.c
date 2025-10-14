#include "lifeDisplay.h"

DisplayLife displayLifeLoad(int life){
    DisplayLife displayLife;
    displayLife.x = DISPLAY_LIFE_X;
    displayLife.y = DISPLAY_LIFE_Y;
    displayLife.width = life;
    displayLife.height = QUAD_SIZE;
    displayLife.color = DISPLAY_LIFE_COLOR;
    return displayLife;

}


void displayLifeDraw(DisplayLife * displayLife){
    al_draw_filled_rectangle(displayLife->x, displayLife->y,
        displayLife->x + displayLife->width, displayLife->y + displayLife->height, displayLife->color);
}