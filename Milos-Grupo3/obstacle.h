#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "gameConstants.h"
//#include "quad.h"

typedef struct{
    ALLEGRO_BITMAP * sprite;
    int x, y, width, height;
}obstacle;

obstacle newObstacle(int x, int y, const char * filepath);

void drawObstacle(obstacle *  obstacle, int cameraX, int positionSpriteX, int positionSpriteY);


#endif // !1

