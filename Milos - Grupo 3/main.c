#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "gameConstants.h"
#include <stdio.h>
#include "level.h"
#include "puzzle.h"
#include <stdio.h>






int main() {

	if (!al_init()) return -1;


	ALLEGRO_DISPLAY* window = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); // Cria a janela do jogo

	if (!window) return -1; // Verifica se criou uma janela

	al_init_primitives_addon(); // inicializa os addons adicionais como retângulo, circulo, etc
	al_install_keyboard(); // inicializa o teclado
	al_install_mouse();
	al_init_font_addon(); // inicializa o addon de fontes
    al_init_ttf_addon(); // inicializa o addon de fontes ttf


	bool done = false, draw = true; // Verifica se o jogo está rodando e declara se pode desenhar na tela

	// No início do programa
	puzzle_init();

	level levelT = level_Load();

	ALLEGRO_FONT* Font = al_create_builtin_font();
	

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE* events = al_create_event_queue(); // Evento Principal
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_timer_event_source(timer));
	al_register_event_source(events, al_get_mouse_event_source());

	al_start_timer(timer);

	while (!done) {

		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);

		if (levelT.puzzle_open) {
			// Se puzzle está aberto, envia eventos apenas para o puzzle
			puzzle_handle_event(&ev);
		}
		else {
			// Se puzzle não está aberto, processa eventos normais do jogo
			if (ev.type == ALLEGRO_EVENT_TIMER) {

				al_get_keyboard_state(&keyState);

				level_Update(&levelT, &keyState);
				draw = true;

			}
			if (draw) {
				al_draw_text(Font, TEXT_COLOR, 25, 25, 0, VERSION);
				draw = false;
				Level_Draw(levelT, Font);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				if (levelT.puzzle_open) {
					levelT.puzzle_open = false; // Fecha puzzle com ESC
				}
				else {
					done = true; // Sai do jogo com ESC
				}
			}
		}
		/*
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done = true; // O Loop Acaba quando pressiona o ESC

		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//al_get_keyboard_state(&keyState);

			level_Update(&levelT, &keyState);
			draw = true;

		}
		if (draw) {
			al_draw_text(Font, TEXT_COLOR, 25, 25, 0, VERSION);
			draw = false;
			Level_Draw(levelT, Font);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

		}
		*/
	}

	al_destroy_display(window);
	al_destroy_timer(timer);
	al_destroy_event_queue(events);

	return 0;
}
