#include "collision.h"


bool collisionEQ(entity * a, quad* b) {
	return (a->x < b->x + b->w &&
		a->x + a->size > b->x &&
		a->y < b->y + b->h &&
		a->y + a->size > b->y);

}

bool collisionEI(entity* a, item* b) {
	return (a->x < b->x + b->size &&
		a->x + a->size > b->x &&
		a->y < b->y + b->size &&
		a->y + a->size > b->y);

}

bool collisionEM(entity* a, Marker* b) {
	return (a->x < b->x + b->size &&
		a->x + a->size > b->x &&
		a->y < b->y + b->size &&
		a->y + a->size > b->y);

}

bool collisionEntityWithEntity(entity* a, entity* b) {
	return (a->x < b->x + b->size &&
		a->x + a->size > b->x &&
		a->y < b->y + b->size &&
		a->y + a->size > b->y);

}
