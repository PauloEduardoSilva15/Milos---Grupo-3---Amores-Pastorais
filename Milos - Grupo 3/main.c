#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "gameConstants.h"
#include "quad.h"
#include "entity.h"
#include "collision.h"
#include "player.h"
#include "level.h"
#include <stdio.h>






int main() {

	if (!al_init()) return -1;


	ALLEGRO_DISPLAY* window = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); // Cria a janela do jogo

	if (!window) return -1; // Verifica se criou uma janela

	al_init_primitives_addon(); // inicializa os addons adicionais como retângulo, circulo, etc
	al_install_keyboard(); // inicializa o teclado

	bool done = false, draw = true; // Verifica se o jogo está rodando e declara se pode desenhar na tela


	//entity a = newEntity(400, 0, 0, 0,PLAYER_NORMAL_COLOR, true);

	/*
	int gravidade = 10;

	float velYE = 0;
	float velY = 0;                  // Velocidade vertical
	const float GRAVITY = 1.0;       // Gravidade aplicada por frame
	const float JUMP_FORCE = -15.0;  // Força do pulo
	bool can_jump = false;           // Controle de pulo


	bool get_ob = false;

	bool enemyDeath = false;

	bool modoAtaque = false, modoDefesa = false;

	
    
	quad player = quad_create(PLAYER_X_0, PLAYER_Y_0, PLAYER_VELOCITY_0, QUAD_SIZE, QUAD_SIZE, MAXLIFE_0, PLAYER_NORMAL_COLOR); // Cria o Jogador
	quad flor = quad_create(0, SCREEN_HEIGHT - 100, 0, SCREEN_WIDTH, 300, 0, al_map_rgb(0, 255, 0)); // Cria o Chão
	quad enemy = quad_create(ENEMY_X_0, ENEMY_Y_0, ENEMY_VELOCITY_0, QUAD_SIZE, QUAD_SIZE, MAXLIFE_0, ENEMY_COLOR);
	quad door = quad_create(DOR_X, DOR_Y_0, DOR_VELOCITY_0, QUAD_SIZE, DOOR_HEIGHT, 0, DOR_COLOR); // Cria o Chão

	int obX = 100, obY = 484;
	quad ob = quad_create(KEY_ITEM_X_0, KEY_ITEM_Y_0, 0, ITENS_QUAD_SIZE, ITENS_QUAD_SIZE, 0, KEY_ITEM_COLOR);

	quad life_player = quad_create(100, 50, 0, player.life, 32, 0, al_map_rgb(0, 255, 0));

	*/

	//entity player = 
	level levelT = level_Load();
	

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE* events = al_create_event_queue(); // Evento Principal
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (!done) {

		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done = true; // O Loop Acaba quando pressiona o ESC

		}



		if (ev.type == ALLEGRO_EVENT_TIMER) {

			al_get_keyboard_state(&keyState);

			/*
			

			if (!aabb_collision(&player, &flor) && !aabb_collision(&player, &enemy)) {
				velY += GRAVITY;
				player.y += velY;
			}



			if (al_key_down(&keyState, ALLEGRO_KEY_A) && player.x > 0 && !aabb_collision(&player, &enemy))
				mov_quad(&player, 0);
			if (al_key_down(&keyState, ALLEGRO_KEY_D) && player.x + player.w < SCREEN_WIDTH && !aabb_collision(&player, &door) && !aabb_collision(&player, &enemy))
				mov_quad(&player, 1);

			if (al_key_down(&keyState, ALLEGRO_KEY_W) && aabb_collision(&player, &flor) && can_jump) {
				player.y -= GRAVITY;
				velY = JUMP_FORCE;
				can_jump = false;

			}

			if (al_key_down(&keyState, ALLEGRO_KEY_J)) {
				modoAtaque = true;

			}
			else {
				modoAtaque = false;
			}




			if (al_key_down(&keyState, ALLEGRO_KEY_K)) {
				modoDefesa = true;

			}
			else {
				modoDefesa = false;

			}



			if (modoAtaque) player.color = PLAYER_ATACK_COLOR;
			if (modoDefesa) player.color = PLAYER_DEFENSE_COLOR;

			if (!modoAtaque && !modoDefesa)player.color = PLAYER_NORMAL_COLOR;


			if (aabb_collision(&player, &ob)) {

				get_ob = true;
			}

			if (get_ob) {
				ob.y = 100;

			}
			else {
				ob.x = KEY_ITEM_X_0;
				ob.y = KEY_ITEM_Y_0;

				door.y = DOR_Y_0;
			}

			if (aabb_collision(&player, &door) && get_ob && door.y < 600)
				door.y += door.vel;




			if (aabb_collision(&player, &flor)) {
				player.y = flor.y - player.h; // Alinha com o chão
				velY = 0;
				can_jump = true;
			}

			if (!aabb_collision(&enemy, &player) && aabb_collision(&enemy, &flor) && !enemyDeath) {

				if ((enemy.x > player.x)) {
					if (!aabb_collision(&enemy, &door))
						mov_quad(&enemy, 0);
				}
				else {

					mov_quad(&enemy, 1);
				}
			}


			if (!aabb_collision(&enemy, &flor) && !enemyDeath) {

				enemy.y += gravidade;
			}


			life_player.w = player.life;

			if (aabb_collision(&player, &enemy) && player.life > 0) {
				if (!modoAtaque) {
					if (!modoDefesa) {
						if (!enemyDeath)
							player.life -= 1;

					}
				}
				else {
					if (!modoDefesa) {
						if (enemy.life > 0) {
							enemy.life -= 2;

						}
					}

				}

				if (enemy.x > player.x)
				{
					enemy.x += 10;
					player.x -= 10;
				}
				else {
					if (!(player.y > enemy.y)) {
						enemy.x -= 10;
						player.x += 10;
					}
					else {
						player.x += 10;
					}
				}
			}

			if ((player.x + player.h) > SCREEN_WIDTH)
			{
				player.x = SCREEN_WIDTH - player.h;
			}
			if ((enemy.x + enemy.h) > SCREEN_WIDTH && !enemyDeath)
			{
				enemy.x = SCREEN_WIDTH - enemy.h;
			}

			if ((player.x) < 0)
			{
				player.x = 0;
			}
			if ((enemy.x) < 0 && !enemyDeath)
			{
				enemy.x = 0;
			}



			if (player.life <= 0) {

				player = quad_create(PLAYER_X_0, PLAYER_Y_0, PLAYER_VELOCITY_0, QUAD_SIZE, QUAD_SIZE, MAXLIFE_0, PLAYER_NORMAL_COLOR);
				enemy = quad_create(ENEMY_X_0, ENEMY_Y_0, ENEMY_VELOCITY_0, QUAD_SIZE, QUAD_SIZE, MAXLIFE_0, ENEMY_COLOR);
				get_ob = false;
			}

			if (enemy.life <= 0) enemyDeath = true;

			if (enemyDeath) {
				enemy.x = 0;
				enemy.y = 0;
			}
			*/
			draw = true;

		}
		if (draw) {
			draw = false;
			Level_Draw(levelT);
			/*
			draw_quad(&ob);
			draw_quad(&player);
			if (!enemyDeath) draw_quad(&enemy);
			draw_quad(&flor);
			draw_quad(&life_player);
			draw_quad(&door);
			*/
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

		}
	}

	al_destroy_display(window);
	al_destroy_timer(timer);
	al_destroy_event_queue(events);

	return 0;
}
