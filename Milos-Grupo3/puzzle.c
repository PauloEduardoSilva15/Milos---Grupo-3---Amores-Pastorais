#include "puzzle.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "gameConstants.h"
#include <string.h>

static Piece pieces[GRID_ROWS][GRID_COLS];
static int solved = 0;
static int tileSize = 80;
static int startX = 0, startY = 0;

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
            if (piece_has_side(q->type, q->rot, opp) && !q->connected)
                dfs(nr, nc);
        }
    }
}

static void update_connections(void) {
    for (int i = 0; i < GRID_ROWS; i++)
        for (int j = 0; j < GRID_COLS; j++)
            pieces[i][j].connected = 0;

    // Propaga fluxo a partir do início
    for (int i = 0; i < GRID_ROWS; i++)
        for (int j = 0; j < GRID_COLS; j++)
            if (pieces[i][j].isStart) dfs(i, j);

    // Checa vitória
    solved = 0;
    for (int i = 0; i < GRID_ROWS; i++)
        for (int j = 0; j < GRID_COLS; j++)
            if (pieces[i][j].isEnd && pieces[i][j].connected)
                solved = 1;
}

// ----- Inicialização -----
void puzzle_init(void) {
    solved = 0;
    tileSize = 80;

    PieceType layout[GRID_ROWS][GRID_COLS] = {
        {PIECE_STRAIGHT, PIECE_STRAIGHT, PIECE_ELBOW,   PIECE_TEE,     PIECE_STRAIGHT},
        {PIECE_ELBOW,    PIECE_TEE,      PIECE_CROSS,   PIECE_ELBOW,   PIECE_TEE},
        {PIECE_STRAIGHT, PIECE_ELBOW,    PIECE_TEE,     PIECE_STRAIGHT,PIECE_STRAIGHT}
    };

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            Piece* p = &pieces[i][j];
            p->type = layout[i][j];
            p->rot = (i + j) % 4;
            p->locked = 0;
            p->isStart = 0;
            p->isEnd = 0;
            p->connected = 0;
            p->size = tileSize;
        }
    }

    pieces[0][0].isStart = 1;
    pieces[0][0].locked = 1;
    pieces[0][0].rot = 2; // para baixo

    pieces[2][4].isEnd = 1;
    pieces[2][4].locked = 1;
    pieces[2][4].rot = 0; // para cima

    update_connections();
}

// ----- Eventos -----
void puzzle_handle_event(ALLEGRO_EVENT* ev) {
    if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev->mouse.button == 1) {
        int mx = ev->mouse.x, my = ev->mouse.y;

        for (int i = 0; i < GRID_ROWS; i++) {
            for (int j = 0; j < GRID_COLS; j++) {
                Piece* p = &pieces[i][j];
                int px = startX + j * tileSize;
                int py = startY + i * tileSize;

                if (mx >= px && mx <= px + tileSize &&
                    my >= py && my <= py + tileSize) {
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

// ----- Desenho -----
void puzzle_draw(int screen_w, int screen_h) {
    al_draw_filled_rectangle(0, 0, screen_w, screen_h, al_map_rgba(40, 40, 40, 220));

    int gridW = GRID_COLS * tileSize;
    int gridH = GRID_ROWS * tileSize;
    startX = (screen_w - gridW) / 2;
    startY = (screen_h - gridH) / 2;

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            Piece* p = &pieces[i][j];
            p->x = startX + j * tileSize;
            p->y = startY + i * tileSize;

            al_draw_filled_rectangle(p->x + 3, p->y + 3,
                p->x + tileSize - 3, p->y + tileSize - 3,
                al_map_rgb(90, 90, 90));

            ALLEGRO_COLOR col = p->connected ? al_map_rgb(0, 180, 255)
                : al_map_rgb(255, 255, 255);

            int cx = p->x + tileSize / 2, cy = p->y + tileSize / 2;
            int len = tileSize / 2 - 10;

            al_draw_filled_rectangle(cx - 5, cy - 5, cx + 5, cy + 5, col);
            for (int s = 0; s < 4; s++) {
                if (piece_has_side(p->type, p->rot, s)) {
                    if (s == 0) al_draw_filled_rectangle(cx - 6, cy - len, cx + 6, cy - 5, col);
                    if (s == 1) al_draw_filled_rectangle(cx + 5, cy - 6, cx + len, cy + 6, col);
                    if (s == 2) al_draw_filled_rectangle(cx - 6, cy + 5, cx + 6, cy + len, col);
                    if (s == 3) al_draw_filled_rectangle(cx - len, cy - 6, cx - 5, cy + 6, col);
                }
            }

            al_draw_rectangle(p->x + 3, p->y + 3,
                p->x + tileSize - 3, p->y + tileSize - 3,
                al_map_rgb(200, 200, 200), 2);
        }
    }

    ALLEGRO_FONT* f = al_create_builtin_font();
    if (f) {
        const char* msg = solved ? "✅ Puzzle resolvido!" : "Conecte o início ao final! Clique para girar";
        al_draw_text(f, al_map_rgb(255, 255, 255), screen_w / 2, startY - 36,
            ALLEGRO_ALIGN_CENTRE, msg);
        al_destroy_font(f);
    }
}

// ----- Estado -----
int puzzle_is_solved(void) { return solved; }
void puzzle_destroy(void) { solved = 0; }
