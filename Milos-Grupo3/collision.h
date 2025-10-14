#ifndef COLLISION_H
#define COLLISION_H

#include "quad.h"
#include "entity.h"
#include "item.h"
#include "marker.h"
#include "systemTileset.h"
#include "gameConstants.h"
#include "obstacle.h"
#include <stdbool.h>

bool collisionEQ(entity* a, quad* b);
bool collisionEI(entity* a, item* b);
bool collisionEntityObstacle(entity * a, obstacle* b);
bool collisionEntityMaker(entity* a, Marker* b);
bool collisionEntityWithEntity(entity* a, entity* b);

#endif 

