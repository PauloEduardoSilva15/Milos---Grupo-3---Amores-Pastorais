#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "quad.h"


quad quad_create(int x, int y, int vel, int size, ALLEGRO_COLOR color) {
    quad p;
    p.x = x;
    p.y = y;
    p.vel = vel;
    p.size = size;
    p.color = color;
    return p;
}

void mov_quad(quad* p, int dir) {
    switch (dir) {

    case 0: // A - esquerda
        p->x -= p->vel;
        break;
    case 1: // D - direita
        p->x += p->vel;
        break;
    case 2:
		p->y -= p->vel;
        break;
    }
}

void draw_quad(quad* p) {
    al_draw_filled_rectangle(p->x, p->y, p->x + p->size, p->y + p->size, p->color);
}
