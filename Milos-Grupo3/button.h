#ifndef BUTTON_H
#define BUTTON_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "gameConstants.h"

typedef struct {

	int x;
	int y;
	int w;
	int h;
	char text[16];
	ALLEGRO_FONT* font;
	ALLEGRO_COLOR color;
	ALLEGRO_COLOR font_color;

}button;

button newButton(int x, int y, char text[], ALLEGRO_FONT* font);

bool button_contains_point(button* q, int x, int y);

void drawButton(button * b);

#endif