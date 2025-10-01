#include "item.h"


item newItem(int x, int y, bool get) {
	item i;
	i.x = x;
	i.y = y;
	i.size = ITENS_QUAD_SIZE;
	i.color = KEY_ITEM_COLOR;
	i.get = get;
	return i;
}

void itemDraw(item* i) {
	al_draw_filled_rectangle(i->x, i->y, i->x + i->size, i->y + i->size, i->color);
}