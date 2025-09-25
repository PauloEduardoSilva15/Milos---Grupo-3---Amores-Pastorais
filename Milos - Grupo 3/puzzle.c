// puzzle.c
#include "puzzle.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <string.h>

#define GRID_ROWS 3
#define GRID_COLS 5

typedef enum {
    PIECE_STRAIGHT = 0,
    PIECE_ELBOW = 1,
    PIECE_TEE = 2,
    PIECE_CROSS = 3
} PieceType;

typedef struct {
    PieceType type;
    int rot;        // 0..3 (multiplo de 90 graus)
    int locked;     // 1 = imóvel
    int isStart;    // 1 = início
    int isEnd;      // 1 = final
    int connected;  // 1 = fluxo chegou até aqui
    int x, y;
    int size;
} Piece;

static Piece pieces[GRID_ROWS][GRID_COLS];
static int solved = 0;

// ----- Funções auxiliares -----
static int piece_has_side(PieceType t, int rot, int side) {
    int local = (side - rot) & 3;
    switch (t) {
    case PIECE_STRAIGHT: return (local == 0 || local == 2);
    case PIECE_ELBOW:    return (local == 0 || local == 1);
    case PIECE_TEE:      return (local == 0 || local == 1 || local == 3);
    case PIECE_CROSS:    return 1;
    default: return 0;
    }
}

// DFS para propagar fluxo
static void dfs(int r, int c) {
    pieces[r][c].connected = 1;
    Piece* p = &pieces[r][c];

    for (int s = 0; s < 4; s++) {
        if (piece_has_side(p->type, p->rot, s)) {
            int nr = r, nc = c;
            if (s == 0) nr--;
            if (s == 1) nc++;
            if (s == 2) nr++;
            if (s == 3) nc--;

            if (nr < 0 || nr >= GRID_ROWS || nc < 0 || nc >= GRID_COLS) continue;
            Piece* q = &pieces[nr][nc];
            int opp = (s + 2) & 3;
            if (piece_has_side(q->type, q->rot, opp) && !q->connected) {
                dfs(nr, nc);
            }
        }
    }
}

// recalcula fluxo a partir do início
static void update_connections(void) {
    for (int i = 0; i < GRID_ROWS; i++)
        for (int j = 0; j < GRID_COLS; j++)
            pieces[i][j].connected = 0;

    // procura início e propaga
    for (int i = 0; i < GRID_ROWS; i++)
        for (int j = 0; j < GRID_COLS; j++)
            if (pieces[i][j].isStart) dfs(i, j);

    // checa vitória: se algum final foi alcançado
    solved = 0;
    for (int i = 0; i < GRID_ROWS; i++)
        for (int j = 0; j < GRID_COLS; j++)
            if (pieces[i][j].isEnd && pieces[i][j].connected)
                solved = 1;
}

// ----- Inicialização -----
void puzzle_init(void) {
    solved = 0;
    int tileSize = 80;

    PieceType layout[GRID_ROWS][GRID_COLS] = {
        {PIECE_STRAIGHT, PIECE_STRAIGHT, PIECE_ELBOW,   PIECE_TEE,     PIECE_STRAIGHT},
        {PIECE_ELBOW,    PIECE_TEE,      PIECE_CROSS,   PIECE_ELBOW,   PIECE_TEE},
        {PIECE_STRAIGHT, PIECE_ELBOW,    PIECE_TEE,     PIECE_STRAIGHT,PIECE_STRAIGHT}
    };

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            pieces[i][j].type = layout[i][j];
            pieces[i][j].rot = (i + j) % 4; // embaralha
            pieces[i][j].locked = 0;
            pieces[i][j].isStart = 0;
            pieces[i][j].isEnd = 0;
            pieces[i][j].connected = 0;
            pieces[i][j].size = tileSize;
        }
    }

    // define início (fixo)
    pieces[0][0].isStart = 1;
    pieces[0][0].locked = 1;
    pieces[0][0].rot = 2; // apontando para baixo

    // define final (fixo)
    pieces[2][4].isEnd = 1;
    pieces[2][4].locked = 1;
    pieces[2][4].rot = 0; // apontando para cima

    update_connections();
}

// ----- Eventos -----
void puzzle_handle_event(ALLEGRO_EVENT* ev) {
    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (ev->mouse.button & 1) {
            int mx = ev->mouse.x, my = ev->mouse.y;
            for (int i = 0; i < GRID_ROWS; i++) {
                for (int j = 0; j < GRID_COLS; j++) {
                    Piece* p = &pieces[i][j];
                    if (mx >= p->x && mx <= p->x + p->size &&
                        my >= p->y && my <= p->y + p->size) {
                        if (!p->locked) {
                            p->rot = (p->rot + 1) & 3;
                            update_connections();
                        }
                        return;
                    }
                }
            }
        }
    }
}

// ----- Desenho -----
void puzzle_draw(int screen_w, int screen_h) {
    al_draw_filled_rectangle(0, 0, screen_w, screen_h, al_map_rgba(40, 40, 40, 200));

    int tileSize = 80;
    int gridW = GRID_COLS * tileSize, gridH = GRID_ROWS * tileSize;
    int startX = (screen_w - gridW) / 2, startY = (screen_h - gridH) / 2;

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            Piece* p = &pieces[i][j];
            p->x = startX + j * tileSize;
            p->y = startY + i * tileSize;

            al_draw_filled_rectangle(p->x + 4, p->y + 4, p->x + tileSize - 4, p->y + tileSize - 4,
                al_map_rgb(100, 100, 100));

            ALLEGRO_COLOR col = p->connected ? al_map_rgb(0, 150, 255) : al_map_rgb(255, 255, 255);

            int cx = p->x + tileSize / 2, cy = p->y + tileSize / 2;
            int len = tileSize / 2 - 10;

            al_draw_filled_rectangle(cx - 6, cy - 6, cx + 6, cy + 6, col);
            for (int s = 0; s < 4; s++) {
                if (piece_has_side(p->type, p->rot, s)) {
                    if (s == 0) al_draw_filled_rectangle(cx - 8, cy - len, cx + 8, cy - 6, col);
                    if (s == 1) al_draw_filled_rectangle(cx + 6, cy - 8, cx + len, cy + 8, col);
                    if (s == 2) al_draw_filled_rectangle(cx - 8, cy + 6, cx + 8, cy + len, col);
                    if (s == 3) al_draw_filled_rectangle(cx - len, cy - 8, cx - 6, cy + 8, col);
                }
            }

            al_draw_rectangle(p->x + 4, p->y + 4, p->x + tileSize - 4, p->y + tileSize - 4,
                al_map_rgb(200, 200, 200), 2);
        }
    }

    ALLEGRO_FONT* f = al_create_builtin_font();
    if (f) {
        al_draw_text(f, al_map_rgb(255, 255, 255), screen_w / 2, startY - 36,
            ALLEGRO_ALIGN_CENTRE, "Conecte o início ao final! Clique para girar");
        al_destroy_font(f);
    }
}

// ----- Estado -----
int puzzle_is_solved(void) { return solved; }
void puzzle_destroy(void) { solved = 0; }
