#include "level003.h"

levelIII Level_III_load(){
    levelIII l;
    l.tileset = load_tileset("./imgs/tilesets/Tileset_Map_003.png", QUAD_SIZE, QUAD_SIZE); // 
    l.map = load_tilemap("./maps/003/map003.txt"); // Carrega o mapa
    l.player = playerLoad();
    l.playerflip = 0;
    l.playerSpritepositionX = 0;
    l.playerSpritepositionY = 0;
    l.npc1 = newEntity(1233, 352, 0, 0, al_map_rgb(100, 0, 150),"./imgs/sprites/Thebos.png", false);
    l.npc2 = newEntity(1198, 352, 0, 0, al_map_rgb(100, 0, 150),"./imgs/sprites/marilia.png", false);
    l.dialogue = dialogueLoad();
    l.inDialogue = false;
    l.dialogueOption = 15;
    l.cameraX = 0;
    l.cameraY = 0;
    l.inPause = false;
    l.isDone = false;
    return l;

}
void level_III_Update(levelIII* l, ALLEGRO_KEYBOARD_STATE* keystate){

    if (l->dialogueOption == 19) {
		/*l->inDialogue = false;
        l->inPause = false;
        l->dialogueOption = 15;*/
        l->isDone = true;
	}
    if(l->inDialogue){
        l->inPause = true;
    }

    if(!l->inPause){
        if(l->player.life <= 0) l->player.isDead = true; 

        if (!check_entity_tile_collision(&l->player, l->map, l->tileset, 1)) {    
            l->player.vY += PLAYER_GRAVIDADE;
            l->player.y += l->player.vY;
        }
        if (check_entity_tile_collision(&l->player, l->map, l->tileset, 1)){
            l->player.y -= l->player.vY;
            l->player.vY = 0;
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
        if(al_key_down(keystate, ALLEGRO_KEY_A))l->playerflip = ALLEGRO_FLIP_HORIZONTAL;
	    if(al_key_down(keystate, ALLEGRO_KEY_D)) l->playerflip = 0;
        if (al_key_down(keystate, ALLEGRO_KEY_E) && collisionEntityWithEntity(&l->player, &l->npc1)) {
            l->inDialogue = true;
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
    draw_Enity_camera_andImage(&l.npc1, l.cameraX, 0);
    if (l.inDialogue) drawDialogue(&l.dialogue, Font, l.dialogueOption);
    draw_Enity_camera_andImage_region(&l.npc2, l.cameraX, 0, 0, 0);
    if (collisionEntityWithEntity(&l.player, &l.npc1))al_draw_text(Font, TEXT_COLOR, (l.npc1.x + l.cameraX)-l.npc1.width/2, l.npc1.y - 25, 0, "[E] Falar");
    playerDraw(&l.player, l.cameraX, l.playerflip, l.playerSpritepositionX, l.playerSpritepositionY);
}
