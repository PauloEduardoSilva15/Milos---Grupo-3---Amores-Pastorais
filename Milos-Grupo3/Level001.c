#include "Level001.h"


levelI Level_I_load() {
    levelI l;
    l.tileset = load_tileset("./imgs/tilesets/Tileset_Map_001.png", QUAD_SIZE, QUAD_SIZE); // Carrega Tileset
    l.map = load_tilemap("./maps/001/map001.txt"); // Carrega o mapa
    l.player = playerLoad(); // PLayer (Dirceu)
    l.npc = newEntity(190, 354, 0, 0, al_map_rgb(100, 0, 150), "./imgs/sprites/sprite_oldMan.png", false); // Velho Desconhecido
    l.guard1 = enemyLoad(1088, 128);
    l.guard2 = enemyLoad(1348, 128);
    l.guard3 = enemyLoad(2398, 354);
    l.guard4 = enemyLoad(2430, 354);
    //l.pauseMenu = createPauseMenu();
    l.inDialogue = false;
    l.dialogueOption = 0;
    l.dialogue = dialogueLoad();
    l.getKey = false;
    l.door = newObstacle(2693, 320, "./imgs/sprites/door.png");
    l.doorSpritePositionX = 0;
    l.hud = newHud(l.player.life, l.getKey);
    l.maker = newMarker(MARKER_X, MARKER_Y); // Carrega o marcador
    l.playerSpritepositionX = 0;
    l.playerSpritepositionY = 0;
    l.guard1flip = 0;
    l.guard2flip = 0;
    l.guard3flip = 0;
    l.guard4flip = 0;
    l.guard1_Folowing = false;
    l.guard2_Folowing = false;
    l.dirPlayer = 0;
    l.isDone = false;
    l.puzzle_open = false;
    l.puzzle_isSolved = false;
    l.PlayerFlip = 0;
    l.inPause = false;
    l.cameraX = 0;
    l.cameraY = 0;

    return l;
}

void level_I_Update(levelI* l, ALLEGRO_KEYBOARD_STATE* keystate) {

    if (l->dialogueOption == 5 || l->dialogueOption == 9) {
        l->inDialogue = false;
        l->inPause = false;
        if (l->dialogueOption == 5) l->dialogueOption = 0;
        else l->dialogueOption = 6;
    }
    if (l->player.x == 608) {
        l->npc.x = 2988;
        l->dialogueOption = 6;
    }
    if (l->inDialogue) {
        l->inPause = true;
    }

    if (l->player.x == 3063)l->isDone = true;


    if (!l->inPause) {
        if (l->player.life <= 0) l->player.isDead = true;
        if (l->guard1.life <= 0) l->guard1.isDead = true;
        if (l->guard1.isDead) {
            l->guard1.x = 0;
            l->guard1.y = 0;
        }
        if (l->guard2.life <= 0) l->guard2.isDead = true;
        if (l->guard2.isDead) {
            l->guard2.x = 0;
            l->guard2.y = 0;
        }
        if (l->guard3.life <= 0) l->guard3.isDead = true;
        if (l->guard3.isDead) {
            l->guard3.x = 0;
            l->guard3.y = 0;
        }

        if (l->guard4.life <= 0) l->guard4.isDead = true;
        if (l->guard4.isDead) {
            l->guard4.x = 0;
            l->guard4.y = 0;
        }

        if (al_key_down(keystate, ALLEGRO_KEY_A))l->PlayerFlip = ALLEGRO_FLIP_HORIZONTAL;
        if (al_key_down(keystate, ALLEGRO_KEY_D)) l->PlayerFlip = 0;

        if(l->player.modoAtaque && l->player.attack_cooldown == 0.0f) {
            l->player.attack_cooldown = 1.0f; // Set cooldown duration
        }

        if(l->player.attack_cooldown > 0.0f) {
            l->player.attack_cooldown -= 0.1f; // Decrease cooldown
            if(l->player.attack_cooldown < 0.0f){
                l->player.attack_cooldown = 0.0f; // Clamp to 0
                l->player.modoAtaque = false; // Reset attack mode
            } 
        }
		if (al_key_down(keystate, ALLEGRO_KEY_K)&&!l->player.modoAtaque) l->player.modoDefesa = true;
		else l->player.modoDefesa = false;

        if (l->player.modoAtaque) {
            l->playerSpritepositionX = 64;
            l->playerSpritepositionY = 64;
        }
        if (l->player.modoDefesa) {
            l->playerSpritepositionX = 32;
            l->playerSpritepositionY = 128;
        }
        if (!l->player.modoAtaque && !l->player.modoDefesa) {
            l->playerSpritepositionX = 0;
            l->playerSpritepositionY = 0;
        }

        


        //Colisões
        if (al_key_down(keystate, ALLEGRO_KEY_E) && collisionEntityWithEntity(&l->player, &l->npc)) {
            l->inDialogue = true;
        }
        /*if (al_key_down(keystate, ALLEGRO_KEY_R)&& l->inDialogue) {
            l->inDialogue = false;
            l->inPause = false;
        }*/
        if (al_key_down(keystate, ALLEGRO_KEY_E) && collisionEntityMaker(&l->player, &l->maker) && !l->puzzle_isSolved) {
            l->inPause = true;
            l->puzzle_open = true;

        }
        if ((check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2) /*||(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))*/ || check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR_2))) {
            l->player.y -= l->player.vY;
        }
        if (!check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR)) {
            l->dirPlayer = 0;
            l->player.vY += PLAYER_GRAVIDADE;
            l->player.y += l->player.vY;
        }

        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_FLOOR) || check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) {
            // Sem ambiguidade: se estiver em chão/wood -> para queda/jump disponível
            l->player.y -= l->player.vY;
            l->player.vY = 0;
            l->player.can_jump = true;
        }
        if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) {
            l->player.y += ENEMY_PUSHBACK;
        }
        if(check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_WOOD)) {
            l->guard2.y += ENEMY_PUSHBACK;
        }

        // ----- Guard1 gravidade / chão (corrigido: agrupamento lógico) -----
        if (!check_entity_tile_collision(&l->guard1, l->map, l->tileset, MAP1_TILE_FLOOR) && !l->guard1.isDead) {
            l->guard1.vY += PLAYER_GRAVIDADE;
            l->guard1.y += l->guard1.vY;
        }
        if ((check_entity_tile_collision(&l->guard1, l->map, l->tileset, MAP1_TILE_FLOOR) || check_entity_tile_collision(&l->guard1, l->map, l->tileset, MAP1_TILE_WOOD)) && !l->guard1.isDead) {
            l->guard1.y -= l->guard1.vY;
            l->guard1.vY = 0;
            l->guard1.can_jump = true;
        }

        // ----- Guard2 gravidade / chão (corrigido: agrupamento lógico) -----
        if (!check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_FLOOR) && !l->guard2.isDead) {
            //l->dirguard1 = 0;
            l->guard2.vY += PLAYER_GRAVIDADE;
            l->guard2.y += l->guard2.vY;
            l->guard2.can_jump = false;
        }
        if ((check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_FLOOR) || check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_WOOD)) && !l->guard2.isDead) {
            l->guard2.y -= l->guard2.vY;
            l->guard2.vY = 0;
            l->guard2.can_jump = true;
        }
        

        if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_SPIN)) {
            l->player.life -= 30;
        }
        if (check_entity_tile_collision(&l->guard1, l->map, l->tileset, MAP1_TILE_SPIN)) {
            l->guard1.life -= 30;
        }
        if (check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_SPIN)) {
            l->guard2.life -= 30;
        }
        if (check_entity_tile_collision(&l->guard3, l->map, l->tileset, MAP1_TILE_SPIN)) {
            l->guard3.life -= 30;
        }
        if (check_entity_tile_collision(&l->guard4, l->map, l->tileset, MAP1_TILE_SPIN)) {
            l->guard4.life -= 30;
        }

        if (l->player.x >= 643){
            set_tile(l->map, 18, 12, MAP1_TILE_SPIN);
            l->guard1_Folowing = true;
        } 

        if (l->guard1_Folowing && l->guard1.x != l->player.x) {
            if (!collisionEntityWithEntity(&l->player, &l->guard1)) {
                if (l->guard1.x > l->player.x) {
                    l->guard1flip = ALLEGRO_FLIP_HORIZONTAL;
                    if (!collisionEntityObstacle(&l->guard1, &l->door)) movEntity(&l->guard1, 0);//esquerda
                }
                else {
                    if (l->guard1.x < l->player.x) l->guard1flip = 0;
                    if (!collisionEntityObstacle(&l->guard1, &l->door) && !l->getKey) {
                        movEntity(&l->guard1, 1);//direita
                    }
                }
            }
        }
        if(l->guard1.x == l->player.x) l->guard1flip = 0;

        if(collisionEntityObstacle(&l->player, &l->door)&& !l->getKey)l->player.x -= 10;
        

        if (l->player.x >= 1218) l->guard2_Folowing = true;
        if (l->guard2_Folowing && l->guard2.x != l->player.x && l->guard2.can_jump) {
            if(l->guard2.x == l->player.x) l->guard2flip = 0;
            if (!collisionEntityWithEntity(&l->player, &l->guard2)) {
                if (l->guard2.x > l->player.x) {
                    l->guard2flip = ALLEGRO_FLIP_HORIZONTAL;
                    if (!collisionEntityObstacle(&l->guard2, &l->door) && !check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_WOOD) && l->guard2.can_jump) movEntity(&l->guard2, 0);//esquerda 
                }
                else {
                    l->guard2flip = 0;
                    if (!collisionEntityObstacle(&l->guard2, &l->door) && !l->getKey && !check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_WOOD)&& l->guard2.can_jump) {
                        movEntity(&l->guard2, 1);//direita

                    }
                    if (check_entity_tile_collision(&l->guard2, l->map, l->tileset, MAP1_TILE_WOOD)) l->guard2.y += l->guard2.v;   

                }
            }
        }
        if (l->player.x > 1988) {
            l->guard3_Folowing = true;
            l->guard4_Folowing = true;
           
        }
        if (l->guard3_Folowing) {
            if (!collisionEntityWithEntity(&l->player, &l->guard3) && !collisionEntityObstacle(&l->guard4, &l->door)) {
                if(l->guard3.x == l->player.x) l->guard3flip = 0;
                if (l->guard3.x > l->player.x) {
                    l->guard3flip = ALLEGRO_FLIP_HORIZONTAL;
                    movEntity(&l->guard3, 0);//esquerda
                }
                else {
                    l->guard3flip = 0;
                    movEntity(&l->guard3, 1);//direita
                }

            }
        }
        if(collisionEntityObstacle(&l->guard3, &l->door) || collisionEntityWithEntity(&l->guard3, &l->guard4))l->guard3.x -=10;
        if (l->guard4_Folowing) {
            if (!collisionEntityWithEntity(&l->player, &l->guard4) && !collisionEntityObstacle(&l->guard4, &l->door)) {
                if(l->guard4.x == l->player.x) l->guard4flip = 0;
                if (l->guard4.x > l->player.x) {
                    l->guard4flip = ALLEGRO_FLIP_HORIZONTAL;
                    movEntity(&l->guard4, 0);//esquerda
                }
                else {
                    l->guard4flip = 0;
                    movEntity(&l->guard4, 1);//direita
                }
            }
            if (collisionEntityWithEntity(&l->guard4, &l->guard3)) l->guard4.x += 10;
        }
        if(collisionEntityObstacle(&l->guard4, &l->door))l->guard4.x -=10;



        if (collisionEntityWithEntity(&l->guard1, &l->player) && l->player.life > 0) {
            if (!l->player.modoAtaque) {
                if (!l->player.modoDefesa)
                    if (!l->guard1.isDead)l->player.life -= 1; //tira vida do player
            }
            else {
                if (!l->player.modoDefesa)
                    if (l->guard1.life > 0) l->guard1.life -= 3; //tira vida do inimigo
            }
            
        }

        if (collisionEntityWithEntity(&l->guard2, &l->player) && l->player.life > 0) {
            if (!l->player.modoAtaque) {
                if (!l->player.modoDefesa)
                    if (!l->guard2.isDead)l->player.life -= 1.5; //tira vida do player
            }
            else {
                if (!l->player.modoDefesa)
                    if (l->guard2.life > 0) l->guard2.life -= 3; //tira vida do inimigo
            }
        }

        if (collisionEntityWithEntity(&l->guard3, &l->player) && l->player.life > 0) {
            if (!l->player.modoAtaque) {
                if (!l->player.modoDefesa)
                    if (!l->guard3.isDead)l->player.life -= 3; //tira vida do player
            }
            else {
                if (!l->player.modoDefesa)
                    if (l->guard3.life > 0) l->guard3.life -= 5; //tira vida do inimigo
            }
        }



        if (collisionEntityWithEntity(&l->guard4, &l->player) && l->player.life > 0) {
            if (!l->player.modoAtaque) {
                if (!l->player.modoDefesa)
                    if (!l->guard4.isDead)l->player.life -= 3; //tira vida do player
            }
            else {
                if (!l->player.modoDefesa)
                    if (l->guard4.life > 0) l->guard4.life -= 5; //tira vida do inimigo
            }
        }

        //Os personagens andam para trás quando colidem
        if (collisionEntityWithEntity(&l->player, &l->guard1)) {
            if (l->guard1.x > l->player.x)
            {
                l->guard1.x += ENEMY_PUSHBACK ;
                l->player.x -= ENEMY_PUSHBACK ;
                if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)||check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2)) l->player.y += ENEMY_PUSHBACK ; 
            }
            else {
                if (!(l->player.y > l->guard1.y)) {
                    l->guard1.x -= ENEMY_PUSHBACK ;
                    l->player.x += ENEMY_PUSHBACK ;
                    if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)||check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))l->player.y += 10; 
                }
                else
                    l->guard1.x += ENEMY_PUSHBACK ;
            }
            
        }

        if (collisionEntityWithEntity(&l->player, &l->guard2)) {
            if (l->guard2.x > l->player.x)
            {
                l->guard2.x += ENEMY_PUSHBACK ;
                l->player.x -= ENEMY_PUSHBACK ;
                if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) l->player.y += ENEMY_PUSHBACK ;
            }
            else {
                if (!(l->player.y > l->guard2.y)) {
                    l->guard2.x -= ENEMY_PUSHBACK ;
                    l->player.x += ENEMY_PUSHBACK ;
                    if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))l->player.y += 10;
                }
                else
                    l->guard2.x += ENEMY_PUSHBACK ;
            }
        }

        if (collisionEntityWithEntity(&l->player, &l->guard3)) {
            if (l->guard3.x > l->player.x)
            {
                l->guard3.x += ENEMY_PUSHBACK ;
                l->player.x -= ENEMY_PUSHBACK ;
                if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) l->player.y += ENEMY_PUSHBACK ;
            }
            else {
                if (!(l->player.y > l->guard3.y)) {
                    l->guard3.x -= ENEMY_PUSHBACK ;
                    l->player.x += ENEMY_PUSHBACK ;
                    if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))l->player.y += 10; 
                }
                else
                    l->guard3.x += ENEMY_PUSHBACK ;
            }
        }

        if (collisionEntityWithEntity(&l->player, &l->guard4)) {
            if (l->guard4.x > l->player.x)
            {
                l->guard4.x += ENEMY_PUSHBACK ;
                l->player.x -= ENEMY_PUSHBACK ;
                if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))l->player.y += ENEMY_PUSHBACK ;
            }
            else {
                if (!(l->player.y > l->guard4.y)) {
                    l->guard4.x -= ENEMY_PUSHBACK;
                    l->player.x += ENEMY_PUSHBACK;
                    if(check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))l->player.y += 10; 
                }
                else
                    l->guard4.x += ENEMY_PUSHBACK;
            }
        }


        if ((l->player.x) < 33) l->player.x = 33;
        if ((l->guard1.x) < 33 && !l->guard1.isDead) l->guard1.x = 33;

        //Controles do player
        if (al_key_down(keystate, ALLEGRO_KEY_W) && l->player.can_jump && !check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) {

            l->dirPlayer = 1;
            l->player.y -= PLAYER_GRAVIDADE;
            l->player.vY = PLAYER_JUMP_FORCE;
            l->player.can_jump = false;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL)) {

                l->player.vY += PLAYER_GRAVIDADE;
                l->player.y += l->player.vY;
            }
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD)) {

                l->player.vY = 0;
                l->player.x -= 10;
            }
        }
        if (al_key_down(keystate, ALLEGRO_KEY_A)) {
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
        if (al_key_down(keystate, ALLEGRO_KEY_D)) {
            l->dirPlayer = 3;
            movEntity(&l->player, 1);
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL))
                l->player.x -= l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WALL_2))
                l->player.x -= l->player.v;
            if (check_entity_tile_collision(&l->player, l->map, l->tileset, MAP1_TILE_WOOD))l->player.x -= l->player.v;
            if (collisionEntityObstacle(&l->player, &l->door) && !l->getKey) l->player.x -= l->player.v;
            if (collisionEntityObstacle(&l->player, &l->door) && l->getKey) {
                l->doorSpritePositionX = 32;
            }
        }
    }

    l->hud.displayLife.width = l->player.life;
    l->hud.getKey = l->getKey;

    //Isso é só para debug;
    if (al_key_down(keystate, ALLEGRO_KEY_X))
        printf("x = %d, y = %d \n", l->player.x, l->player.y);
    //Camera segindo o player no eixo X
    l->cameraX = -(l->player.x - SCREEN_WIDTH / 2);

    if (al_key_down(keystate, ALLEGRO_KEY_B)) l->isDone = true;
}



void Level_I_Draw(levelI  l, ALLEGRO_FONT* Font) {
    //desenha o tileMap
    draw_tilemap(l.map, l.tileset, l.cameraX, l.cameraY);
    //drawEntity(&l.player);
    //desenha o texto em cima do npc
    if (collisionEntityWithEntity(&l.player, &l.npc))al_draw_text(Font, TEXT_COLOR, (l.npc.x + l.cameraX) - l.npc.width / 2, l.npc.y - 25, 0, "[E] Falar");
    //desenha o texto em cima do maker
    if (collisionEntityMaker(&l.player, &l.maker))al_draw_text(Font, TEXT_COLOR, (l.maker.x + l.cameraX) - l.maker.size / 2, l.maker.y - 25, 0, "[E] Interagir");



    //desenha o dialogo;
    if (l.inDialogue) drawDialogue(&l.dialogue, Font, l.dialogueOption);
    //desenha o maker
    draw_maker_with_camera(&l.maker, l.cameraX);
    //desenha o npc
    draw_Enity_camera_andImage(&l.npc, l.cameraX, 0);
    // desenha a porta
    drawObstacle(&l.door, l.cameraX, l.doorSpritePositionX, 0);
    //desenha o guarda 1
    if (!l.guard1.isDead)enemyDraw(&l.guard1, l.cameraX, l.guard1flip, 0, 0);
    if (!l.guard2.isDead)enemyDraw(&l.guard2, l.cameraX, l.guard2flip, 0, 0);
    if (!l.guard3.isDead)enemyDraw(&l.guard3, l.cameraX, l.guard3flip, 0, 0);
    if (!l.guard4.isDead)enemyDraw(&l.guard4, l.cameraX, l.guard4flip, 0, 0);
    //desenha a hitbox do player
    //draw_entity_with_camera(&l.player, l.cameraX);
    //desenha o player
    playerDraw(&l.player, l.cameraX, l.PlayerFlip, l.playerSpritepositionX, l.playerSpritepositionY);


    if (l.player.x >= l.door.x - 64 && !l.getKey)al_draw_text(Font, ENEMY_COLOR, SCREEN_WIDTH / 2, 530, ALLEGRO_ALIGN_CENTER, "Você precisa de uma chave");



    //desenha a hud
    drawHud(&l.hud, Font);
}
