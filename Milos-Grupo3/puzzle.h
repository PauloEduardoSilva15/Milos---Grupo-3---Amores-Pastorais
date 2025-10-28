#ifndef PUZZLE_H
#define PUZZLE_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "quad.h"
#include "gameConstants.h"

typedef enum {
    PIECE_STRAIGHT = 0,
    PIECE_ELBOW = 1,
    PIECE_TEE = 2,
    PIECE_CROSS = 3
} PieceType;

typedef struct {
    PieceType type;
    int rot;        // 0..3 (múltiplos de 90 graus)
    int locked;     // 1 = imóvel
    int isStart;    // 1 = início
    int isEnd;      // 1 = final
    int connected;  // 1 = fluxo chegou até aqui
    int x, y;       // posição de desenho
    int size;
} Piece;

void puzzle_init(void);
void puzzle_handle_event(ALLEGRO_EVENT* ev);
void puzzle_draw(int screen_w, int screen_h);
int puzzle_is_solved(void);
void puzzle_destroy(void);

#endif
