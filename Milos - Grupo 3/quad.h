#ifndef QUAD_H;
#define QUAD_H

#include <allegro5/allegro.h>

typedef struct {
    int x;
    int y;
    int vel;
    int size;
    ALLEGRO_COLOR color;
} quad;

// Funções do quad
quad quad_create(int x, int y, int vel, int size, ALLEGRO_COLOR color);
void mov_quad(quad* p, int dir);
void draw_quad(quad* p);

#endif



