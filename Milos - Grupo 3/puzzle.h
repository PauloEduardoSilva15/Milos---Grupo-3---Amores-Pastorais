// puzzle.h
#ifndef PUZZLE_H
#define PUZZLE_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "quad.h"
#include "gameConstants.h"

typedef struct
{
	int x;
	int y;
	int size;
	int rotation;   // 0..3 (multiplo de 90 graus)
	int type;       // 0 = reto, 1 = cotovelo, 2 = T, 3 = cruz
}Pieces;

typedef struct {
	quad area;
	ALLEGRO_BITMAP* img;
	Pieces grid[GRID_ROWS][GRID_COLS];
}Puzzle;


void puzzle_init(void);
void puzzle_handle_event(ALLEGRO_EVENT* ev);
void puzzle_draw(int screen_w, int screen_h);
int puzzle_is_solved(void);
void puzzle_destroy(void);

#endif
