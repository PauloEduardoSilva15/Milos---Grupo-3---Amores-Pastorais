#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>


#define TITLE "Pastoral Loves" // Titulo da Janela
#define VERSION "Alpha 0.1.0"// versão do jogo
#define SCREEN_WIDTH 800 // Largura da Janela
#define SCREEN_HEIGHT 600 // Altura da Janela
#define FPS 60

#define TEXT_COLOR al_map_rgb(255, 255, 255)


// level 001
#define MAP1_TILE_FLOOR 1 
#define MAP1_TILE_FLOOR_2 21 
#define MAP1_TILE_WOOD 9
#define MAP1_TILE_WALL 14
#define MAP1_TILE_WALL_2 24
#define MAP1_TILE_WALL_3 12
#define MAP1_TILE_SPIN 17
#define MAP1_FINAL_LEVEL1 5
#define MAP1_FINAL_LEVEL2 6
#define MAP1_FINAL_LEVEL3 15
#define MAP1_FINAL_LEVEL4 16
#define MAP2_FINAL_WATER 4

//#define MAP1_TILE_CHEST 18


#define QUAD_SIZE 32 // As artes do jogo será no padrao 32bits -> 32x32p pixels]
#define ITENS_QUAD_SIZE (QUAD_SIZE/2)// As artes dos itens jogo ser no padr�o 16bits -> 16x16 pixels
#define MAXLIFE_0 100 /// Maximo de vida que toda entidade pode ter



#define PLAYER_GRAVIDADE 1.0f;

#define PLAYER_X_0 (SCREEN_WIDTH / 2) - QUAD_SIZE
#define PLAYER_Y_0 (SCREEN_HEIGHT / 2) - QUAD_SIZE
#define PLAYER_VELOCITY_0 5
#define PLAYER_VELOCITY_Y_0 0
#define PLAYER_JUMP_FORCE -17.0
#define PLAYER_NORMAL_COLOR  al_map_rgba(0, 0, 255, 50)
#define PLAYER_ATACK_COLOR  al_map_rgb(100, 0, 200)
#define PLAYER_DEFENSE_COLOR  al_map_rgb(180, 0, 200);
#define PLAYER_ATACK_DAMAGE 2

#define ENEMY_GRAVIDADE 1.0;
#define ENEMY_X_0 (SCREEN_WIDTH - 30) - QUAD_SIZE
#define ENEMY_Y_0 (SCREEN_HEIGHT / 2) 
#define ENEMY_VELOCITY_0 3
#define ENEMY_COLOR  al_map_rgb(255, 0, 0)
#define ENEMY_ATACK_DAMAGE 1


#define KEY_ITEM_X (SCREEN_WIDTH - 700)//(SCREEN_WIDTH - 700)
#define KEY_ITEM_Y_0  100
#define KEY_ITEM_COLOR  al_map_rgb(255, 255, 0)

#define DISPLAY_LIFE_X (SCREEN_WIDTH - 700)
#define DISPLAY_LIFE_Y 50
#define DISPLAY_LIFE_W MAXLIFE_0
#define DISPLAY_LIFE_COLOR  al_map_rgb(0, 255, 0)



#define DOR_X (SCREEN_WIDTH - 200) - QUAD_SIZE
#define DOR_Y_0 (SCREEN_HEIGHT / 2) 
#define DOOR_HEIGHT 200
#define DOR_VELOCITY_0 50
#define DOR_COLOR  al_map_rgb(150, 50, 0)

#define MARKER_X 1633
#define MARKER_Y 185
#define MARKER_COLOR al_map_rgb(100, 100, 100)

#define GRID_ROWS 3
#define GRID_COLS 5

#define BUTTON_X 200
#define BUTTON_COLOR_NORMAL al_map_rgb(64, 25, 22) 
#define BUTTON_COLOR_HOVER al_map_rgb(115, 72, 47) 
//#define BUTTON_COLOR_CLICKED al_map_rgb(150, 150, 0)


#endif