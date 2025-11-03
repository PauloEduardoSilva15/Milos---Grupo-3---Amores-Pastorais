#ifndef ENEMY_H
#define ENEMY_H

#include "gameConstants.h"
#include "entity.h"

entity enemyLoad(int x, int y);

void enemyDraw(entity * enemy, int Camerax, int flip, int sX, int sY);

#endif