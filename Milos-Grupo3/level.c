#include "level.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "gameConstants.h"
#include "quad.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "obstacle.h"
#include "item.h"
#include "collision.h"
#include <math.h>

// Carrega o level
level level_Load() {
	level teste;//declara o level
	teste.p = playerLoad(); //carrega o player
	teste.e = enemyLoad(); //carrega o inimigo
	teste.npc = newEntity(190, 500 - 32, 0, 0, al_map_rgb(100, 0, 150), false);
	teste.f = quad_create(0, SCREEN_HEIGHT - 100, 0, SCREEN_WIDTH, 300, al_map_rgb(0, 255, 0)); // Carrega o Ch�o
	teste.d = obstacleLoad();//carrega a porta
	teste.dL = quad_create(DISPLAY_LIFE_X, DISPLAY_LIFE_Y, 0, MAXLIFE_0, QUAD_SIZE, al_map_rgb(0, 255, 0)); // Carrega a barra de vida
	teste.textBox = dialogueLoad();
	teste.inDialogue = false;
	teste.k = newItem(KEY_ITEM_X, KEY_ITEM_Y_0, false);//carrega a chave
	teste.m = newMarker(MARKER_X, MARKER_Y); // Carrega o marcador
	teste.puzzle_open = false; //inicia com o puzzle fechado
	teste.puzzle_solved = false; //inicia com o puzzle n�o resolvido
	teste.show_interact_text = false; //inicia sem mostrar o texto de interação
	teste.dialogueOption = 0;
	teste.dialogoTermindado = false;
	return teste;
}

// Atualiza o level
void level_Update(level* l, ALLEGRO_KEYBOARD_STATE* keyState, ALLEGRO_EVENT ev) {

	if(al_key_down(keyState, ALLEGRO_KEY_E) && collisionE(&l->p, &l->npc)){
		l->inDialogue = true;
	}
	if(al_key_down(keyState, ALLEGRO_KEY_R)){
		l->inDialogue = false;
	}

	if(l->inDialogue && al_key_down(keyState, ALLEGRO_KEY_T) && l->dialogueOption < 2) {
		l->dialogueOption++;
		
	}
	if(l->dialogueOption >= 2){
		l->dialogueOption = 0;
	} 
	

	
	
	// Verifica colisão com marker
	l->show_interact_text = collisionEM(&l->p, &l->m);

	// Abre puzzle quando colide com marker e pressiona E
	if (l->show_interact_text && al_key_down(keyState, ALLEGRO_KEY_E) && !l->puzzle_solved) {
		l->puzzle_open = true;
	}


	// GRAVIDADE E PULO
	if (!collisionEQ(&l->p, &l->f) && !collisionE(&l->e, &l->p)) {
		l->p.vY += PLAYER_GRAVIDADE;
		l->p.y += l->p.vY;
	}

	if (collisionEQ(&l->p, &l->f)) {
		l->p.y = l->f.y - l->p.size;
		l->p.vY = 0;
		l->p.can_jump = true;
		if (al_key_down(keyState, ALLEGRO_KEY_W) && l->p.can_jump) {
			l->p.y -= PLAYER_GRAVIDADE;
			l->p.vY = PLAYER_JUMP_FORCE;
			l->p.can_jump = false;
		}
	}

	if (!collisionEQ(&l->e, &l->f) && !l->e.isDead) {
		l->e.vY += ENEMY_GRAVIDADE;
		l->e.y += l->e.vY;
	}
	if (collisionEQ(&l->p, &l->f) && !l->e.isDead) {
		l->e.y = l->f.y - l->e.size; // Alinha com o chão
		l->e.vY = 0;
	}

	//verifica colisao com a chave e a porta
	if (collisionEI(&l->p, &l->k)) l->k.get = true;
	if (l->k.get) {
		l->k.x = 100;
		l->k.y = 100;
	}
	if (!l->k.get) {
		l->k.x = KEY_ITEM_X;
		l->k.y = KEY_ITEM_Y_0;
		l->d.y = DOR_Y_0;
	}
	if (collisionEQ(&l->p, &l->d) && l->k.get && l->d.y < 900) l->d.y += 10 * l->d.v;

	// CONTROLES DO PLAYER
	if (!l->puzzle_open) {
		// movimenta o player
		if (!collisionE(&l->p, &l->e)) {
			if (al_key_down(keyState, ALLEGRO_KEY_A))
				movEntity(&l->p, 0);
			if (al_key_down(keyState, ALLEGRO_KEY_D) && !collisionEQ(&l->p, &l->d))
				movEntity(&l->p, 1);
		}
		// modo ataque e defesa
		if (al_key_down(keyState, ALLEGRO_KEY_J)) l->p.modoAtaque = true;
		else l->p.modoAtaque = false;
		if (al_key_down(keyState, ALLEGRO_KEY_K)) l->p.modoDefesa = true;
		else l->p.modoDefesa = false;
	}

	if (l->p.modoAtaque) l->p.color = PLAYER_ATACK_COLOR;//muda a cor do player NO MODO ATAQUE
	if (l->p.modoDefesa) l->p.color = PLAYER_DEFENSE_COLOR;//muda a cor do player NO MODO DEFESA
	if (!l->p.modoAtaque && !l->p.modoDefesa)l->p.color = PLAYER_NORMAL_COLOR;//muda a cor do player NO MODO NORMAL

	




	//movimenta o inimigo
	if (!collisionE(&l->p, &l->e) && collisionEQ(&l->e, &l->f) && !l->e.isDead) {
		if (l->e.x > l->p.x) {
			if (!collisionEQ(&l->e, &l->d)) movEntity(&l->e, 0);//esquerda
		}
		else movEntity(&l->e, 1);//direita
	}

	l->dL.w = l->p.life; //atualiza a barra de vida do player

	//verifica colisao entre player e inimigo
	if (collisionE(&l->e, &l->p) && l->p.life > 0) {
		if (!l->p.modoAtaque) {
			if (!l->p.modoDefesa)
				if (!l->e.isDead)l->p.life -= 3; //tira vida do player
		}
		else {
			if (!l->p.modoDefesa)
				if (l->e.life > 0) l->e.life -= 3; //tira vida do inimigo
		}
	}

	//Os personagens andam para trás quando colidem
	if (collisionE(&l->p, &l->e)) {
		if (l->e.x > l->p.x)
		{
			l->e.x += 10;
			l->p.x -= 10;
		}
		else {
			if (!(l->p.y > l->e.y)) {
				l->e.x -= 10;
				l->p.x += 10;
			}
			else
				l->p.x += 10;
		}
	}

	//impede que os personagens saiam da tela
	if ((l->p.x + l->p.size) > SCREEN_WIDTH) l->p.x = SCREEN_WIDTH - l->p.size;
	if ((l->e.x + l->e.size) > SCREEN_WIDTH && !l->e.isDead) l->e.x = SCREEN_WIDTH - l->e.size;
	if ((l->p.x) < 0) l->p.x = 0;
	if ((l->e.x) < 0 && !l->e.isDead) l->e.x = 0;

	//verifica se alguem morreu
	if (l->p.life <= 0) *l = level_Load();
	if (l->e.life <= 0) l->e.isDead = true;
	if (l->e.isDead) {
		l->e.x = 0;
		l->e.y = 0;
	}

}

// Desenha o level
void Level_Draw(level l, ALLEGRO_FONT* Font) {

	
	MarkerDraw(&l.m);

	drawEntity(&l.npc);
	drawEntity(&l.p);

	
	// Mostra texto de interação apenas quando perto do marker

	if(collisionEM(&l.p, &l.m)&& !l.puzzle_solved) al_draw_text(Font, TEXT_COLOR, l.m.x-25, l.m.y - 25, 0, "[E] Interagir");
	if (!l.e.isDead) drawEntity(&l.e);

	if (collisionE(&l.p, &l.npc))al_draw_text(Font, TEXT_COLOR, l.npc.x - 25, l.npc.y - 25, 0, "[E] Falar");
	draw_quad(&l.dL);
	draw_quad(&l.f);
	draw_quad(&l.d);
	itemDraw(&l.k);
	if(l.inDialogue) drawDialogue(&l.textBox, Font, l.dialogueOption);
}
