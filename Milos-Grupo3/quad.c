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

bool quad_contains_point(quad* q, int x, int y){
    return (x >= q->x && x <= q->x + q->w && y >= q->y && y <= q->y + q->h);
}

void draw_quad(quad* p) {
    al_draw_filled_rectangle(p->x, p->y, p->x + p->w, p->y + p->h, p->color);
}
