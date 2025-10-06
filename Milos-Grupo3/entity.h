#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "quad.h"

//Entitys ou entidade s�o todos os personagens. Essa estrutura serve para o jogador, pro inimigo e para os npcs

//Struct da entity
typedef struct {
	int x;
	int y;
	int v;
	float vY;
	int size;
	int life;
	ALLEGRO_COLOR color;
	quad q;
	bool can_jump;
	bool modoAtaque; 
	bool modoDefesa;
	bool isDead;

}entity;


//fun��es da entity
entity newEntity(int x, int y, int v, float vY, ALLEGRO_COLOR color, bool can_jump);
void movEntity(entity* e, int dir);
void drawEntity(entity* e);

#endif // !ENTITY_H
