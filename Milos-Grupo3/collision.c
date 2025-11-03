#include "collision.h"


bool collisionEntityObstacle(entity * a, obstacle* b) {
	return (a->x < b->x + b->width &&
		a->x + a->width > b->x &&
		a->y < b->y + b->height &&
		a->y + a->height > b->y);

}
bool collisionEntityMaker(entity* a, Marker* b) {
	return (a->x < b->x + b->size &&
		a->x + a->width > b->x &&
		a->y < b->y + b->size &&
		a->y + a->height > b->y);

}

bool collisionEntityWithEntity(entity* a, entity* b) {
	return (a->x < b->x + b->width &&
		a->x + a->width > b->x &&
		a->y < b->y + b->height &&
		a->y + a->height > b->y);

}
