#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "entity.h"
#include "gameConstants.h"
#include "quad.h"


entity newEntity(int x, int y, int v,ALLEGRO_COLOR color, bool isLiving) {
	entity e;
	e.x = x;
	e.y = y;
	e.v = v;
	e.size = QUAD_SIZE;
	e.color = color;
	e.isLiving = isLiving;
	return e;
}




void movEntity(entity* e, int dir) {

	switch (dir) {

	case 0: // A - esquerda
		e->x -= e->v;
		break;
	case 1: // D - direita
		e->x += e->v;
	}
}

void drawEntity(entity* e) {
	al_draw_filled_rectangle(e->x, e->y, e->x + e->size, e->y + e->size, e->color);
}