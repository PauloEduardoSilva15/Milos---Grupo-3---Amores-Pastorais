#include "gamePauseMenu.h"


PauseMenu createPauseMenu(ALLEGRO_FONT* font) {
	PauseMenu menu;
	menu.ContinuePlaybutton;
	menu.retriviedbutton;
	menu.exitButton;
	return menu;
}

void drawPauseMenu(PauseMenu* menu, ALLEGRO_MOUSE_STATE* mouseState) {
    
    drawButton(&menu->ContinuePlaybutton);
    drawButton(&menu->exitButton);

    // Muda a cor da opção selecionada
    if (button_contains_point(&menu->ContinuePlaybutton, mouseState->x, mouseState->y)) {
        menu->ContinuePlaybutton.color = BUTTON_COLOR_HOVER;
        menu->exitButton.color = BUTTON_COLOR_NORMAL;

    }
    else if (button_contains_point(&menu->exitButton, mouseState->x, mouseState->y)) {
        menu->exitButton.color = BUTTON_COLOR_HOVER;
        menu->ContinuePlaybutton.color = BUTTON_COLOR_NORMAL;
    }
    else {
        menu->ContinuePlaybutton.color = BUTTON_COLOR_NORMAL;
        menu->exitButton.color = BUTTON_COLOR_NORMAL;
    }
}