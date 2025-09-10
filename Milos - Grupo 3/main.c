#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "quad.h"
#include <stdio.h>

int main() {

	if (!al_init()) return -1;

	int sizeWindow[2] = { 800, 600 }; // sizeWindow[0] -> width(largura)   sizeWindow[1] --> height(altura)
	ALLEGRO_DISPLAY* window = al_create_display(sizeWindow[0], sizeWindow[1]); // Cria a janela do jogo

	if (!window) return -1; // Verifica se criou uma janela

	al_init_primitives_addon(); // inicializa os addons adicionais como retângulo, circulo, etc
	al_install_keyboard(); // inicializa o teclado

	bool done = false, draw = true; // Verifica se o jogo está rodando e declara se pode desenhar na tela

	int dir = -1;

	quad player = quad_create(100, 100, 10, 32); // Cria o Jogador
	quad flor = quad_create(0, sizeWindow[1]-100, 0, sizeWindow[0]); // Cria o Chão

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

		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_A: // Move para esquerda
			mov_quad(&player, 0);
			break;
		case ALLEGRO_KEY_D: // Move para direita
			mov_quad(&player, 1);
			break;
		}

		if(ev.type == ALLEGRO_EVENT_TIMER){
			
			

			if (player.y + player.size < flor.y)
				player.y += 10;
			draw = true;

			
		}
		if (draw) {
			draw = false;
			draw_quad(&player);
			draw_quad(&flor);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}



		

		
		
	}

	al_destroy_display(window);
	al_destroy_event_queue(events);

	return 0;
}