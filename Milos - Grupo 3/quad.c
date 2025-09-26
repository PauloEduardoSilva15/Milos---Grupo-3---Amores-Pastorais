#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "quad.h"



quad quad_create(int x, int y, int v, int w, int h, ALLEGRO_COLOR color) {

    quad p;
    p.x = x;
    p.y = y;
    p.v = v;
    p.w = w;
    p.h = h;
    p.color = color;
    return p;
}


void draw_quad(quad* p) {
    al_draw_filled_rectangle(p->x, p->y, p->x + p->w, p->y + p->h, p->color);
}
