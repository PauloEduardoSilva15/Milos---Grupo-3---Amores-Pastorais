#ifndef SYSTEM_TILESET_H
#define SYSTEM_TILESET_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "entity.h"

typedef struct {
    ALLEGRO_BITMAP* tileset;
    int tile_width;
    int tile_height;
    int tiles_per_row;
} Tileset;


typedef struct {
    int** tiles; // matriz 2D de índices de tiles
    int width;
    int height;
    bool** collision_map;
} Tilemap;









Tileset* load_tileset(const char* filename, int tile_width, int tile_height);
void destroy_tileset(Tileset* tileset);

void draw_tile(Tileset* tileset, int tile_index, int x, int y);


Tilemap* create_tilemap(int width, int height);
void destroy_tilemap(Tilemap* map);
void draw_tilemap(Tilemap* map, Tileset* tileset, int offset_x, int offset_y);
void set_tile(Tilemap* map, int x, int y, int tile_index);
Tilemap* load_tilemap(const char* filename);


bool check_entity_tile_collision(const entity* e, const Tilemap* map, const Tileset* tileset, int tile_index_to_check);
void get_tile_world_start_pos(const entity* e, const Tilemap* map, const Tileset* tileset, int* world_x, int* world_y);

#endif // SYSTEM_TILESET_H