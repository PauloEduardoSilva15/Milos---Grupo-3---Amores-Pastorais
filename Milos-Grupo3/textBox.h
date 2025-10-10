#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "gameConstants.h"


typedef struct {
	ALLEGRO_FONT* font;
	int x, y;
	int width, height;
	int dialogueOption;
	ALLEGRO_COLOR boxColor;
}textBox;

textBox dialogueLoad(ALLEGRO_FONT* font);
void drawDialogue(textBox * text);

#endif // !TEXTBOX_H

