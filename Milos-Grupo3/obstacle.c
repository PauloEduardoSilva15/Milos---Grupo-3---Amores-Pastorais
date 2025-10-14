#include "obstacle.h"

obstacle newObstacle(int x, int y, const char * filepath){
	obstacle ob;
	ob.sprite = al_load_bitmap(filepath);
	ob.x = x;
	ob.y = y;
	ob.width = QUAD_SIZE;
	ob.height = QUAD_SIZE*3;
	return ob;
}

void drawObstacle(obstacle *  obstacle, int cameraX, int positionSpriteX, int positionSpriteY){
	al_draw_bitmap_region(obstacle->sprite, positionSpriteX, positionSpriteY, obstacle->width, obstacle->height, obstacle->x + cameraX, obstacle->y, 0);
}