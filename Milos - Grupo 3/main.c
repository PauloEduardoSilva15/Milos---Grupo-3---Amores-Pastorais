#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "quad.h"
#include <stdio.h>


int aabb_collision(quad* a, quad* b) {
	return (a->x < b->x + b->w &&
		a->x + a->w > b->x &&
		a->y < b->y + b->h &&
		a->y + a->h > b->y);
}


int main() {

	if (!al_init()) return -1;

	int const fps = 60;
	int sizeWindow[2] = { 800, 600 }; // sizeWindow[0] -> width(largura)   sizeWindow[1] --> height(altura)
	ALLEGRO_DISPLAY* window = al_create_display(sizeWindow[0], sizeWindow[1]); // Cria a janela do jogo

	if (!window) return -1; // Verifica se criou uma janela

	al_init_primitives_addon(); // inicializa os addons adicionais como retângulo, circulo, etc
	al_install_keyboard(); // inicializa o teclado

	bool done = false, draw = true; // Verifica se o jogo está rodando e declara se pode desenhar na tela

	//int dir = -1;

	int gravidade = 10;

	float velY = 0;                  // Velocidade vertical
	const float GRAVITY = 1.0;       // Gravidade aplicada por frame
	const float JUMP_FORCE = -15.0;  // Força do pulo
	bool can_jump = false;           // Controle de pulo


	bool get_ob = false;

	bool enemyDeath = false;

	bool modoAtaque = false, modoDefesa = false;


	quad player = quad_create((sizeWindow[0] / 2) - 32, 300, 5, 32, 32, 100, al_map_rgb(0, 0, 255)); // Cria o Jogador
	quad flor = quad_create(0, sizeWindow[1] - 100, 0, sizeWindow[0], 300, 0, al_map_rgb(0, 255, 0)); // Cria o Chão
	quad enemy = quad_create(770 - 32, 300, 5, 32, 32, 100, al_map_rgb(255, 0, 0));
	quad door = quad_create(600, 300, 10, 32, 200, 0, al_map_rgb(150, 50, 0)); // Cria o Chão

	int obX = 100, obY = 484;
	quad ob = quad_create(obX, obY, 0, 16, 16, 0, al_map_rgb(255, 255, 0));

	quad life_player = quad_create(100, 50, 0, player.life, 32, 0, al_map_rgb(0, 255, 0));
	quad life_enemy = quad_create(600, 50, 0, enemy.life, 32, 0, al_map_rgb(0, 255, 0));

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / fps);
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

			if (!aabb_collision(&player, &flor) && !aabb_collision(&player, &enemy)) {
				velY += GRAVITY;
				player.y += velY;
			}



			if (al_key_down(&keyState, ALLEGRO_KEY_A) && player.x > 0 && !aabb_collision(&player, &enemy))
				mov_quad(&player, 0);
			if (al_key_down(&keyState, ALLEGRO_KEY_D) && player.x + player.w < sizeWindow[0] && !aabb_collision(&player, &door) && !aabb_collision(&player, &enemy))
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



			if (modoAtaque) player.color = al_map_rgb(100, 0, 200);
			if (modoDefesa) player.color = al_map_rgb(180, 0, 200);

			if (!modoAtaque && !modoDefesa)player.color = al_map_rgb(0, 0, 255);


			if (aabb_collision(&player, &ob)) {

				get_ob = true;
			}

			if (get_ob) {
				ob.x = 100;
				ob.y = 100;

			}
			else {
				ob.x = obX;
				ob.y = obY;

				door.y = 300;
			}

			if (aabb_collision(&player, &door) && get_ob && door.y < 600)
				door.y += 70;




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
			life_enemy.w = enemy.life;

			if (aabb_collision(&player, &enemy) && player.life > 0) {
				if (!modoAtaque) {
					if (!modoDefesa) {
						if (!enemyDeath)
							player.life -= 5 / 5;

					}
				}
				else {
					if (!modoDefesa) {
						if (enemy.life > 0) {
							enemy.life -= 5 / 5;

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

			if ((player.x + player.h) > sizeWindow[0])
			{
				player.x = sizeWindow[0] - player.h;
			}
			if ((enemy.x + enemy.h) > sizeWindow[0] && !enemyDeath)
			{
				enemy.x = sizeWindow[0] - enemy.h;
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
				/*player.x = (sizeWindow[0] / 2) - 32;
				player.y = 300;
				player.life = 100;

				enemy.x = 770 - 32;
				enemy.y = 300;
				enemy.life = 100;*/

				player = quad_create((sizeWindow[0] / 2) - 32, 300, 5, 32, 32, 100, al_map_rgb(0, 0, 255));
				enemy = quad_create(770 - 32, 300, 5, 32, 32, 100, al_map_rgb(255, 0, 0));
				get_ob = false;
			}

			if (enemy.life <= 0) enemyDeath = true;

			if (enemyDeath) {
				enemy.x = 0;
				enemy.y = 0;
			}

			draw = true;

		}
		if (draw) {
			draw = false;
			draw_quad(&ob);
			draw_quad(&player);
			if (!enemyDeath) draw_quad(&enemy);
			draw_quad(&flor);
			draw_quad(&life_player);
			draw_quad(&life_enemy);
			draw_quad(&door);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_display(window);
	al_destroy_timer(timer);
	al_destroy_event_queue(events);

	return 0;
}