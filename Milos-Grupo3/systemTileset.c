#include "systemTileset.h"


// Carrega um tileset a partir de um arquivo
Tileset* load_tileset(const char* filename, int tile_width, int tile_height) {
    Tileset* tileset = malloc(sizeof(Tileset));
    
    tileset->tileset = al_load_bitmap(filename);
    if (!tileset->tileset) {
        printf("Erro ao carregar tileset: %s\n", filename);
        free(tileset);
        return NULL;
    }
    
    tileset->tile_width = tile_width;
    tileset->tile_height = tile_height;
    
    // Calcula quantos tiles tem por linha
    int bmp_width = al_get_bitmap_width(tileset->tileset);
    tileset->tiles_per_row = bmp_width / tile_width;
    
    return tileset;
}

// Libera a memória do tileset
void destroy_tileset(Tileset* tileset) {
    if (tileset) {
        al_destroy_bitmap(tileset->tileset);
        free(tileset);
    }
}

// Desenha um tile específico
void draw_tile(Tileset* tileset, int tile_index, int x, int y) {
    if (tile_index < 0) return; // tile vazio
    
    int src_x = (tile_index % tileset->tiles_per_row) * tileset->tile_width;
    int src_y = (tile_index / tileset->tiles_per_row) * tileset->tile_height;
    
    al_draw_bitmap_region(
        tileset->tileset,
        src_x, src_y,
        tileset->tile_width, tileset->tile_height,
        x, y, 0
    );
}

// Cria um tilemap vazio
Tilemap* create_tilemap(int width, int height) {
    Tilemap* map = malloc(sizeof(Tilemap));
    map->width = width;
    map->height = height;
    
    // Aloca matriz 2D
    map->tiles = malloc(height * sizeof(int*));
    for (int y = 0; y < height; y++) {
        map->tiles[y] = malloc(width * sizeof(int));
        
        // Inicializa com -1 (tile vazio)
        for (int x = 0; x < width; x++) {
            map->tiles[y][x] = -1;
        }
    }
    
    return map;
}

// Libera a memória do tilemap
void destroy_tilemap(Tilemap* map) {
    if (map) {
        for (int y = 0; y < map->height; y++) {
            free(map->tiles[y]);
        }
        free(map->tiles);
        free(map);
    }
}

// Desenha o tilemap completo
void draw_tilemap(Tilemap* map, Tileset* tileset, int offset_x, int offset_y) {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            int tile_index = map->tiles[y][x];
            if (tile_index >= 0) {
                int screen_x = x * tileset->tile_width + offset_x;
                int screen_y = y * tileset->tile_height + offset_y;
                draw_tile(tileset, tile_index, screen_x, screen_y);
            }
        }
    }
}

// Define um tile específico no mapa
void set_tile(Tilemap* map, int x, int y, int tile_index) {
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        map->tiles[y][x] = tile_index;
    }
}




// Carrega um tilemap a partir de um arquivo (formato simples)
Tilemap* load_tilemap(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo: %s\n", filename);
        return NULL;
    }
    
    int width, height;
    fscanf(file, "%d %d", &width, &height);
    //fscanf_s(file, "%d %d", &width, &height);
    
    Tilemap* map = create_tilemap(width, height);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fscanf(file, "%d", &map->tiles[y][x]);
            //fscanf_s(file, "%d", &map->tiles[y][x]);
        }
    }
    
    fclose(file);
    return map;
}


bool check_entity_tile_collision(const entity* e, const Tilemap* map, const Tileset* tileset, int tile_index_to_check){
    // 1. Calcular as coordenadas do canto superior esquerdo e inferior direito da entidade
    int entity_left = e->x;
    int entity_top = e->y;
    int entity_right = e->x + e->width;
    int entity_bottom = e->y + e->height;

    // 2. Determinar o range de tiles que a entidade está ocupando
    // Converte coordenadas do mundo para coordenadas do mapa (índices de tile)
    int tile_width = tileset->tile_width;
    int tile_height = tileset->tile_height;

    int map_x_start = entity_left / tile_width;
    int map_y_start = entity_top / tile_height;
    int map_x_end = (entity_right - 1) / tile_width; // -1 para evitar checar o tile adjacente
    int map_y_end = (entity_bottom - 1) / tile_height; // -1 para evitar checar o tile adjacente
    
    // 3. Iterar sobre o range de tiles
    for (int y = map_y_start; y <= map_y_end; y++) {
        for (int x = map_x_start; x <= map_x_end; x++) {
            
            // 4. Verificar se o tile está dentro dos limites do mapa
            if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
                
                // 5. Verificar o índice do tile
                int current_tile_index = map->tiles[y][x];
                
                // 6. Se o tile atual for o tile específico procurado, há colisão.
                if (current_tile_index == tile_index_to_check) {
                    
                    // Verificação de colisão mais precisa (AABB)
                    // Calcula as coordenadas do tile atual
                    int tile_left = x * tile_width;
                    int tile_top = y * tile_height;
                    int tile_right = tile_left + tile_width;
                    int tile_bottom = tile_top + tile_height;
                    
                    // Checa se os retângulos se sobrepõem (AABB)
                    // Note que as coordenadas da entidade já foram usadas para encontrar o tile,
                    // mas essa checagem é útil se o tile_index_to_check for, por exemplo, um tile de "parede".
                    bool collision_overlap = (entity_left < tile_right &&
                                            entity_right > tile_left &&
                                            entity_top < tile_bottom &&
                                            entity_bottom > tile_top);
                                            
                    if (collision_overlap) {
                        return true;
                    }
                }
            }
        }
    }
    
    // 7. Se a iteração terminar sem encontrar o tile específico em colisão, retorna falso.
    return false;
}



