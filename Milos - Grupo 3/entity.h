#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "quad.h"

typedef struct {
	int x;
	int y;
	int v;
	int size;
	int life;
	ALLEGRO_COLOR color;
	quad q;
	bool isLiving;

}entity;



entity newEntity(int x, int y, int v, ALLEGRO_COLOR color, bool osLiving);


void movEntity(entity* e, int dir);

void drawEntity(entity* e);

#endif // !ENTITY_H
