#include "TitleMenu.h"
#include <stdio.h>

TitleMenu createTitleMenu( ALLEGRO_FONT *font){
    TitleMenu menu;
    //menu.bg = al_load_bitmap("Milos-Grupo3/imgs/bgMenu.jpeg"); // Linux
    //menu.logo = al_load_bitmap("Milos-Grupo3/imgs/GameLogo.png"); // Linux
    menu.bg = al_load_bitmap("./imgs/bgMenu.jpeg"); // Windows
    menu.logo = al_load_bitmap("./imgs/GameLogo.png"); //Windows
    menu.font = font;
    menu.startGameButton = newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2), "Jogar", font); // Botão de iniciar o jogo
    menu.exitButton = newButton((SCREEN_WIDTH / 2)-100, (SCREEN_HEIGHT / 2) + 50, "Sair", font);// Botão de sair do jogo
    menu.selectedOption = 0; // Nenhuma opção selecionada
    menu.runningLevel = false;// Indica se o nível está em execução


    return menu;
}

void drawTitleMenu(TitleMenu* menu, ALLEGRO_MOUSE_STATE* mouseState) {

    al_draw_scaled_bitmap(menu->bg, 0, 0, al_get_bitmap_width(menu->bg), al_get_bitmap_height(menu->bg), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    al_draw_scaled_bitmap(menu->logo, 0, 0, al_get_bitmap_width(menu->logo), al_get_bitmap_height(menu->logo), SCREEN_WIDTH / 2 - al_get_bitmap_width(menu->logo) / 4, 50,al_get_bitmap_width(menu->logo) / 2, al_get_bitmap_height(menu->logo) / 2, 0);

    //al_draw_bitmap(menu->logo, 0, 0, 0);
    drawButton(&menu->startGameButton);
    drawButton(&menu->exitButton);

    // Desenha o texto dos botões
    //al_draw_text(menu->font, TEXT_COLOR, menu->startGameButton.x + menu->startGameButton.w / 2, menu->startGameButton.y + menu->startGameButton.h / 4, ALLEGRO_ALIGN_CENTER, "Start Game");
    //al_draw_text(menu->font, TEXT_COLOR, menu->exitButton.x + menu->exitButton.w / 2, menu->exitButton.y + menu->exitButton.h / 4, ALLEGRO_ALIGN_CENTER, "Exit");

    // Desenha um retângulo ao redor da opção selecionada
    //
    if(button_contains_point(&menu->startGameButton, mouseState->x, mouseState->y)) {
        menu->startGameButton.color = BUTTON_COLOR_HOVER;
        menu->exitButton.color = BUTTON_COLOR_NORMAL;

    } else if(button_contains_point(&menu->exitButton, mouseState->x, mouseState->y)) {
        menu->exitButton.color = BUTTON_COLOR_HOVER;
        menu->startGameButton.color = BUTTON_COLOR_NORMAL;
    } else {
        menu->startGameButton.color = BUTTON_COLOR_NORMAL;
        menu->exitButton.color = BUTTON_COLOR_NORMAL;
    }
}