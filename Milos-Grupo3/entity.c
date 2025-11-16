#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "entity.h"
#include "gameConstants.h"


entity newEntity(int x, int y, int v, float vY,ALLEGRO_COLOR color, const char* filename, bool can_jump) {
	entity e;
	e.sprite= al_load_bitmap(filename);
	if(!e.sprite){
		printf("Erro ao carregar a imagem %s\n", filename);
	}
	e.x = x;
	e.y = y;
	e.v = v;
	e.vY = vY;
	e.width = QUAD_SIZE;
	e.height = QUAD_SIZE*2;
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
	al_draw_filled_rectangle(e->x, e->y, e->x + e->width, e->y + e->height, e->color);
}


void draw_entity_with_camera(entity* p, int camera_x) {
    al_draw_filled_rectangle(p->x + camera_x, p->y,
        p->x + p->width+ camera_x, p->y + p->height, p->color);
}

void draw_Enity_camera_andImage(entity* e, int camera_x, int flip){
	al_draw_bitmap(e->sprite, e->x + camera_x, e->y, flip);
}

void draw_Enity_camera_andImage_region(entity* e, int camera_x, int flip, int sx, int sy){
	al_draw_bitmap_region(e->sprite, sx, sy, e->width, e->height, e->x + camera_x, e->y, flip);
}