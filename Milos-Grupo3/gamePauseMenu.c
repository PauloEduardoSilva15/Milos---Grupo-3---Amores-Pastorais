#include "gamePauseMenu.h"


PauseMenu createPauseMenu(ALLEGRO_FONT * font) {
	PauseMenu menu;
	menu.ContinuePlaybutton =  newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2), "Continuar", font);;
	menu.retriviedbutton = newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2) + 50, "Tela Inicial", font);
	menu.exitButton = newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2) + 100, "Sair do Jogo", font);;
	return menu;
}

void drawPauseMenu(PauseMenu* menu , ALLEGRO_MOUSE_STATE* mouseState) {
    
    drawButton(&menu->ContinuePlaybutton);
    drawButton(&menu->retriviedbutton);
    drawButton(&menu->exitButton);

}