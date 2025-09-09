#ifndef QUAD_H;
#define QUAD_H



typedef struct {
    int x;
    int y;
    int vel;
    int size;
} quad;

// Funções do quad
quad quad_create(int x, int y, int vel, int size);
void mov_quad(quad* p, int dir);
void draw_quad(quad* p);

#endif



