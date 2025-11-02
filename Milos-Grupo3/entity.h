#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "gameConstants.h"

//Entitys ou entidade s�o todos os personagens. Essa estrutura serve para o jogador, pro inimigo e para os npcs

//Struct da entity
typedef struct {
	ALLEGRO_BITMAP * sprite;
	int x;
	int y;
	int v;
	float vY;
	int width, height;
	int life;
	ALLEGRO_COLOR color;
	bool can_jump;
	bool modoAtaque; 
	bool modoDefesa;
	bool isDead;

}entity;


//fun��es da entity
entity newEntity(int x, int y, int v, float vY, ALLEGRO_COLOR color, const char* filename, bool can_jump);
void movEntity(entity* e, int dir);
void drawEntity(entity* e);
void draw_entity_with_camera(entity* p, int camera_x);
void draw_Enity_camera_andImage(entity* p, int camera_x, int flip);
void draw_Enity_camera_andImage_region(entity* e, int camera_x, int flip, int sx, int sy);
#endif // !ENTITY_H
