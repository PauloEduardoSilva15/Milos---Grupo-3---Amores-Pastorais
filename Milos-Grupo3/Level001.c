#include "Level001.h"

levelI Level_I_load(){
    levelI l;
    l.tileset = load_tileset("Milos-Grupo3/imgs/tilesets/Tileset_Map_001.png", QUAD_SIZE, QUAD_SIZE);
    l.map = load_tilemap("Milos-Grupo3/maps/001/map001.txt");

    //l.tileset = load_tileset("./imgs/tilesets/tileset001.png", QUAD_SIZE, QUAD_SIZE);
    //l.map = load_tilemap("./map001.txt");
    l.player = playerLoad();
    return l;
}



void Level_I_Draw(levelI  l){

    

    drawEntity(&l.player);
    draw_tilemap(l.map, l.tileset, 0, 0);
    
}