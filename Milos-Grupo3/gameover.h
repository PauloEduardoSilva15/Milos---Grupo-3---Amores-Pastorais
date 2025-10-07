#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "level.h"  // para usar a struct Level

typedef struct {
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* gameSceneGray;
    ALLEGRO_FONT* font;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_RECT retryButton;
    ALLEGRO_RECT exitButton;
    bool running;
} GameOver;

// Cria o objeto GameOver
GameOver createGameOver(ALLEGRO_FONT* font);

// Mostra a tela de Game Over e retorna o novo Level quando o jogador escolher "Tentar novamente"
level gameOver_Show(void);

// Libera recursos
void destroyGameOver(GameOver* over);

#endif
