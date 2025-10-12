#include "gameover.h"
#include <stdio.h>

GameOver createGameOver(ALLEGRO_FONT* font) {
    GameOver over;
    over.bg = NULL; // tela preta
    over.logo = al_load_bitmap("./imgs/voce_perdeu.png"); // imagem “Você Perdeu”
    over.font = font;

    over.retryButton = newButton((SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2), "Tela Inicial", font);
    over.exitButton = newButton((SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) + 50, "Sair", font);

    over.selectedOption = 0;
    over.active = false;
    return over;
}

void drawGameOver(GameOver* over, ALLEGRO_MOUSE_STATE* mouseState) {

    // fundo preto
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Imagem “Você Perdeu”
    al_draw_scaled_bitmap(over->logo, 0, 0,
        al_get_bitmap_width(over->logo), al_get_bitmap_height(over->logo),
        SCREEN_WIDTH / 2 - al_get_bitmap_width(over->logo) / 4, 80,
        al_get_bitmap_width(over->logo) / 2, al_get_bitmap_height(over->logo) / 2, 0);

    // Botões
    drawButton(&over->retryButton);
    drawButton(&over->exitButton);

    // Hover
    if (button_contains_point(&over->retryButton, mouseState->x, mouseState->y)) {
        over->retryButton.color = BUTTON_COLOR_HOVER;
        over->exitButton.color = BUTTON_COLOR_NORMAL;
    }
    else if (button_contains_point(&over->exitButton, mouseState->x, mouseState->y)) {
        over->exitButton.color = BUTTON_COLOR_HOVER;
        over->retryButton.color = BUTTON_COLOR_NORMAL;
    }
    else {
        over->retryButton.color = BUTTON_COLOR_NORMAL;
        over->exitButton.color = BUTTON_COLOR_NORMAL;
    }
}

GameOver gameOver_global; // variável global acessível de qualquer lugar

void showGameOver() {
    gameOver_global.active = true;
}
