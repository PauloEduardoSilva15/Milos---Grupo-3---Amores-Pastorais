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

void applyGravity(entity* e, float gravity) {
    if (e->can_jump == false) { // A gravidade só age quando o jogador está no ar
        e->vY += gravity;
    }
}

// Inicia o pulo, alterando a velocidade vertical e o estado de pulo
void jumpEntity(entity* e, float jump_velocity) {
    if (e->can_jump) {
        e->vY = jump_velocity; // jump_velocity deve ser negativo
        e->can_jump = false;
    }
}

// Aplica a velocidade vertical (vY) à posição y da entidade
void updateEntityY(entity* e) {
    e->y += (int)e->vY;
}