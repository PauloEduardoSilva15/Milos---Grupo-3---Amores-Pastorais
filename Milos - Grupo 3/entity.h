#ifndef ENTITY_H
#define ENTITY_H

#include "quad.h"

typedef struct {
	quad* q;
	int life;
}entity;



entity newEntity(quad* q, int life);

#endif // !ENTITY_H
