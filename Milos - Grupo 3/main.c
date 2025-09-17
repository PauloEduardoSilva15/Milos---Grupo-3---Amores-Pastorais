#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "quad.h"
#include <stdio.h>

int aabb_collision(quad* a, quad* b) {
    return (a->x < b->x + b->size &&
        a->x + a->size > b->x &&
        a->y < b->y + b->size &&
        a->y + a->size > b->y);
}

int main() {

    if (!al_init()) return -1;

    int sizeWindow[2] = { 800, 600 };
    ALLEGRO_DISPLAY* window = al_create_display(sizeWindow[0], sizeWindow[1]);

    if (!window) return -1;

    al_init_primitives_addon();
    al_install_keyboard();

    bool done = false, draw = true;

    // Variáveis de física do jogador
    float velY = 0;                  // Velocidade vertical
    const float GRAVITY = 1.0;       // Gravidade aplicada por frame
    const float JUMP_FORCE = -15.0;  // Força do pulo
    bool can_jump = false;           // Controle de pulo

    bool get_ob = false;

    quad player = quad_create((sizeWindow[0] / 2) - 32, 300, 5, 32, al_map_rgb(0, 0, 255));
    quad flor = quad_create(0, sizeWindow[1] - 100, 0, sizeWindow[0], al_map_rgb(0, 255, 0));
    quad door = quad_create(600, 400, 10, 100, al_map_rgb(150, 50, 0));
    quad ob = quad_create(100, 484, 0, 16, al_map_rgb(255, 255, 0));

    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT_QUEUE* events = al_create_event_queue();
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(events, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(events, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                done = true;
        }

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            al_get_keyboard_state(&keyState);

            // Movimento lateral
            if (al_key_down(&keyState, ALLEGRO_KEY_A) && player.x > 0)
                mov_quad(&player, 0);
            if (al_key_down(&keyState, ALLEGRO_KEY_D) &&
                player.x + player.size < sizeWindow[0] &&
                !aabb_collision(&player, &door))
                mov_quad(&player, 1);

            // Pular
            if (al_key_down(&keyState, ALLEGRO_KEY_W) && can_jump) {
                velY = JUMP_FORCE;
                can_jump = false;
            }

            // Aplica gravidade
            velY += GRAVITY;
            player.y += velY;

            // Verifica colisão com o chão
            if (aabb_collision(&player, &flor)) {
                player.y = flor.y - player.size; // Alinha com o chão
                velY = 0;
                can_jump = true;
            }

            // Colisão com o objeto
            if (aabb_collision(&player, &ob)) {
                ob.y = 100;
                ob.x = 100;
                get_ob = true;
            }

            // Porta se move se pegar o objeto
            if (aabb_collision(&player, &door) && get_ob && door.y < 600)
                door.y += 10;

            draw = true;
        }

        if (draw) {
            draw = false;

            draw_quad(&ob);
            draw_quad(&player);
            draw_quad(&flor);
            draw_quad(&door);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    al_destroy_display(window);
    al_destroy_timer(timer);
    al_destroy_event_queue(events);

    return 0;
}
