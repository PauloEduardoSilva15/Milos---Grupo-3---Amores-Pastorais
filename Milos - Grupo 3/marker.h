#ifndef MARKER_H
#define MARKER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "gameConstants.h"
#include <stdbool.h>

typedef struct {
	int x;
	int y;
	int size;
	ALLEGRO_COLOR color;
}Marker;

Marker newMarker(int x, int y);

void MarkerDraw(Marker* m);

#endif
