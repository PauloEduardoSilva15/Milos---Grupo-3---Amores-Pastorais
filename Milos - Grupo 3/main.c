#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "quad.h"
#include <stdio.h>


int aabb_collision(quad* a, quad* b) {
	return (a->x < b->x + b->size &&
		a->x + a->size > b->x &&
		a->y < b->y + b->size &&
		a->y + a->size > b->y);
}


int main() {

	if (!al_init()) return -1;

	int sizeWindow[2] = { 800, 600 }; // sizeWindow[0] -> width(largura)   sizeWindow[1] --> height(altura)
	ALLEGRO_DISPLAY* window = al_create_display(sizeWindow[0], sizeWindow[1]); // Cria a janela do jogo

	if (!window) return -1; // Verifica se criou uma janela

	al_init_primitives_addon(); // inicializa os addons adicionais como retângulo, circulo, etc
	al_install_keyboard(); // inicializa o teclado

	bool done = false, draw = true; // Verifica se o jogo está rodando e declara se pode desenhar na tela

	//int dir = -1;

	int gravidade = 10;

	bool ground, jumping = false, get_ob = false;
	


	quad player = quad_create((sizeWindow[0]/2)-32, 400, 5, 32, al_map_rgb(0, 0, 255)); // Cria o Jogador
	quad flor = quad_create(0, sizeWindow[1]-100, 0, sizeWindow[0], al_map_rgb(0, 255,0)); // Cria o Chão

	quad door = quad_create(600, 400, 10, 100, al_map_rgb(150, 50, 0)); // Cria o Chão
	quad ob = quad_create(100, 484, 0, 16, al_map_rgb(255, 255, 0));

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
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



		if(ev.type == ALLEGRO_EVENT_TIMER){
			
			al_get_keyboard_state(&keyState);

			if (al_key_down(&keyState, ALLEGRO_KEY_A) && player.x > 0)
				mov_quad(&player, 0);
			if (al_key_down(&keyState, ALLEGRO_KEY_D) && player.x + player.size < sizeWindow[0] && !aabb_collision(&player, &door))
				mov_quad(&player, 1);

			if (al_key_down(&keyState, ALLEGRO_KEY_W) && aabb_collision(&player, &flor)) {
				player.y -= gravidade;
				
			}
			if (aabb_collision(&player, &ob)) {
				ob.y = 100;
				ob.x = 100;
				get_ob = true;
			}

			if (aabb_collision(&player, &door) && get_ob && door.y < 600)
				door.y += 10;


			if (!aabb_collision(&player, &flor)) {
				player.y += gravidade;
				ground = false;
			}
			else {
				ground = true;
			}
		        
			draw = true;
			
		}
		if (draw) {
			draw = false;
			draw_quad(&ob);
			draw_quad(&player);
			draw_quad(&flor);
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