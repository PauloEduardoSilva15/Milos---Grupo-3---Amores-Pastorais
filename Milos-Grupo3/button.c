#include "button.h"


button newButton(int x, int y, char text, ALLEGRO_FONT * font) {
	button b;
	b.x = x;
	b.y = y;
	b.w = BUTTON_X;
	b.h = QUAD_SIZE;
	b.text = text;
	b.font = font;
	b.color = BUTTON_COLOR_NORMAL;
	b.font_color = TEXT_COLOR;

}

bool button_contains_point(button* b, int x, int y) {
	return (x >= b->x && x <= b->x + b->w && y >= b->y && y <= b->y + b->h);
}

void drawButton(button * b) {
	al_draw_text(b->font, b->font_color, (b->x + b->w) / 2, (b->y + b->h) / 2, ALLEGRO_ALIGN_CENTER, b->text);
	al_draw_filled_rectangle(b->x, b->y, b->x + b->w, b->y + b->h, b->color);
}