#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define SCREEN_WIDTH 800 // Largura da Janela
#define SCREEN_HEIGHT 600 // Altura da Janela
#define FPS 60

#define QUAD_SIZE 32 // As artes do jogo será no padrão 32bits -> 32x32p pixels
#define ITENS_QUAD_SIZE (QUAD_SIZE/2)// As artes dos itens jogo será no padrão 16bits -> 16x16 pixels
#define MAXLIFE_0 100 /// Maximo de vida que toda entidade pode ter

#define PLAYER_GRAVIDADE 1.0;

#define PLAYER_X_0 (SCREEN_WIDTH / 2) - QUAD_SIZE
#define PLAYER_Y_0 (SCREEN_HEIGHT / 2) - QUAD_SIZE
#define PLAYER_VELOCITY_0 5
#define PLAYER_VELOCITY_Y_0 0
#define PLAYER_JUMP_FORCE -15.0
#define PLAYER_NORMAL_COLOR  al_map_rgb(0, 0, 255)
#define PLAYER_ATACK_COLOR  al_map_rgb(100, 0, 200)
#define PLAYER_DEFENSE_COLOR  al_map_rgb(180, 0, 200);
#define PLAYER_ATACK_DAMAGE 2

#define ENEMY_GRAVIDADE 5;
#define ENEMY_X_0 (SCREEN_WIDTH - 30) - QUAD_SIZE
#define ENEMY_Y_0 (SCREEN_HEIGHT / 2) 
#define ENEMY_VELOCITY_0 3
#define ENEMY_COLOR  al_map_rgb(255, 0, 0)
#define ENEMY_ATACK_DAMAGE 1


#define KEY_ITEM_X (SCREEN_WIDTH - 700)
#define KEY_ITEM_Y_0  (SCREEN_HEIGHT / 2) + 184
#define KEY_ITEM_COLOR  al_map_rgb(255, 255, 0)


#define DOR_X (SCREEN_WIDTH - 200) - QUAD_SIZE
#define DOR_Y_0 (SCREEN_HEIGHT / 2) 
#define DOOR_HEIGHT 200
#define DOR_VELOCITY_0 50
#define DOR_COLOR  al_map_rgb(150, 50, 0)




#endif