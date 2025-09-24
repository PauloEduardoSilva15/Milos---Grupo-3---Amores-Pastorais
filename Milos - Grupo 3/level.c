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




level level_Load() {
	level teste;
	teste.p = playerLoad(); //newEntity(PLAYER_X_0, PLAYER_Y_0, PLAYER_VELOCITY_0, 0, PLAYER_NORMAL_COLOR, true);
	teste.e = enemyLoad();
	teste.f = quad_create(0, SCREEN_HEIGHT - 100, 0, SCREEN_WIDTH, 300, al_map_rgb(0, 255, 0)); // Cria o Chão
	teste.d = obstacleLoad();
	teste.k = newItem(KEY_ITEM_X, KEY_ITEM_Y_0, false);
	return teste;
}

void level_Update(level* l, ALLEGRO_KEYBOARD_STATE* keyState) {
	al_get_keyboard_state(&keyState);
	//l->p.can_jump = false;
	if (!collisionEQ(&l->p, &l->f)&&!collisionE(&l->e, &l->p)) {
		l->p.vY += PLAYER_GRAVIDADE;
		l->p.y += l->p.vY;
	}
	if (collisionEQ(&l->p, &l->f)) {
		l->p.y = l->f.y - l->p.size; // Alinha com o chão
		l->p.vY = 0;
		l->p.can_jump = true;
		if (al_key_down(&keyState, ALLEGRO_KEY_W) && l->p.can_jump) {
			l->p.y -= PLAYER_GRAVIDADE;
			l->p.vY = PLAYER_JUMP_FORCE;
			l->p.can_jump = false;

		}
	}


	if (al_key_down(&keyState, ALLEGRO_KEY_A) && l->p.x > 0  && !collisionE(&l->p, &l->e))
		movEntity(&l->p, 0);
	if (al_key_down(&keyState, ALLEGRO_KEY_D) && l->p.x + l->p.size < SCREEN_WIDTH && !collisionEQ(&l->p, &l->d)  &&!collisionE(&l->p, &l->e))
		movEntity(&l->p, 1);

	if (al_key_down(&keyState, ALLEGRO_KEY_J)) l->p.modoAtaque = true;
	else l->p.modoAtaque = false;

	if (al_key_down(&keyState, ALLEGRO_KEY_K)) l->p.modoDefesa = true;
	else l->p.modoDefesa = false;

	if (l->p.modoAtaque) l->p.color = PLAYER_ATACK_COLOR;
	if (l->p.modoDefesa) l->p.color = PLAYER_DEFENSE_COLOR;
	if (!l->p.modoAtaque && !l->p.modoDefesa)l->p.color = PLAYER_NORMAL_COLOR;

	if (collisionEI(&l->p, &l->k)) {

		l->k.get = true;
	}

	if (l->k.get) {
		l->k.y = 100;

	}
	else {
		l->k.x = KEY_ITEM_X;
		l->k.y = KEY_ITEM_Y_0;

		l->d.y = DOR_Y_0;
	}
	if (collisionEQ(&l->p, &l->d) && l->k.get && l->d.y < 900) l->d.y += 10 * l->d.v;

	if (!collisionE(&l->p, &l->e) && collisionEQ(&l->e, &l->f)) {

		if ((l->e.x > l->p.x)) {
			if (!collisionEQ(&l->e, &l->d))
				movEntity(&l->e, 0);
		}
		else {

			movEntity(&l->e, 1);
		}
	}


	if (!collisionEQ(&l->e, &l->f)) {
		l->e.vY += ENEMY_GRAVIDADE;
		l->e.y += l->e.vY;
	}
	if (collisionEQ(&l->p, &l->f)) {
		l->e.y = l->f.y - l->e.size; // Alinha com o chão
		l->e.vY = 0;
	}
	
	if (collisionE(&l->e, &l->p) && l->p.life > 0) {
		

		if (!l->p.modoAtaque) {
			if (!l->p.modoDefesa) l->p.life -= 1;

		}
		else {
			if (!l->p.modoDefesa) {
				if (l->e.life > 0) {
					l->e.life -= 2;

				}
			}

		}
	}
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
			else {
				l->p.x += 10;
			}
		}

	}

	if ((l->p.x + l->p.size) > SCREEN_WIDTH)
	{
		l->p.x = SCREEN_WIDTH - l->p.size;
	}
	if ((l->e.x + l->e.size) > SCREEN_WIDTH)
	{
		l->e.x = SCREEN_WIDTH - l->e.size;
	}

	if ((l->p.x) < 0)
	{
		l->p.x = 0;
	}
	if ((l->e.x) < 0 )
	{
		l->e.x = 0;
	}


	if (l->p.life <= 0) {

		*l = level_Load();
	}

	
	

}




void Level_Draw(level l) {
	
	drawEntity(&l.p);
	drawEntity(&l.e);
	draw_quad(&l.f);
	draw_quad(&l.d);
	itemDraw(&l.k);
}