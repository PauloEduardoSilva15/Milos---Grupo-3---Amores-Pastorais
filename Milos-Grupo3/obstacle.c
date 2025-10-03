#include "obstacle.h"

quad obstacleLoad() {
	quad obstacle = quad_create(DOR_X, DOR_Y_0, DOR_VELOCITY_0, QUAD_SIZE, DOOR_HEIGHT, DOR_COLOR);
	return obstacle;
}