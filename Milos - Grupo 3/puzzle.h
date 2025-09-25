// puzzle.h
#ifndef PUZZLE_H
#define PUZZLE_H

#include <allegro5/allegro5.h>

void puzzle_init(void);
void puzzle_handle_event(ALLEGRO_EVENT* ev);
void puzzle_draw(int screen_w, int screen_h);
int puzzle_is_solved(void);
void puzzle_destroy(void);

#endif
