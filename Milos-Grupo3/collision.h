#ifndef COLLISION_H
#define COLLISION_H

#include "entity.h"
#include "item.h"
#include "marker.h"
#include "systemTileset.h"
#include "gameConstants.h"
#include "obstacle.h"
#include <stdbool.h>


bool collisionEntityObstacle(entity * a, obstacle* b);
bool collisionEntityMaker(entity* a, Marker* b);
bool collisionEntityWithEntity(entity* a, entity* b);

#endif 

