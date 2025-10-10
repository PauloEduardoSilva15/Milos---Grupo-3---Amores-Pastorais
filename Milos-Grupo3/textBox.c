#include "textBox.h"


textBox dialogueLoad(ALLEGRO_FONT* font) {
	textBox dialogue;
	dialogue.font = font;
	dialogue.x = 0;
	dialogue.y = 400;
	dialogue.width = SCREEN_WIDTH;
	dialogue.height = 200;
	dialogue.dialogueOption = 0;
	dialogue.boxColor = DOR_COLOR;
	return dialogue;

}


void drawDialogue(textBox * text) {
	al_draw_filled_rectangle(text->x, text->y, text->x + text->width, text->y + text->height, text->boxColor);
}

