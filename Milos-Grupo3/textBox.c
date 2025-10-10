#include "textBox.h"


textBox dialogueLoad(ALLEGRO_FONT* font) {
	textBox dialogue;
	dialogue.font = font;
	dialogue.x = 0;
	dialogue.y = 400;
	dialogue.width = SCREEN_WIDTH;
	dialogue.height = 200;
	
	dialogue.boxColor = DOR_COLOR;
	return dialogue;

}


void drawDialogue(textBox * text, int textOption) {

	text->dialogueOption = textOption;
	switch (textOption) {
	case 0:
		strcpy(text->personagem, "Homem Velho");
		break;
	}

	al_draw_filled_rectangle(text->x, text->y, text->x + text->width, text->y + text->height, text->boxColor);
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->x + 25, 0, text->personagem);
}

