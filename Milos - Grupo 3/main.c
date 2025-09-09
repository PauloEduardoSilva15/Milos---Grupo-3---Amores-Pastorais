#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

int main() {

	if (!al_init()) return -1;

	int sizeWindow[2] = { 800, 600 }; // sizeWindow[0] -> width(largura)   sizeWindow[1] --> height(altura)
	ALLEGRO_DISPLAY* window = al_create_display(sizeWindow[0], sizeWindow[1]); // Cria a janela do jogo

	if (!window) return -1; // Verifica se criou uma janela

	al_init_primitives_addon(); // inicializa os addons adicionais como retângulo, circulo, etc
	al_install_keyboard(); // inicializa o teclado

	bool done = false; // Verifica se o jogo está rodando

	ALLEGRO_EVENT_QUEUE* events = al_create_event_queue(); // Evento Principal
	al_register_event_source(events, al_get_keyboard_event_source());

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done = true; // O Loop Acaba quando pressiona o ESC
		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a Tela
	}

	al_destroy_display(window);
	al_destroy_event_queue(events);

	return 0;
}