#include "gameover.h"
#include <stdio.h>

GameOver createGameOver(ALLEGRO_FONT* font) {
    GameOver over;
    //over.bg = NULL; // tela preta || obs Isso daqui não faz sentido nenhum. Se não tem imagem de plano de fundo n tem o porque tentar referenciar como se existisse uma imagem
    //over.logo = al_load_bitmap("./imgs/voce_perdeu.png"); // imagem “Você Perdeu” // Você tentou importar uma imagem que não existe no projeto
    over.font = font;
    over.retryButton = newButton((SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2), "Tela Inicial", font); // Certinho essa parte
    over.exitButton = newButton((SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) + 50, "Sair", font); //  Certinho essa parte
    over.active = false;  // Certinho essa parte
    return over;
}

void drawGameOver(GameOver* over, ALLEGRO_MOUSE_STATE* mouseState) {

   
    al_draw_text(over->font, TEXT_COLOR, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)-70, ALLEGRO_ALIGN_CENTER, "Você Morreu");

    // Botões
    drawButton(&over->retryButton);
    drawButton(&over->exitButton);

    // Hover
    if (button_contains_point(&over->retryButton, mouseState->x, mouseState->y)) {
        over->retryButton.color = BUTTON_COLOR_HOVER;
        over->exitButton.color = BUTTON_COLOR_NORMAL;
    }
    else{
        if (button_contains_point(&over->exitButton, mouseState->x, mouseState->y)) {
        over->exitButton.color = BUTTON_COLOR_HOVER;
        over->retryButton.color = BUTTON_COLOR_NORMAL;
        }else {
        over->retryButton.color = BUTTON_COLOR_NORMAL;
        over->exitButton.color = BUTTON_COLOR_NORMAL;
        }

    } 
    

}

//GameOver gameOver_global; // variável global acessível de qualquer lugar || Isso deveria ser colocado na main


