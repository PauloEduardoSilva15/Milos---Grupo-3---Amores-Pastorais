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
	char personagem[20];
	char texto[100];
	ALLEGRO_COLOR boxColor;
}textBox;

textBox dialogueLoad();
void drawDialogue(textBox * text, ALLEGRO_FONT* font, int textOption);

#endif // !TEXTBOX_H


