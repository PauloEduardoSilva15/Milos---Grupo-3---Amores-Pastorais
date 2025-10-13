#include "gamePauseMenu.h"


PauseMenu createPauseMenu(ALLEGRO_FONT * font) {
	PauseMenu menu;
	menu.ContinuePlaybutton =  newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2), "Continuar", font);;
	menu.retriviedbutton = newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2) + 50, "Tela Inicial", font);
	menu.exitButton = newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2) + 100, "Sair do Jogo", font);;
	return menu;
}

void drawPauseMenu(PauseMenu* menu , ALLEGRO_MOUSE_STATE* mouseState) {
    if(button_contains_point(&menu->ContinuePlaybutton, mouseState->x, mouseState->y)) {
        menu->ContinuePlaybutton.color = BUTTON_COLOR_HOVER;
        menu->exitButton.color = BUTTON_COLOR_NORMAL;
		menu->retriviedbutton.color = BUTTON_COLOR_NORMAL;

    } else{
        if(button_contains_point(&menu->exitButton, mouseState->x, mouseState->y)) {
        menu->exitButton.color = BUTTON_COLOR_HOVER;
        menu->ContinuePlaybutton.color = BUTTON_COLOR_NORMAL;
		menu->retriviedbutton.color = BUTTON_COLOR_NORMAL;
        }else{
			if(button_contains_point(&menu->retriviedbutton, mouseState->x, mouseState->y)) {
			menu->retriviedbutton.color = BUTTON_COLOR_HOVER;
        	menu->exitButton.color = BUTTON_COLOR_NORMAL;
        	menu->ContinuePlaybutton.color = BUTTON_COLOR_NORMAL;
			}else{
				menu->retriviedbutton.color = BUTTON_COLOR_NORMAL;
				menu->ContinuePlaybutton.color = BUTTON_COLOR_NORMAL;
            	menu->exitButton.color = BUTTON_COLOR_NORMAL;
			}
        }
    } 
    drawButton(&menu->ContinuePlaybutton);
    drawButton(&menu->retriviedbutton);
    drawButton(&menu->exitButton);

}