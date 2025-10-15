#include "level003.h"

levelIII Level_III_load(){
    levelIII l;
    l.tileset = load_tileset("./imgs/tilesets/Tileset_Map_003.png", QUAD_SIZE, QUAD_SIZE); // 
    l.map = load_tilemap("./maps/003/map003.txt"); // Carrega o mapa
    l.player = playerLoad();
    l.playerflip = 0;
    l.playerSpritepositionX = 0;
    l.playerSpritepositionY = 0;
    l.cameraX = 0;
    l.cameraY = 0;
    l.inPause = false;
    l.isDone = false;
    return l;

}
void level_III_Update(levelIII* l, ALLEGRO_KEYBOARD_STATE* keystate){

    if(!l->inPause){
        if(l->player.life <= 0) l->player.isDead = true; 

        if (!check_entity_tile_collision(&l->player, l->map, l->tileset, 1)) {    
            l->player.vY += PLAYER_GRAVIDADE;
            l->player.y += l->player.vY;
        }
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, 1)){
            l->player.y -= l->player.vY;
            l->player.vY = 0;
            l->player.can_jump = true;
        }

        if (al_key_down(keystate, ALLEGRO_KEY_W) && l->player.can_jump && !check_entity_tile_collision(&l->player, l->map, l->tileset, 0) ) {
            l->player.y -= PLAYER_GRAVIDADE;
		    l->player.vY = PLAYER_JUMP_FORCE;
		    l->player.can_jump = false;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, 0)){
                l->player.vY = 0;
            }
	    }

        if (al_key_down(keystate, ALLEGRO_KEY_A)){
            movEntity(&l->player, 0); 
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, 0))
                l->player.x += l->player.v;
        }
        if (al_key_down(keystate, ALLEGRO_KEY_D)){
            movEntity(&l->player, 1); 
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, 0))
                l->player.x -= l->player.v;
        }
    }

    if(al_key_down(keystate, ALLEGRO_KEY_X))
        printf("x = %d, y = %d \n", l->player.x, l->player.y);
    //Camera segindo o player no eixo X
    l->cameraX = -(l->player.x - SCREEN_WIDTH / 2);

    //if(al_key_down(keystate, ALLEGRO_KEY_B)) l->isDone = true;

}
void Level_III_Draw(levelIII l, ALLEGRO_FONT* Font){
    draw_tilemap(l.map, l.tileset, l.cameraX, l.cameraY);
    playerDraw(&l.player, l.cameraX, l.playerflip, l.playerSpritepositionX, l.playerSpritepositionY);
}
