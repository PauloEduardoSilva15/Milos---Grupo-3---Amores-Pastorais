#include "TitleMenu.h"

TitleMenu createTitleMenu(ALLEGRO_FONT *font){
    TitleMenu menu;
    menu.background = al_load_bitmap("./assets/imgs/menu_background.png");
    menu.font = font;
    menu.startGameButton = quad_create(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, 200, QUAD_SIZE, al_map_rgb(0, 255, 0));
    menu.exitButton = quad_create(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100, 0, 200, QUAD_SIZE, al_map_rgb(255, 0, 0));
    menu.selectedOption = 0;

    return menu;
}

void drawTitleMenu(TitleMenu* menu) {
    al_draw_bitmap(menu->background, 0, 0, 0);
    draw_quad(&menu->startGameButton);
    draw_quad(&menu->exitButton);

    // Desenha o texto dos botões
    //al_draw_text(menu->font, al_map_rgb(0, 0, 0), menu->startGameButton.x + menu->startGameButton.w / 2, menu->startGameButton.y + menu->startGameButton.h / 4, ALLEGRO_ALIGN_CENTER, "Start Game");
    //al_draw_text(menu->font, al_map_rgb(0, 0, 0), menu->exitButton.x + menu->exitButton.w / 2, menu->exitButton.y + menu->exitButton.h / 4, ALLEGRO_ALIGN_CENTER, "Exit");

    // Desenha um retângulo ao redor da opção selecionada
    quad* selectedQuad = (menu->selectedOption == 0) ? &menu->startGameButton : &menu->exitButton;
    al_draw_rectangle(selectedQuad->x - 5, selectedQuad->y - 5, selectedQuad->x + selectedQuad->w + 5, selectedQuad->y + selectedQuad->h + 5, al_map_rgb(255, 255, 0), 3);
}