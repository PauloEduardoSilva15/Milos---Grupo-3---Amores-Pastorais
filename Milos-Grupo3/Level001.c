#include "Level001.h"


levelI Level_I_load(){
    levelI l;
    l.tileset = load_tileset("./imgs/tilesets/Tileset_Map_001.png", QUAD_SIZE, QUAD_SIZE); // Carrega Tileset
    l.map = load_tilemap("./maps/001/map001.txt"); // Carrega o mapa
    l.player = playerLoad(); // PLayer (Dirceu)
    l.npc = newEntity(190, 416 - 64, 0, 0, al_map_rgb(100, 0, 150),"./imgs/sprites/sprite_oldMan.png", false); // Velho Desconhecido
    //l.pauseMenu = createPauseMenu();
    l.inDialogue = false;
    l.dialogueOption = 0;
    l.dialogue = dialogueLoad();
    l.getKey = false;
    //l.displayLife = displayLifeLoad(l.player.life);
    l.door = newObstacle(2693,320, "./imgs/sprites/door.png");
    l.doorSpritePositionX = 0;
    l.hud = newHud(l.player.life, l.getKey);
    l.maker = newMarker(MARKER_X, MARKER_Y); // Carrega o marcador
    l.dirPlayer = 0;
    l.isDone = false;
    l.PlayerFlip = 0;
    l.inPause = false;
    l.cameraX = 0;
    l.cameraY = 0;
    
    return l;
}

void level_I_Update(levelI * l, ALLEGRO_KEYBOARD_STATE * keystate){

    if (l->dialogueOption == 5 || l->dialogueOption == 9) {
		l->inDialogue = false;
        l->inPause = false;
        if(l->dialogueOption == 5) l->dialogueOption = 0;
        else l->dialogueOption = 6;
	}
    if(l->player.x == 608){
        l->npc.x = 2988;
        l->dialogueOption = 6;
    }
    if(l->inDialogue){
        l->inPause = true;
    }
    
   if(l->player.x == 3063)l->isDone = true;

    

    


    
  
    if(!l->inPause){
        if(l->player.life <= 0) l->player.isDead = true; 
        if(al_key_down(keystate, ALLEGRO_KEY_A))l->PlayerFlip = ALLEGRO_FLIP_HORIZONTAL;
	    if(al_key_down(keystate, ALLEGRO_KEY_D)) l->PlayerFlip = 0;
        //Colisões
        if (al_key_down(keystate, ALLEGRO_KEY_E) && collisionEntityWithEntity(&l->player, &l->npc)) {
            l->inDialogue = true;
        }
        if (al_key_down(keystate, ALLEGRO_KEY_R)) {
            l->inDialogue = false;
            l->inPause = false;
        }
        if (al_key_down(keystate, ALLEGRO_KEY_E) && collisionEntityMaker(&l->player, &l->maker)) {
            l->getKey = true;

        }
        if((check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2) /*||(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))*/ || check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR_2))){
            l->player.y -= l->player.vY;
        }
        if (!check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR)) {    
            l->dirPlayer = 0;
            l->player.vY += PLAYER_GRAVIDADE;
            l->player.y += l->player.vY;
        }
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR)|| (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)&& l->dirPlayer !=1)){
            l->player.y -= l->player.vY;
            l->player.vY = 0;
            l->player.can_jump = true;
        }
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_SPIN)){
            l->player.life -= 30;
        }


          //Controles do player
        if (al_key_down(keystate, ALLEGRO_KEY_W) && l->player.can_jump && !check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) {

            l->dirPlayer = 1;
            l->player.y -= PLAYER_GRAVIDADE;
		    l->player.vY = PLAYER_JUMP_FORCE;
		    l->player.can_jump = false;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL)){

                l->player.vY += PLAYER_GRAVIDADE;
                l->player.y += l->player.vY;
            }
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)){

                l->player.vY = 0;
            }
	    }
        if (al_key_down(keystate, ALLEGRO_KEY_A)){
            l->dirPlayer = 2;
            movEntity(&l->player, 0); 
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL))
                l->player.x += l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))
                l->player.x += l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_3))
                l->player.x += l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))l->player.x += l->player.v;
    
        } 
        if (al_key_down(keystate, ALLEGRO_KEY_D)){
            l->dirPlayer = 3;
            movEntity(&l->player, 1);
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL))
                l->player.x -= l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))
                l->player.x -= l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))l->player.x -= l->player.v;
            if(collisionEntityObstacle(&l->player, &l->door)&& !l->getKey) l->player.x -= l->player.v;
            if(collisionEntityObstacle(&l->player, &l->door)&& l->getKey) {
                l->doorSpritePositionX = 32;
            }

            
        } 

        
    }

    l->hud.displayLife.width = l->player.life;
    l->hud.getKey = l->getKey;
    
    
    //Isso é só para debug;
    if(al_key_down(keystate, ALLEGRO_KEY_X))
        printf("x = %d, y = %d \n", l->player.x, l->player.y);

    


    //Camera segindo o player no eixo X
    l->cameraX = -(l->player.x - SCREEN_WIDTH / 2);

    
	

}



void Level_I_Draw(levelI  l, ALLEGRO_FONT* Font){
    draw_tilemap(l.map, l.tileset, l.cameraX, l.cameraY);
    //drawEntity(&l.player);
    if (collisionEntityWithEntity(&l.player, &l.npc))al_draw_text(Font, TEXT_COLOR, (l.npc.x + l.cameraX)-l.npc.width/2, l.npc.y - 25, 0, "[E] Falar");
    if (collisionEntityMaker(&l.player, &l.maker))al_draw_text(Font, TEXT_COLOR, (l.maker.x + l.cameraX)-l.maker.size/2, l.maker.y - 25, 0, "[E] Interagir");
    if (l.inDialogue) drawDialogue(&l.dialogue, Font, l.dialogueOption);
    draw_maker_with_camera(&l.maker, l.cameraX);
    draw_Enity_camera_andImage(&l.npc, l.cameraX);
    drawObstacle(&l.door, l.cameraX, l.doorSpritePositionX, 0);
    //draw_entity_with_camera(&l.player, l.cameraX);
    playerDraw(&l.player, l.cameraX, l.PlayerFlip);
    drawHud(&l.hud);
    //if(l.inPause) al_clear_to_color(al_map_rgb(0, 0, 0));
}