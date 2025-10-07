#include "gameover.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define SCREEN_W 800
#define SCREEN_H 600

// Variável global para o estado da tela
static GameOver over;

GameOver createGameOver(ALLEGRO_FONT* font) {
    GameOver o;
    o.font = font;
    o.background = NULL;
    o.gameSceneGray = NULL;
    o.running = true;

    // Define posições dos botões
    o.retryButton = (ALLEGRO_RECT){ SCREEN_W / 2 - 150, SCREEN_H / 2, 300, 60 };
    o.exitButton = (ALLEGRO_RECT){ SCREEN_W / 2 - 150, SCREEN_H / 2 + 80, 300, 60 };

    return o;
}

static void drawButton(ALLEGRO_RECT rect, const char* text, ALLEGRO_FONT* font) {
    al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, al_map_rgb(50, 50, 50));
    al_draw_rectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, al_map_rgb(255, 255, 255), 2);
    int textW = al_get_text_width(font, text);
    int textH = al_get_font_line_height(font);
    al_draw_text(font, al_map_rgb(255, 255, 255), rect.x + rect.w / 2 - textW / 2, rect.y + rect.h / 2 - textH / 2, 0, text);
}

static void applyGrayScale(ALLEGRO_BITMAP* bmp) {
    al_lock_bitmap(bmp, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
    int w = al_get_bitmap_width(bmp);
    int h = al_get_bitmap_height(bmp);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ALLEGRO_COLOR c = al_get_pixel(bmp, x, y);
            unsigned char r, g, b, a;
            al_unmap_rgba(c, &r, &g, &b, &a);
            unsigned char gray = (r + g + b) / 3;
            ALLEGRO_COLOR newC = al_map_rgba(gray, gray, gray, a);
            al_put_pixel(x, y, newC);
        }
    }

    al_unlock_bitmap(bmp);
}

level gameOver_Show(void) {
    over = createGameOver(al_load_font("arial.ttf", 36, 0));

    // Captura o backbuffer e aplica escala de cinza
    over.gameSceneGray = al_clone_bitmap(al_get_backbuffer(al_get_current_display()));
    applyGrayScale(over.gameSceneGray);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_EVENT event;

    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(al_get_current_display()));

    while (over.running) {
        while (al_get_next_event(queue, &event)) {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                exit(0);
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) {
                int mx = event.mouse.x;
                int my = event.mouse.y;
                if (mx >= over.retryButton.x && mx <= over.retryButton.x + over.retryButton.w &&
                    my >= over.retryButton.y && my <= over.retryButton.y + over.retryButton.h) {
                    // Reinicia o level
                    destroyGameOver(&over);
                    al_destroy_event_queue(queue);
                    return level_Load();
                }
                if (mx >= over.exitButton.x && mx <= over.exitButton.x + over.exitButton.w &&
                    my >= over.exitButton.y && my <= over.exitButton.y + over.exitButton.h) {
                    destroyGameOver(&over);
                    al_destroy_event_queue(queue);
                    exit(0);
                }
            }
        }

        // Desenha a tela
        al_draw_bitmap(over.gameSceneGray, 0, 0, 0);
        al_draw_filled_rectangle(0, 0, SCREEN_W, SCREEN_H, al_map_rgba(0, 0, 0, 150));

        al_draw_text(over.font, al_map_rgb(255, 0, 0), SCREEN_W / 2, SCREEN_H / 2 - 120, ALLEGRO_ALIGN_CENTER, "GAME OVER");

        drawButton(over.retryButton, "Tentar Novamente", over.font);
        drawButton(over.exitButton, "Sair do Jogo", over.font);

        al_flip_display();
        al_rest(0.01);
    }

    destroyGameOver(&over);
    al_destroy_event_queue(queue);

    // Retorna o Level padrão (fallback)
    return level_Load();
}

void destroyGameOver(GameOver* o) {
    if (o->background) al_destroy_bitmap(o->background);
    if (o->gameSceneGray) al_destroy_bitmap(o->gameSceneGray);
    if (o->font) al_destroy_font(o->font);
}
