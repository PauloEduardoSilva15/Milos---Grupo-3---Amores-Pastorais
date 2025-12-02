#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "gameConstants.h"
#include <stdio.h>
#include "Level001.h"
#include "Level002.h"
#include "level003.h"
#include "puzzle.h"
#include "systemTileset.h"
#include "TitleMenu.h"
#include "gameover.h"
#include "gamePauseMenu.h"
#include "minigame.h"





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
	
	ALLEGRO_BITMAP* icon = al_load_bitmap("./imgs/icon.png");

	al_set_display_icon(window, icon);
	bool done = false, draw = true; // Verifica se o jogo está rodando e declara se pode desenhar na tela
	ALLEGRO_FONT* Font = al_create_builtin_font();
	puzzle_init();

	levelI level1 = Level_I_load();
	levelII level2 = Level_II_load();
	levelIII level3 = Level_III_load();
	TitleMenu titleMenu = createTitleMenu(Font);
	GameOver gameOver = createGameOver(Font);
	minigame minigame = loadMinigame(Font);


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

		//if (level1.puzzle_isSolved) puzzle_init();

		if (level1.puzzle_open)
		{
			// Se puzzle está aberto, envia eventos apenas para o puzzle

			puzzle_handle_event(&ev);
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (level1.puzzle_open) {
					// O puzzle será atualizado no main loop através de puzzle_handle_event
					if (puzzle_is_solved()) {
						level1.puzzle_open = false;
						level1.puzzle_isSolved = puzzle_is_solved();
						puzzle_destroy(); // Limpa o puzzle após resolver
						level1.getKey = true;
						level1.inPause = false;

					}
				}
				draw = true;
			}
			if (draw) {
				if (!puzzle_is_solved())puzzle_draw(SCREEN_WIDTH, SCREEN_HEIGHT);
				al_draw_text(Font, TEXT_COLOR, 50, SCREEN_HEIGHT - 100, 0, "Controles:");
				al_draw_text(Font, TEXT_COLOR, 50, SCREEN_HEIGHT - 80, 0, "R - Sair do Puzzle");
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				draw = false;
			}
		}
		else {
			if (ev.type == ALLEGRO_EVENT_TIMER) {


				al_get_keyboard_state(&keyState);
				al_get_mouse_state(&mouseState);
				//titleMenu.selectedOption = ReturnMenuOption(titleMenu, &mouseState, &ev);

				if (titleMenu.selectedOption == 1 && !level1.player.isDead && !level1.isDone) level_I_Update(&level1, &keyState);
				if (titleMenu.selectedOption == 2) done = true;
				draw = true;
				if (level1.player.isDead || level2.player.isDead) gameOver.active = true;
				//if(level1.inPause) drawPauseMenu(&pauseMenu);

				if (level1.isDone && !level2.player.isDead && !level2.isDone)level_II_Update(&level2, &keyState);
				if (level1.isDone && level2.isDone && !level3.player.isDead)level_III_Update(&level3, &keyState);

				if (minigame.marcou == true && al_key_down(&keyState, ALLEGRO_KEY_E)) {
					puzzle_destroy();
					destroy_tileset(level1.tileset);	
					destroy_tilemap(level1.map);
					destroy_tileset(level2.tileset);
					destroy_tilemap(level2.map);
					destroy_tileset(level3.tileset);
					destroy_tilemap(level3.map);
					al_destroy_bitmap(minigame.poema);
					al_destroy_bitmap(level1.storyPopUpImage);
					
					al_destroy_bitmap(level1.player.sprite);
					al_destroy_bitmap(level2.player.sprite);
					al_destroy_bitmap(level3.player.sprite);

					al_destroy_bitmap(level1.guard1.sprite);
					al_destroy_bitmap(level1.guard2.sprite);
					al_destroy_bitmap(level1.guard3.sprite);
					al_destroy_bitmap(level1.guard4.sprite);
					al_destroy_bitmap(level2.guard1.sprite);
					al_destroy_bitmap(level2.guard2.sprite);
					al_destroy_bitmap(level2.guard3.sprite);
					al_destroy_bitmap(level2.guard4.sprite);

					al_destroy_bitmap(level1.npc.sprite);
					al_destroy_bitmap(level2.npc1.sprite);
					al_destroy_bitmap(level3.npc1.sprite);
					al_destroy_bitmap(level3.npc2.sprite);
					al_destroy_bitmap(level2.npc2.sprite);

					al_destroy_bitmap(level1.hud.key.sprite);
					al_destroy_bitmap(level1.hud.AtacarDefender);
					al_destroy_bitmap(level2.hud.key.sprite);
					al_destroy_bitmap(level2.hud.AtacarDefender);
	
					al_destroy_bitmap(level1.door.sprite);
	
					al_destroy_bitmap(titleMenu.bg);
					al_destroy_bitmap(titleMenu.logo);

					al_destroy_font(Font);


					Font = al_create_builtin_font();
					titleMenu = createTitleMenu(Font);
					puzzle_init();
					level1 = Level_I_load();
					level2 = Level_II_load();
					level3 = Level_III_load();
					minigame = loadMinigame(Font);
					pauseMenu = createPauseMenu(Font);
					gameOver = createGameOver(Font);
				}
			}
			if (draw) {

				draw = false;


				if (!titleMenu.runningLevel)drawTitleMenu(&titleMenu, &mouseState);
				if (titleMenu.selectedOption == 1 && !gameOver.active && !level1.isDone)Level_I_Draw(level1, Font);

				if (level1.isDone && !gameOver.active && titleMenu.selectedOption == 1 && !level2.player.isDead && !level2.isDone)Level_II_Draw(level2, Font);
				if (level1.isDone && level2.isDone && !gameOver.active && titleMenu.selectedOption == 1 && !level3.player.isDead && !level3.isDone)Level_III_Draw(level3, Font);
				if (gameOver.active) drawGameOver(&gameOver, &mouseState);

				if (level1.isDone && level2.isDone && level3.isDone) {
					drawMinigame(&minigame, &mouseState);
				}


				if (level1.inPause && !level1.inDialogue && !level1.puzzle_open && !level3.isDone) drawPauseMenu(&pauseMenu, &mouseState);



				//printf("x = %d, y = %d\n", mouseState.x, mouseState.y);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}


		}




		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if(!titleMenu.runningLevel){
				if (button_contains_point(&titleMenu.startGameButton, mouseState.x, mouseState.y)) { 
					titleMenu.runningLevel = true;
				
					titleMenu.selectedOption = 1; // Start Game
				}
				else {
					if (button_contains_point(&titleMenu.exitButton, mouseState.x, mouseState.y))
					titleMenu.selectedOption = 2; // Exit
				}
			}
			

			if (button_contains_point(&gameOver.retryButton, mouseState.x, mouseState.y) && gameOver.active) {

				puzzle_destroy();
				destroy_tileset(level1.tileset);
				destroy_tilemap(level1.map);
				destroy_tileset(level2.tileset);
				destroy_tilemap(level2.map);
				destroy_tileset(level3.tileset);
				destroy_tilemap(level3.map);

				al_destroy_bitmap(minigame.poema);
				al_destroy_bitmap(level1.storyPopUpImage);
				
				al_destroy_bitmap(level1.player.sprite);
				al_destroy_bitmap(level2.player.sprite);
				al_destroy_bitmap(level3.player.sprite);

				al_destroy_bitmap(level1.guard1.sprite);
				al_destroy_bitmap(level1.guard2.sprite);
				al_destroy_bitmap(level1.guard3.sprite);
				al_destroy_bitmap(level1.guard4.sprite);
				al_destroy_bitmap(level2.guard1.sprite);
				al_destroy_bitmap(level2.guard2.sprite);
				al_destroy_bitmap(level2.guard3.sprite);
				al_destroy_bitmap(level2.guard4.sprite);

				al_destroy_bitmap(level1.npc.sprite);
				al_destroy_bitmap(level2.npc1.sprite);
				al_destroy_bitmap(level2.npc2.sprite);
				al_destroy_bitmap(level3.npc1.sprite);
				al_destroy_bitmap(level3.npc2.sprite);
				

				al_destroy_bitmap(level1.hud.key.sprite);
				al_destroy_bitmap(level1.hud.AtacarDefender);
				al_destroy_bitmap(level2.hud.key.sprite);
				al_destroy_bitmap(level2.hud.AtacarDefender);
	
				al_destroy_bitmap(level1.door.sprite);

	
				al_destroy_bitmap(titleMenu.bg);
				al_destroy_bitmap(titleMenu.logo);

				al_destroy_font(Font);


				
				Font = al_create_builtin_font();
				puzzle_init();
				titleMenu = createTitleMenu(Font);
				level1 = Level_I_load();
				level2 = Level_II_load();
				level3 = Level_III_load();
				minigame = loadMinigame(Font);
				pauseMenu = createPauseMenu(Font);
				gameOver = createGameOver(Font);
			}
			else {
				if (button_contains_point(&gameOver.exitButton, mouseState.x, mouseState.y) && gameOver.active)
					done = true;
			}


			if (button_contains_point(&pauseMenu.retriviedbutton, mouseState.x, mouseState.y) && level1.inPause && !level1.puzzle_open) {

				// Reinicia o jogo completamente
				// Limpa todos os dados dos níveis e volta para o menu principal

				// Desaloca a memória usada pelos recursos dos níveis
				puzzle_destroy();
				destroy_tileset(level1.tileset);
				destroy_tilemap(level1.map);
				destroy_tileset(level2.tileset);
				destroy_tilemap(level2.map);
				destroy_tileset(level3.tileset);
				destroy_tilemap(level3.map);

				al_destroy_bitmap(minigame.poema);
				al_destroy_bitmap(level1.storyPopUpImage);
				
				al_destroy_bitmap(level1.player.sprite);
				al_destroy_bitmap(level2.player.sprite);
				al_destroy_bitmap(level3.player.sprite);

				al_destroy_bitmap(level1.guard1.sprite);
				al_destroy_bitmap(level1.guard2.sprite);
				al_destroy_bitmap(level1.guard3.sprite);
				al_destroy_bitmap(level1.guard4.sprite);
				al_destroy_bitmap(level2.guard1.sprite);
				al_destroy_bitmap(level2.guard2.sprite);
				al_destroy_bitmap(level2.guard3.sprite);
				al_destroy_bitmap(level2.guard4.sprite);

				al_destroy_bitmap(level1.npc.sprite);
				al_destroy_bitmap(level2.npc1.sprite);
				al_destroy_bitmap(level2.npc2.sprite);
				al_destroy_bitmap(level3.npc1.sprite);
				al_destroy_bitmap(level3.npc2.sprite);
				

				al_destroy_bitmap(level1.hud.key.sprite);
				al_destroy_bitmap(level1.hud.AtacarDefender);
				al_destroy_bitmap(level2.hud.key.sprite);
				al_destroy_bitmap(level2.hud.AtacarDefender);
	
				al_destroy_bitmap(level1.door.sprite);
	
				al_destroy_bitmap(titleMenu.bg);
				al_destroy_bitmap(titleMenu.logo);

				al_destroy_font(Font);


				// Reinicia as variáveis do jogo
				// Reseta o menu de título, os níveis, o menu de pausa e o game over
				Font = al_create_builtin_font();
				titleMenu = createTitleMenu(Font);
				puzzle_init();
				level1 = Level_I_load();
				level2 = Level_II_load();
				level3 = Level_III_load();
				minigame = loadMinigame(Font);
				pauseMenu = createPauseMenu(Font);
				gameOver = createGameOver(Font);

			}
			else {
				if (button_contains_point(&pauseMenu.ContinuePlaybutton, mouseState.x, mouseState.y) && level1.inPause && !level1.puzzle_open) {
					level1.inPause = false;
					level2.inPause = false;
					level3.inPause = false;
				}
				if (button_contains_point(&pauseMenu.exitButton, mouseState.x, mouseState.y) && level1.inPause && !level1.puzzle_open)
					done = true;
			}
			if (button_contains_point(&minigame.resposta1, mouseState.x, mouseState.y) && level1.isDone && level2.isDone && level3.isDone) {
				minigame.respostaMarcada = 1;
			}
			if (button_contains_point(&minigame.resposta2, mouseState.x, mouseState.y) && level1.isDone && level2.isDone && level3.isDone) {
				minigame.respostaMarcada = 2;
			}
			if (button_contains_point(&minigame.resposta3, mouseState.x, mouseState.y) && level1.isDone && level2.isDone && level3.isDone) {
				minigame.respostaMarcada = 3;
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE && titleMenu.runningLevel && !gameOver.active) {
				level1.inDialogue = false;
				level1.inPause = true;
				if (level1.isDone && !level2.isDone) {
					level2.inPause = true;
					level2.inDialogue = false;
				}
				if (level1.isDone && level2.isDone && !level3.isDone) {

					level3.inPause = true;
					level2.inDialogue = false;
				}
				if (level1.puzzle_open) {
					level1.puzzle_open = false;
				}
				//done = true; // Sai do jogo com ESC
			}

			if(ev.keyboard.keycode == ALLEGRO_KEY_J) {
				if (!level1.isDone && !level1.player.isDead) level1.player.modoAtaque = true;
				if (level1.isDone && !level2.isDone && !level2.player.isDead) level2.player.modoAtaque = true;
			}

			if ((level1.inDialogue || level2.inDialogue || level3.inDialogue) && ev.keyboard.keycode == ALLEGRO_KEY_T && (level1.dialogueOption != 5 || level1.dialogueOption != 9 || level2.dialogueOption != 14 || level3.dialogueOption != 19)) {
				if (!level1.isDone) level1.dialogueOption++;
				if (level1.isDone && !level2.isDone) level2.dialogueOption++;
				if (level1.isDone && level2.isDone && !level3.isDone) level3.dialogueOption++;
			}
			if ((level1.inDialogue || level2.inDialogue || level3.inDialogue) && ev.keyboard.keycode == ALLEGRO_KEY_R) {
				if (!level1.isDone) {
					level1.inDialogue = false;
					level1.inPause = false;
				}
				if (level1.isDone && !level2.isDone) {
					level2.inDialogue = false;
					level2.inPause = false;
				}
				if (level1.isDone && level2.isDone && !level3.isDone) {
					level3.inDialogue = false;
					level3.inPause = false;
				}
			}

			if (level1.puzzle_open && ev.keyboard.keycode == ALLEGRO_KEY_R) {
				level1.puzzle_open = false;
				level1.inPause = false;
			}


		}

	}

	puzzle_destroy();
	destroy_tileset(level1.tileset);
	destroy_tilemap(level1.map);
	destroy_tileset(level2.tileset);
	destroy_tilemap(level2.map);
	destroy_tileset(level3.tileset);
	destroy_tilemap(level3.map);

	al_destroy_bitmap(minigame.poema);
	al_destroy_bitmap(level1.storyPopUpImage);

	al_destroy_bitmap(level1.player.sprite);
	al_destroy_bitmap(level2.player.sprite);
	al_destroy_bitmap(level3.player.sprite);

	al_destroy_bitmap(level1.guard1.sprite);
	al_destroy_bitmap(level1.guard2.sprite);
	al_destroy_bitmap(level1.guard3.sprite);
	al_destroy_bitmap(level1.guard4.sprite);
	al_destroy_bitmap(level2.guard1.sprite);
	al_destroy_bitmap(level2.guard2.sprite);
	al_destroy_bitmap(level2.guard3.sprite);
	al_destroy_bitmap(level2.guard4.sprite);

	al_destroy_bitmap(level1.npc.sprite);
	al_destroy_bitmap(level2.npc1.sprite);
	al_destroy_bitmap(level3.npc1.sprite);
	al_destroy_bitmap(level3.npc2.sprite);
	al_destroy_bitmap(level2.npc2.sprite);

	al_destroy_bitmap(level1.hud.key.sprite);
	al_destroy_bitmap(level1.hud.AtacarDefender);
	al_destroy_bitmap(level2.hud.key.sprite);
	al_destroy_bitmap(level2.hud.AtacarDefender);
	
	al_destroy_bitmap(level1.door.sprite);
	
	al_destroy_bitmap(titleMenu.bg);
	al_destroy_bitmap(titleMenu.logo);
	al_destroy_bitmap(icon);
	

	al_destroy_font(Font);

	al_destroy_display(window);
	al_destroy_timer(timer);
	al_destroy_event_queue(events);

	return 0;
}
