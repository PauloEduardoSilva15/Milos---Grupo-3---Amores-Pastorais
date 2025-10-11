#ifndef LEVEL_H
#define LEVEL_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "quad.h"
#include "entity.h"
#include "obstacle.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "marker.h"
#include "textBox.h"


typedef struct {
	entity p; //player
	entity e; // inimigo
	entity npc; // npc
	quad f; // chão ou floor
	quad d; // porta ou door
	quad dL; // display life
	item k; // key ou chave
	Marker m; // maker
	textBox textBox; // caixa de texto
	int dialogueOption;
	bool inDialogue;
	bool puzzle_open;
	bool puzzle_solved;
	bool show_interact_text;  // Nova flag para mostrar texto de interação
	bool dialogoTermindado;
}level;


level level_Load();

void level_Update(level* l, ALLEGRO_KEYBOARD_STATE * keyState, ALLEGRO_EVENT* ev);

void Level_Draw(level l, ALLEGRO_FONT* Font);


#endif 


