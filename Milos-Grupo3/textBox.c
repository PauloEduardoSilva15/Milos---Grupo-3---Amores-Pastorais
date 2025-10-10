#include "textBox.h"


textBox dialogueLoad() {
	textBox dialogue;
	
	dialogue.x = 0;
	dialogue.y = 500;
	dialogue.width = SCREEN_WIDTH;
	dialogue.height = 100;
	
	dialogue.boxColor = DOR_COLOR;
	return dialogue;

}


void drawDialogue(textBox * text, ALLEGRO_FONT* font, int textOption) {
	text->font = font;
	text->dialogueOption = textOption;
	switch (textOption) {
	case 0:
		strcpy(text->personagem, "Homem Velho");
		strcpy(text->texto, "Olá pessoa, linda, bonita. Maravilhosa Errante.");
		break;
	case 1:
		strcpy(text->personagem, "Dirceu");
		strcpy(text->texto, "Olá pessoa, linda, bonita. Maravilhosa Bunda. ssssss");
	}

	al_draw_filled_rectangle(text->x, text->y, text->x + text->width, text->y + text->height, text->boxColor);
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 25, 0, text->personagem);
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 35, 0, text->texto);
}

