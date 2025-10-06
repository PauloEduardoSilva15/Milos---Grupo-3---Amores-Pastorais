#ifndef SYSTEM_TILESET_H
#define SYSTEM_TILESET_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

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
} Tilemap;


Tileset* load_tileset(const char* filename, int tile_width, int tile_height);
void destroy_tileset(Tileset* tileset);
void draw_tile(Tileset* tileset, int tile_index, int x, int y);


Tilemap* create_tilemap(int width, int height);
void destroy_tilemap(Tilemap* map);
void draw_tilemap(Tilemap* map, Tileset* tileset, int offset_x, int offset_y);
void set_tile(Tilemap* map, int x, int y, int tile_index);
Tilemap* load_tilemap(const char* filename);

#endif // SYSTEM_TILESET_H