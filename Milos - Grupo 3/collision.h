#ifndef COLLISION_H
#define COLLISION_H

#include "quad.h"
#include "entity.h"
#include "item.h"
#include <stdbool.h>

bool collisionEQ(entity* a, quad* b);
bool collisionEI(entity* a, item* b);
bool collisionE(entity* a, entity* b);

#endif 

