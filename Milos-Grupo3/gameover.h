#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "button.h"
#include "gameConstants.h"

typedef struct GameOver {
    ALLEGRO_BITMAP* bg;
    ALLEGRO_BITMAP* logo; // imagem "Você Perdeu"
    ALLEGRO_FONT* font;
    button retryButton;   // "Tela Inicial"
    button exitButton;    // "Sair"
    int selectedOption;   // 1 = Tela Inicial, 2 = Sair
    bool active;          // indica se a tela está ativa
} GameOver;

GameOver createGameOver(ALLEGRO_FONT* font);
void drawGameOver(GameOver* over, ALLEGRO_MOUSE_STATE* mouseState);

extern GameOver gameOver_global;
void showGameOver();

#endif
#pragma once
