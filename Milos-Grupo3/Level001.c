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

void level_I_Update(levelI * l, ALLEGRO_KEYBOARD_STATE * keystate){


    // Lógica de Colisão com o Chão

    
    

    if (!check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR)) {
        l->player.vY += PLAYER_GRAVIDADE;
		l->player.y += l->player.vY;
    }

    if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2)){
		l->player.y -= l->player.vY;
    }


    if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR)) {
		l->player.y -= l->player.vY;
		l->player.vY = 0;
		l->player.can_jump = true;
		if (al_key_down(keystate, ALLEGRO_KEY_W) && l->player.can_jump) {

            l->player.y -= PLAYER_GRAVIDADE;
			l->player.vY = PLAYER_JUMP_FORCE;
			l->player.can_jump = false;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL)){
                if(!check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2)){
                    l->player.vY += PLAYER_GRAVIDADE;
                    l->player.y += l->player.vY;
                }
            }
		}
	}
    
    if (al_key_down(keystate, ALLEGRO_KEY_A)){
       movEntity(&l->player, 0); 
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL))
            l->player.x += l->player.v;
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))
            l->player.x -= l->player.v;
         
    
    } 
    if (al_key_down(keystate, ALLEGRO_KEY_D)){
        movEntity(&l->player, 1);
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL))
            l->player.x -= l->player.v;
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))
            l->player.x -= l->player.v;
        
    } 



    
    

}



void Level_I_Draw(levelI  l){

    

    
    draw_tilemap(l.map, l.tileset, 0, 0);
    drawEntity(&l.player);
    
}