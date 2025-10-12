#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "entity.h"
#include "gameConstants.h"
#include "quad.h"


entity newEntity(int x, int y, int v, float vY,ALLEGRO_COLOR color, bool can_jump) {
	entity e;
	e.x = x;
	e.y = y;
	e.v = v;
	e.vY = vY;
	e.size = QUAD_SIZE;
	e.life = MAXLIFE_0;
	e.color = color;
	e.can_jump = can_jump;
	e.modoAtaque = false;
	e.modoDefesa = false;
	e.isDead = false;
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


void draw_entity_with_camera(entity* p, int camera_x) {
    al_draw_filled_rectangle(p->x + camera_x, p->y,
        p->x + p->size + camera_x, p->y + p->size, p->color);
}
