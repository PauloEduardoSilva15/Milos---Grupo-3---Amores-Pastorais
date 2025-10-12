#include "Level001.h"


levelI Level_I_load(){
    levelI l;
    l.tileset = load_tileset("./imgs/tilesets/Tileset_Map_001.png", QUAD_SIZE, QUAD_SIZE); // Carrega Tileset
    l.map = load_tilemap("./maps/001/map001.txt"); // Carrega o mapa
    l.player = playerLoad(); // PLayer ou Dirceu
    l.npc = newEntity(190, 416 - 32, 0, 0, al_map_rgb(100, 0, 150), false); // Velho Desconhecido
    l.inDialogue = false;
    l.dialogueOption = 0;
    l.dialogue = dialogueLoad();
    l.cameraX = 0;
    l.cameraY = 0;

    
    return l;
}

void level_I_Update(levelI * l, ALLEGRO_KEYBOARD_STATE * keystate){

    //Colisões
    if (al_key_down(keystate, ALLEGRO_KEY_E) && collisionEntityWithEntity(&l->player, &l->npc)) {
		l->inDialogue = true;
	}
	if (al_key_down(keystate, ALLEGRO_KEY_R)) {
		l->inDialogue = false;
	}


	if (l->dialogueOption == 5 || l->dialogueOption == 9) {
		l->inDialogue = false;
		l->dialogueOption = 0;
	}

    if(l->player.x == 768){
        l->npc.x = 2988;
        l->dialogueOption = 6;
    }


    if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2) || check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD) || check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR_2)){
		l->player.y -= l->player.vY;
    }
    if (!check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR) || !check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) {
        l->player.vY += PLAYER_GRAVIDADE;
		l->player.y += l->player.vY;
    }
    if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)){
		l->player.y -= l->player.vY;
		l->player.vY = 0;
		l->player.can_jump = true;
	}
    if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR)){
		l->player.y -= l->player.vY;
		l->player.vY = 0;
		l->player.can_jump = true;
	}
    if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_SPIN)) l->player.isDead = true;
    //Controles do player
    if(!l->inDialogue){

        
        if (al_key_down(keystate, ALLEGRO_KEY_W) && l->player.can_jump) {
            l->player.y -= PLAYER_GRAVIDADE;
		    l->player.vY = PLAYER_JUMP_FORCE;
		    l->player.can_jump = false;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL)){

                l->player.vY += PLAYER_GRAVIDADE;
                l->player.y += l->player.vY;
            }
	    }    
        if (al_key_down(keystate, ALLEGRO_KEY_A)){
            movEntity(&l->player, 0); 
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL))
                l->player.x += l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))
                l->player.x += l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))
                l->player.x += l->player.v;
    
        } 
        if (al_key_down(keystate, ALLEGRO_KEY_D)){
            movEntity(&l->player, 1);
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL))
                l->player.x -= l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))
                l->player.x -= l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))
                l->player.x -= l->player.v;
        } 
        
        
    }

    
    

    if(al_key_down(keystate, ALLEGRO_KEY_X)){
        printf("x = %d, y = %d ", l->player.x, l->player.y);
    }
   
    //if(l->player.isDead) *l = Level_I_load();

    //Camera segindo o player no eixo X
    l->cameraX = -(l->player.x - SCREEN_WIDTH / 2);

    
    

}



void Level_I_Draw(levelI  l, ALLEGRO_FONT* Font){
    draw_tilemap(l.map, l.tileset, l.cameraX, l.cameraY);
    //drawEntity(&l.player);
    if (collisionEntityWithEntity(&l.player, &l.npc))al_draw_text(Font, TEXT_COLOR, (l.npc.x + l.cameraX)-l.npc.size/2, l.npc.y - 25, 0, "[E] Falar");
    if (l.inDialogue) drawDialogue(&l.dialogue, Font, l.dialogueOption);
    draw_entity_with_camera(&l.npc, l.cameraX);
    draw_entity_with_camera(&l.player, l.cameraX);
    
}