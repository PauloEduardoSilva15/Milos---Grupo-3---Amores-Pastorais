#ifndef ITEM_H
#define ITEM_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "gameConstants.h"
#include <stdbool.h>

typedef struct {
	int x;
	int y;
	int size;
	bool get;
	ALLEGRO_COLOR color;
}item;

item newItem(int x, int y, bool get);

void itemDraw(item* i);

#endif
