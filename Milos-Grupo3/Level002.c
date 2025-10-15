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
    l.npc1 = newEntity(605, 320, 0, 0, al_map_rgb(100, 0, 150),"./imgs/sprites/sprite_oldMan.png", false);
    l.npc2 = newEntity(625, 320, 0, 0, al_map_rgb(100, 0, 150),"./imgs/sprites/sprite_oldMan.png", false);
    l.guard1 = enemyLoad(1230, 0);
    l.guard2 = enemyLoad(1740, -64);
    l.guard3 = enemyLoad(2495, 320);
    l.guard4 = enemyLoad(2525, 320);
    l.guard1_Folowing = false;
    l.guard2_Folowing = false;
    l.guard3_Folowing = false;
    l.guard4_Folowing = false;
    l.guard1flip = true;
    l.guard2flip = true;
    l.guard3flip = true;
    l.guard4flip = true;
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

        if (l->guard1.life <= 0) l->guard1.isDead = true;
        if (l->guard1.isDead) {
		    l->guard1.x = 0;
		    l->guard1.y = 0;
	    }if (l->guard2.life <= 0) l->guard2.isDead = true;
        if (l->guard2.isDead) {
		    l->guard2.x = 0;
		    l->guard2.y = 0;
	    }if (l->guard3.life <= 0) l->guard3.isDead = true;
        if (l->guard3.isDead) {
		    l->guard3.x = 0;
		    l->guard3.y = 0;
	    }if (l->guard4.life <= 0) l->guard4.isDead = true;
        if (l->guard4.isDead) {
		    l->guard4.x = 0;
		    l->guard4.y = 0;
	    }


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
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR))
                l->player.x += l->player.v;
    
        } 
        if (al_key_down(keystate, ALLEGRO_KEY_D)){
            movEntity(&l->player, 1);   
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, 3))l->player.x -= l->player.v; 
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR))
                l->player.x -= l->player.v;        
        } 

        if(l->player.x < 400) l->player.x = 400;
        if(l->player.x > 2800-l->player.width) l->player.x = 2800-l->player.width;

        if (check_entity_tile_collision(&l->player, l->map, l->tileset, 4)){
            l->player.life -= 30;
        }
        if (check_entity_tile_collision(&l->guard1, l->map, l->tileset, 4)){
            l->guard1.life -= 30;
        }
        if (check_entity_tile_collision(&l->guard2, l->map, l->tileset, 4)){
            l->guard2.life -= 30;
        }

        if (!check_entity_tile_collision(&l->guard1, l->map, l->tileset, 1) && !l->guard1.isDead) {    
            l->guard1.vY += PLAYER_GRAVIDADE;
            l->guard1.y += l->guard1.vY;
        }
        if ((check_entity_tile_collision(&l->guard1, l->map, l->tileset, 1)|| check_entity_tile_collision(&l->guard1, l->map, l->tileset, 3) || check_entity_tile_collision(&l->guard1, l->map, l->tileset, 7))&& !l->guard1.isDead){
            l->guard1.y -= l->guard1.vY;
            l->guard1.vY = 0;
        }


        if(l->player.x >= 750) l->guard1_Folowing = true;

        if(l->guard1_Folowing){
            if (!collisionEntityWithEntity(&l->player, &l->guard1)) {
		        if (l->guard1.x > l->player.x) {
                    l->guard1flip = ALLEGRO_FLIP_HORIZONTAL;
			            movEntity(&l->guard1, 0);//esquerda
		        }
		        else{
                    if(l->guard1.x < l->player.x) l->guard1flip = ALLEGRO_FLIP_HORIZONTAL;
                    movEntity(&l->guard1, 1);//direita
	            }
            }
        }


        if(l->player.x >= 1550) l->guard2_Folowing = true;

        if(l->guard2_Folowing){

            if (!check_entity_tile_collision(&l->guard2, l->map, l->tileset, 1) && !l->guard2.isDead) {    
                l->guard2.vY += PLAYER_GRAVIDADE;
                l->guard2.y += l->guard2.vY;
            }
            if ((check_entity_tile_collision(&l->guard2, l->map, l->tileset, 1)|| check_entity_tile_collision(&l->guard2, l->map, l->tileset, 3) || check_entity_tile_collision(&l->guard2, l->map, l->tileset, 7))&& !l->guard2.isDead){
                l->guard2.y -= l->guard2.vY;
                l->guard2.vY = 0;
            }
            if (!collisionEntityWithEntity(&l->player, &l->guard2)) {
		        if (l->guard2.x > l->player.x) {
                    l->guard2flip = ALLEGRO_FLIP_HORIZONTAL;
			        movEntity(&l->guard2, 0);//esquerda
		        }
		        else{
                    if(l->guard2.x < l->player.x) l->guard1flip = ALLEGRO_FLIP_HORIZONTAL;
                    movEntity(&l->guard2, 1);//direita
	            }
            }
        }

        if(l->player.x >= 1953){
            l->guard3_Folowing = true;
            l->guard4_Folowing = true;
        } 
        if(l->guard3_Folowing){
            if (!collisionEntityWithEntity(&l->player, &l->guard3)) {
		        if (l->guard3.x > l->player.x) {
                    l->guard3flip = ALLEGRO_FLIP_HORIZONTAL;
			        movEntity(&l->guard3, 0);//esquerda
		        }
		        else movEntity(&l->guard3, 1);//direita
	        }
        }
        if(l->guard4_Folowing){
            if (!collisionEntityWithEntity(&l->player, &l->guard4)) {
		        if (l->guard4.x > l->player.x) {
                    l->guard4flip = ALLEGRO_FLIP_HORIZONTAL;
			        movEntity(&l->guard4, 0);//esquerda
		        }
		        else movEntity(&l->guard4, 1);//direita
	        }
            if(collisionEntityWithEntity(&l->guard4, &l->guard3)) l->guard4.x += 10;
        }

        

        if (collisionEntityWithEntity(&l->guard1, &l->player) && l->player.life > 0) {
		    if (!l->player.modoAtaque) {
			    if (!l->player.modoDefesa)
				    if (!l->guard1.isDead)l->player.life -= 3; //tira vida do player
		    }
		    else {
			    if (!l->player.modoDefesa)
				    if (l->guard1.life > 0) l->guard1.life -= 3; //tira vida do inimigo
		    }
	    }
        if (collisionEntityWithEntity(&l->player, &l->guard1)) {
		    if (l->guard1.x > l->player.x)
		    {
			    l->guard1.x += 10;
			    l->player.x -= 10;
		    }
		    else {
			    if (!(l->player.y > l->guard1.y)) {
				    l->guard1.x -= 10;
				    l->player.x += 10;
			    }
			    else
				    l->guard1.x += 10;
		    }
	    }
        if (collisionEntityWithEntity(&l->guard2, &l->player) && l->player.life > 0) {
		    if (!l->player.modoAtaque) {
			    if (!l->player.modoDefesa)
				    if (!l->guard2.isDead)l->player.life -= 3; //tira vida do player
		    }
		    else {
			    if (!l->player.modoDefesa)
				    if (l->guard2.life > 0) l->guard2.life -= 3; //tira vida do inimigo
		    }
	    }
        if (collisionEntityWithEntity(&l->player, &l->guard2)) {
		    if (l->guard2.x > l->player.x)
		    {
			    l->guard2.x += 10;
			    l->player.x -= 10;
		    }
		    else {
			    if (!(l->player.y > l->guard2.y)) {
				    l->guard2.x -= 10;
				    l->player.x += 10;
			    }
			    else
				    l->guard2.x += 10;
		    }
	    }

        if (collisionEntityWithEntity(&l->guard3, &l->player) && l->player.life > 0) {
		    if (!l->player.modoAtaque) {
			    if (!l->player.modoDefesa)
				    if (!l->guard3.isDead)l->player.life -= 3; //tira vida do player
		    }
		    else {
			    if (!l->player.modoDefesa)
				    if (l->guard3.life > 0) l->guard3.life -= 3; //tira vida do inimigo
		    }
	    }
        if (collisionEntityWithEntity(&l->player, &l->guard3)) {
		    if (l->guard3.x > l->player.x)
		    {
			    l->guard3.x += 10;
			    l->player.x -= 10;
		    }
		    else {
			    if (!(l->player.y > l->guard3.y)) {
				    l->guard3.x -= 10;
				    l->player.x += 10;
			    }
			    else
				    l->guard3.x += 10;
		    }
	    }

        if (collisionEntityWithEntity(&l->guard4, &l->player) && l->player.life > 0) {
		    if (!l->player.modoAtaque) {
			    if (!l->player.modoDefesa)
				    if (!l->guard4.isDead)l->player.life -= 3; //tira vida do player
		    }
		    else {
			    if (!l->player.modoDefesa)
				    if (l->guard4.life > 0) l->guard4.life -= 3; //tira vida do inimigo
		    }
	    }
        if (collisionEntityWithEntity(&l->player, &l->guard4)) {
		    if (l->guard4.x > l->player.x)
		    {
			    l->guard4.x += 10;
			    l->player.x -= 10;
		    }
		    else {
			    if (!(l->player.y > l->guard2.y)) {
				    l->guard4.x -= 10;
				    l->player.x += 10;
			    }
			    else
				    l->guard4.x += 10;
		    }
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
    if (collisionEntityWithEntity(&l.player, &l.npc1)|| collisionEntityWithEntity(&l.player, &l.npc2))al_draw_text(Font, TEXT_COLOR, (l.npc1.x + l.cameraX)-l.npc1.width/2, l.npc1.y - 25, 0, "[E] Falar");
    if (l.inDialogue) drawDialogue(&l.dialogue, Font, l.dialogueOption);
    if(!l.guard1.isDead)enemyDraw(&l.guard1, l.cameraX, l.guard1flip, 0, 0);
    if(!l.guard2.isDead)enemyDraw(&l.guard2, l.cameraX, l.guard2flip, 0, 0);
    if(!l.guard3.isDead)enemyDraw(&l.guard3, l.cameraX, l.guard3flip, 0, 0);
    if(!l.guard4.isDead)enemyDraw(&l.guard4, l.cameraX, l.guard4flip, 0, 0);
    draw_Enity_camera_andImage(&l.npc1, l.cameraX);
    draw_Enity_camera_andImage(&l.npc2, l.cameraX);
    playerDraw(&l.player, l.cameraX, l.playerflip, l.playerSpritepositionX, l.playerSpritepositionY);
}
