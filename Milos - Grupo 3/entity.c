#include "entity.h"
#include "quad.h"


entity newEntity(quad* q, int life) {
	entity Entity;
	Entity.q = q;
	Entity.life = life;
}