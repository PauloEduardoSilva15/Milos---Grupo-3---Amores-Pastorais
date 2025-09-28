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

			//al_get_keyboard_state(&keyState);

			level_Update(&levelT, &keyState);
			draw = true;

		}
		if (draw) {
			draw = false;
			Level_Draw(levelT);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

		}
	}

	al_destroy_display(window);
	al_destroy_timer(timer);
	al_destroy_event_queue(events);

	return 0;
}
