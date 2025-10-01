#include "TitleMenu.h"
#include <stdio.h>

TitleMenu createTitleMenu( ALLEGRO_FONT *font){
    TitleMenu menu;
    //menu.background = backgrond;
    //menu.logo = al_load_bitmap("GameLogo.png");
    menu.font = font;
    menu.startGameButton = quad_create((SCREEN_WIDTH / 2) - 100, SCREEN_HEIGHT / 2, 0, 200, QUAD_SIZE, al_map_rgb(0, 255, 0));
    menu.exitButton = quad_create((SCREEN_WIDTH / 2)-100, SCREEN_HEIGHT / 2 + 100, 0, 200, QUAD_SIZE, al_map_rgb(255, 0, 0));
    menu.selectedOption = 0;
    menu.selectedButton = &menu.startGameButton;
    menu.runningLevel = false;


    return menu;
}





void drawTitleMenu(TitleMenu* menu, ALLEGRO_MOUSE_STATE* mouseState) {
    //al_draw_bitmap(menu->logo, 0, 0, 0);
    draw_quad(&menu->startGameButton);
    draw_quad(&menu->exitButton);

    // Desenha o texto dos botões
    al_draw_text(menu->font, al_map_rgb(0, 0, 0), menu->startGameButton.x + menu->startGameButton.w / 2, menu->startGameButton.y + menu->startGameButton.h / 4, ALLEGRO_ALIGN_CENTER, "Start Game");
    al_draw_text(menu->font, al_map_rgb(0, 0, 0), menu->exitButton.x + menu->exitButton.w / 2, menu->exitButton.y + menu->exitButton.h / 4, ALLEGRO_ALIGN_CENTER, "Exit");

    // Desenha um retângulo ao redor da opção selecionada
    //
    if (quad_contains_point(&menu->startGameButton, mouseState->x, mouseState->y)) {
        menu->selectedButton = &menu->startGameButton;
    } else if (quad_contains_point(&menu->exitButton, mouseState->x, mouseState->y)) {
        menu->selectedButton = &menu->exitButton;
    } else {
        menu->selectedButton = NULL; // Nenhum botão selecionado
    }
    if (menu->selectedButton != NULL) {
        al_draw_rectangle(menu->selectedButton->x - 5, menu->selectedButton->y - 5, menu->selectedButton->x + menu->selectedButton->w + 5, menu->selectedButton->y + menu->selectedButton->h + 5, al_map_rgb(255, 255, 0), 3);
    }
    
}