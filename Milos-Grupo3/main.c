#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "gameConstants.h"
#include <stdio.h>
//#include "level.h"
#include "Level001.h"
#include "puzzle.h"
#include "systemTileset.h"
#include <stdio.h>
#include "TitleMenu.h"
#include "gameover.h"
#include "gamePauseMenu.h"





int main() {

	if (!al_init()) return -1;


	ALLEGRO_DISPLAY* window = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); // Cria a janela do jogo
	al_set_window_title(window, TITLE);
	if (!window) return -1; // Verifica se criou uma janela

	al_init_image_addon(); // inicializa o addon de imagens
	al_init_primitives_addon(); // inicializa os addons adicionais como retângulo, circulo, etc
	al_install_keyboard(); // inicializa o teclado
	al_install_mouse(); // inicia o mouse
	al_init_font_addon(); // inicializa o addon de fontes
    al_init_ttf_addon(); // inicializa o addon de fontes ttf


	bool done = false, draw = true; // Verifica se o jogo está rodando e declara se pode desenhar na tela
	


	// No início do programa
	//puzzle_init();

	levelI levelT = Level_I_load();

	ALLEGRO_FONT* Font = al_create_builtin_font();

	
	
	TitleMenu titleMenu = createTitleMenu(Font);
	GameOver gameOver = createGameOver(Font);

	PauseMenu pauseMenu = createPauseMenu(Font);

	ALLEGRO_MOUSE_STATE mouseState;
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

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			

			al_get_keyboard_state(&keyState);
			al_get_mouse_state(&mouseState);
			//titleMenu.selectedOption = ReturnMenuOption(titleMenu, &mouseState, &ev);
			
			if(titleMenu.selectedOption == 1 && !levelT.player.isDead) level_I_Update(&levelT, &keyState);
			if(titleMenu.selectedOption == 2) done = true;
			draw = true;
			if (levelT.player.isDead) gameOver.active = true;
			//if(levelT.inPause) drawPauseMenu(&pauseMenu);

			if(levelT.isDone){
				titleMenu = createTitleMenu(Font);
				levelT = Level_I_load();
				pauseMenu = createPauseMenu(Font);
				gameOver = createGameOver(Font);
			}
		}
		if (draw) {
				
			draw = false;
				

			if(!titleMenu.runningLevel)drawTitleMenu(&titleMenu, &mouseState);
			if (titleMenu.selectedOption == 1 && !gameOver.active)Level_I_Draw(levelT, Font);
			if (gameOver.active) drawGameOver(&gameOver, &mouseState);
			

				
			if(levelT.inPause && !levelT.inDialogue) drawPauseMenu(&pauseMenu, &mouseState);

			// Tutorial Controls
			al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 50, 0, "Controles:");
			al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 60, 0, "W - Pular");
			al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 70, 0, "A - Esquerda");
			al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 80, 0, "D - Direita");
			al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 90, 0, "E - Interagir");
			al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 100, 0, "J - Ataque");
			al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 110, 0, "K - Defesa");

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (button_contains_point(&titleMenu.startGameButton, mouseState.x, mouseState.y)) {
				titleMenu.runningLevel = true;
				titleMenu.selectedOption = 1; // Start Game
			}
			else {
				if (button_contains_point(&titleMenu.exitButton, mouseState.x, mouseState.y))
					titleMenu.selectedOption = 2; // Exit
			}

			if (button_contains_point(&gameOver.retryButton, mouseState.x, mouseState.y) && gameOver.active) {
				//gameOver.active = false;
				titleMenu = createTitleMenu(Font);
				levelT = Level_I_load();
				pauseMenu = createPauseMenu(Font);
				gameOver = createGameOver(Font);
			}
			else {
				if (button_contains_point(&gameOver.exitButton, mouseState.x, mouseState.y) && gameOver.active)
					done = true;
			}

			if (button_contains_point(&pauseMenu.retriviedbutton, mouseState.x, mouseState.y) && levelT.inPause) {
				titleMenu = createTitleMenu(Font);
				levelT = Level_I_load();
				gameOver = createGameOver(Font);
			}
			else {
				if (button_contains_point(&pauseMenu.ContinuePlaybutton, mouseState.x, mouseState.y) && levelT.inPause)
					levelT.inPause = false;
				if (button_contains_point(&pauseMenu.exitButton, mouseState.x, mouseState.y) && levelT.inPause)
					done = true;
			}
			
		}

		if(ev.type ==  ALLEGRO_EVENT_KEY_DOWN){
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE && titleMenu.runningLevel&& !gameOver.active) {
				levelT.inDialogue = false;
				levelT.inPause = true;
				//done = true; // Sai do jogo com ESC
			}

			if (levelT.inDialogue && ev.keyboard.keycode == ALLEGRO_KEY_T && (levelT.dialogueOption != 5 || levelT.dialogueOption != 9))
				levelT.dialogueOption++;
			
		}


		//if (levelT.puzzle_solved) puzzle_init();
		/*if (levelT.puzzle_open)
		{
			// Se puzzle está aberto, envia eventos apenas para o puzzle
			
			puzzle_handle_event(&ev);
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (levelT.puzzle_open) {
				// O puzzle será atualizado no main loop através de puzzle_handle_event
					if (puzzle_is_solved()) {
						levelT.puzzle_open = false;
						levelT.puzzle_solved = puzzle_is_solved();
						puzzle_destroy(); // Limpa o puzzle após resolver
						levelT.k.get = true;
					
					}
				}
				draw = true;
			}
			if (draw) {
				//al_draw_text(Font, TEXT_COLOR, 25, 25, 0, VERSION);
				if(!puzzle_is_solved())puzzle_draw(SCREEN_WIDTH, SCREEN_HEIGHT);

				al_draw_text(Font, TEXT_COLOR, 50, SCREEN_HEIGHT-100, 0, "Controles:");
				al_draw_text(Font, TEXT_COLOR, 50, SCREEN_HEIGHT-80, 0, "R - Sair do Puzzle");


				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				draw = false;
			}
		}
		else {
			// Se puzzle não está aberto, processa eventos normais do jogo
			if (ev.type == ALLEGRO_EVENT_TIMER) {

				al_get_keyboard_state(&keyState);
				al_get_mouse_state(&mouseState);
				//titleMenu.selectedOption = ReturnMenuOption(titleMenu, &mouseState, &ev);
				
				if(titleMenu.selectedOption == 1) level_Update(&levelT, &keyState);
				if(titleMenu.selectedOption == 2) done = true;
				draw = true;

			}
			if (draw) {
				
				draw = false;
				

				if(!titleMenu.runningLevel)drawTitleMenu(&titleMenu, &mouseState);
				if (titleMenu.selectedOption == 1)Level_Draw(levelT, Font);

				
				al_draw_text(Font, TEXT_COLOR, 25, 25, 0, VERSION);

				// Tutorial Controls
				al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 50, 0, "Controles:");
				al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 60, 0, "W - Pular");
				al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 70, 0, "A - Esquerda");
				al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 80, 0, "D - Direita");
				al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 90, 0, "E - Interagir");
				al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 100, 0, "J - Ataque");
				al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 110, 0, "K - Defesa");

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (levelT.puzzle_open && ev.keyboard.keycode == ALLEGRO_KEY_R) {
				levelT.puzzle_open = false; 
			}
			
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) done = true; // Fecha o jogo se clicar no X da janela
		
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				
				if (levelT.puzzle_open) {
					levelT.puzzle_open = false;
				}
				done = true; // Sai do jogo com ESC
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (button_contains_point(&titleMenu.startGameButton, mouseState.x, mouseState.y)) {
				titleMenu.runningLevel = true;
				titleMenu.selectedOption = 1; // Start Game
			}
			else {
				if (button_contains_point(&titleMenu.exitButton, mouseState.x, mouseState.y))
					titleMenu.selectedOption = 2; // Exit
			}
		}
	*/
	}
	destroy_tileset(levelT.tileset);
	destroy_tilemap(levelT.map);
	al_destroy_bitmap(levelT.player.sprite);
	al_destroy_bitmap(levelT.npc.sprite);
	al_destroy_bitmap(titleMenu.bg);
	al_destroy_bitmap(titleMenu.logo);
	al_destroy_display(window);
	al_destroy_timer(timer);
	al_destroy_event_queue(events);
	
	return 0;
}
