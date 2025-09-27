#ifndef QUAD_H
#define QUAD_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

//Quads são todos os elementos que podem ser interativos ou não, mas que precisam ser desenhados na tela

//Struct do quad
typedef struct {
    int x;
    int y;
    int v;
    int w;
    int h;
    ALLEGRO_COLOR color;
} quad;

// Funções do quad
quad quad_create(int x, int y, int v, int w, int h, ALLEGRO_COLOR color);
void draw_quad(quad* p);

#endif