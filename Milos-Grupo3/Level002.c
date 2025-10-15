#include "Level002.h"


levelII Level_II_load(){
    levelII l;
    l.tileset = load_tileset("./imgs/tilesets/Tileset_Map_002.png", QUAD_SIZE, QUAD_SIZE); // Carrega Tileset
    l.map = load_tilemap("./maps/002/map002.txt"); // Carrega o mapa
    l.player = playerLoad();
    l.player.x = 500;
    l.playerflip = 0;
    l.dialogue = dialogueLoad();
    l.inDialogue = false;
    l.dialogueOption = 10;
    l.playerSpritepositionX = 0;
    l.playerSpritepositionY = 0;
    l.npc1 = newEntity(680, 320, 0, 0, al_map_rgb(100, 0, 150),"./imgs/sprites/sprite_oldMan.png", false);
    l.npc2 = newEntity(695, 320, 0, 0, al_map_rgb(100, 0, 150),"./imgs/sprites/sprite_oldMan.png", false);
    l.cameraX = 0;
    l.cameraY = 0;
    l.inPause = false;
    l.hud = newHud(l.player.life, false);
    return l;

}
void level_II_Update(levelII* l, ALLEGRO_KEYBOARD_STATE* keystate){

    if (l->dialogueOption == 14) {
		l->inDialogue = false;
        l->inPause = false;
        l->dialogueOption = 10;
	}

    if(!l->inPause){
        if(l->player.life <= 0) l->player.isDead = true; 

        if(al_key_down(keystate, ALLEGRO_KEY_A))l->playerflip = ALLEGRO_FLIP_HORIZONTAL;
	    if(al_key_down(keystate, ALLEGRO_KEY_D)) l->playerflip = 0;

        if (al_key_down(keystate, ALLEGRO_KEY_J)) l->player.modoAtaque = true;
		    else l->player.modoAtaque = false;
		    if (al_key_down(keystate, ALLEGRO_KEY_K)) l->player.modoDefesa = true;
		    else l->player.modoDefesa = false;


        if (al_key_down(keystate, ALLEGRO_KEY_E) && (collisionEntityWithEntity(&l->player, &l->npc1)|| collisionEntityWithEntity(&l->player, &l->npc2))) {
            l->inDialogue = true;
        }

        if(l->player.modoAtaque){
            l->playerSpritepositionX = 64;
            l->playerSpritepositionY = 64;
        }
        if(l->player.modoDefesa){
            l->playerSpritepositionX = 32;
            l->playerSpritepositionY = 128;
        }
        if(!l->player.modoAtaque && !l->player.modoDefesa){
            l->playerSpritepositionX = 0;
            l->playerSpritepositionY = 0;
        }
         if (!check_entity_tile_collision(&l->player, l->map, l->tileset, 1)) {    
            l->player.vY += PLAYER_GRAVIDADE;
            l->player.y += l->player.vY;
        }
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, 1) || check_entity_tile_collision(&l->player, l->map, l->tileset, 3) || check_entity_tile_collision(&l->player, l->map, l->tileset, 7)){
            l->player.y -= l->player.vY;
            l->player.vY = 0;
            l->player.can_jump = true;
        }

         if (al_key_down(keystate, ALLEGRO_KEY_W) && l->player.can_jump ) {
            l->player.y -= PLAYER_GRAVIDADE;
		    l->player.vY = PLAYER_JUMP_FORCE;
		    l->player.can_jump = false;
            
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, 3)){

                l->player.vY = 0;
            }
	    }
        if (al_key_down(keystate, ALLEGRO_KEY_A)){
            movEntity(&l->player, 0); 
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, 3))l->player.x += l->player.v;
    
        } 
        if (al_key_down(keystate, ALLEGRO_KEY_D)){
            movEntity(&l->player, 1);   
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, 3))l->player.x -= l->player.v;         
        } 

        if(l->player.x < 400) l->player.x = 400;
        if(l->player.x > 2800-l->player.width) l->player.x = 2800-l->player.width;

        if (check_entity_tile_collision(&l->player, l->map, l->tileset, 4)){
            l->player.life -= 5;
        }

        
    }
    l->hud.displayLife.width = l->player.life;
    //Isso é só para debug;
    if(al_key_down(keystate, ALLEGRO_KEY_X))
        printf("x = %d, y = %d \n", l->player.x, l->player.y);

    
    //Camera segindo o player no eixo X
    l->cameraX = -(l->player.x - SCREEN_WIDTH / 2);
}
void Level_II_Draw(levelII l, ALLEGRO_FONT* Font){
    al_clear_to_color(al_map_rgb(9, 155, 255));
    draw_tilemap(l.map, l.tileset, l.cameraX, l.cameraY);
    drawHud(&l.hud);
    if (collisionEntityWithEntity(&l.player, &l.npc1)|| collisionEntityWithEntity(&l.player, &l.npc1))al_draw_text(Font, TEXT_COLOR, (l.npc1.x + l.cameraX)-l.npc1.width/2, l.npc1.y - 25, 0, "[E] Falar");
    if (l.inDialogue) drawDialogue(&l.dialogue, Font, l.dialogueOption);
    draw_Enity_camera_andImage(&l.npc1, l.cameraX);
    draw_Enity_camera_andImage(&l.npc2, l.cameraX);
    playerDraw(&l.player, l.cameraX, l.playerflip, l.playerSpritepositionX, l.playerSpritepositionY);
}
