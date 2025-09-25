// main.c (versão modificada)
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "quad.h"
#include "puzzle.h"
#include <stdio.h>
#include <math.h>

int aabb_collision(quad* a, quad* b) {
    return (a->x < b->x + b->w &&
        a->x + a->w > b->x &&
        a->y < b->y + b->h &&
        a->y + a->h > b->y);
}

int main() {

    if (!al_init()) return -1;

    int sizeWindow[2] = { 800, 600 };
    ALLEGRO_DISPLAY* window = al_create_display(sizeWindow[0], sizeWindow[1]);
    if (!window) return -1;

    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();

    bool done = false, draw = true;

    int gravidade = 10;
    float velY = 0;
    const float GRAVITY = 1.0f;
    const float JUMP_FORCE = -15.0f;
    bool can_jump = false;

    bool get_ob = false;
    bool modoAtaque = false, modoDefesa = false;

    quad player = quad_create((sizeWindow[0] / 2) - 32, 300, 5, 32, 32, 100, al_map_rgb(0, 0, 255));
    quad flor = quad_create(0, sizeWindow[1] - 100, 0, sizeWindow[0], 300, 0, al_map_rgb(0, 255, 0));
    quad enemy = quad_create(770 - 32, 300, 5, 32, 32, 100, al_map_rgb(255, 0, 0));
    quad door = quad_create(600, 300, 10, 32, 200, 0, al_map_rgb(150, 50, 0));

    // NOTE: a "chave" (ob) começa fora da tela -> invisível/inacessível
    quad ob = quad_create(-1000, -1000, 0, 16, 16, 0, al_map_rgb(255, 255, 0));

    quad life_player = quad_create(600, 100, 0, player.life, 32, 0, al_map_rgb(0, 255, 0));
    quad life_enemy = quad_create(600, 200, 0, enemy.life, 32, 0, al_map_rgb(0, 255, 0));

    // marcador cinza (sobre o quadrado amarelo original)
    int markerX = 100;
    int markerY = flor.y - 75;
    int markerW = 32;
    int markerH = 50;

    ALLEGRO_FONT* font = al_create_builtin_font();

    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT_QUEUE* events = al_create_event_queue();
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_register_event_source(events, al_get_mouse_event_source());

    // puzzle
    bool puzzle_open = false;
    bool puzzle_solved = false;
    puzzle_init(); // inicializa dados do puzzle (gera peças, etc.)

    al_start_timer(timer);

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(events, &ev);

        // Quando puzzle aberto, envie eventos para o puzzle (uso mouse + clique)
        if (puzzle_open) {
            // roteia eventos relevantes para o puzzle
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                // manter o timer para desenhar
            }
            else {
                puzzle_handle_event(&ev);
                // se puzzle detectou solução internamente, sinalizamos aqui
                if (puzzle_is_solved()) {
                    puzzle_solved = true;
                    puzzle_open = false; // fecha puzzle automaticamente
                    // faz a chave aparecer em frente ao player
                    ob.x = player.x + player.w * 2;
                    ob.y = player.y;
                }
                // evitamos o resto do loop quando puzzle está aberto
                if (ev.type != ALLEGRO_EVENT_TIMER) continue;
            }
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) done = true;
            // se não estiver com puzzle aberto, tratamos teclas normais
            if (!puzzle_open) {
                if (ev.keyboard.keycode == ALLEGRO_KEY_E) {
                    // checa distância do player ao marcador (centro)
                    float dx = (player.x + player.w / 2) - (markerX + markerW / 2);
                    float dy = (player.y + player.h / 2) - (markerY + markerH / 2);
                    float dist = sqrtf(dx * dx + dy * dy);
                    if (dist <= 50.0f && !puzzle_solved) {
                        puzzle_open = true;
                    }
                }
            }
        }

        if (ev.type == ALLEGRO_EVENT_TIMER) {

            al_get_keyboard_state(&keyState);

            if (!aabb_collision(&player, &flor) && !aabb_collision(&player, &enemy)) {
                velY += GRAVITY;
                player.y += velY;
            }

            // quando puzzle aberto, bloqueia movimentos
            if (!puzzle_open) {
                if (al_key_down(&keyState, ALLEGRO_KEY_A) && player.x > 0 && !aabb_collision(&player, &enemy))
                    mov_quad(&player, 0);
                if (al_key_down(&keyState, ALLEGRO_KEY_D) && player.x + player.w < sizeWindow[0] && !aabb_collision(&player, &door) && !aabb_collision(&player, &enemy))
                    mov_quad(&player, 1);

                if (al_key_down(&keyState, ALLEGRO_KEY_W) && aabb_collision(&player, &flor)) {
                    player.y -= gravidade;
                }

                if (al_key_down(&keyState, ALLEGRO_KEY_J)) modoAtaque = true;
                else modoAtaque = false;

                if (al_key_down(&keyState, ALLEGRO_KEY_K)) modoDefesa = true;
                else modoDefesa = false;

                if (al_key_down(&keyState, ALLEGRO_KEY_W) && can_jump) {
                    velY = JUMP_FORCE;
                    can_jump = false;
                }
            }

            if (modoAtaque) player.color = al_map_rgb(100, 0, 200);
            if (modoDefesa) player.color = al_map_rgb(180, 0, 200);
            if (!modoAtaque && !modoDefesa) player.color = al_map_rgb(0, 0, 255);

            // pegar chave (ob) se colidir - só poderá pegar se ela tiver sido posicionada (ou seja, puzzle resolvido)
            if (aabb_collision(&player, &ob)) {
                // coleta a chave
                get_ob = true;
                // move a chave pra fora da tela após pegar
                ob.x = 100; ob.y = 100;
            }

            // se pegar a chave, abre a porta
            if (aabb_collision(&player, &door) && get_ob && door.y < 600)
                door.y += 50;

            if (aabb_collision(&player, &flor)) {
                player.y = flor.y - player.h;
                velY = 0;
                can_jump = true;
            }

            if (!aabb_collision(&enemy, &player) && aabb_collision(&enemy, &flor)) {
                if ((enemy.x > player.x)) {
                    if (!aabb_collision(&enemy, &door))
                        mov_quad(&enemy, 0);
                }
                else {
                    mov_quad(&enemy, 1);
                }
            }

            if (!aabb_collision(&enemy, &flor)) {
                mov_quad(&enemy, 3);
            }

            if (aabb_collision(&player, &enemy) && player.life > 0) {
                if (!modoAtaque) {
                    if (!modoDefesa) {
                        player.life -= 5 / 5;
                        life_player.w = player.life;
                    }
                }
                else {
                    if (!modoDefesa) {
                        if (enemy.life > 0) {
                            enemy.life -= 5 / 5;
                            life_enemy.w = enemy.life;
                        }
                    }
                }
                if (enemy.x > player.x) {
                    enemy.x += 10; player.x -= 10;
                }
                else {
                    if (!(player.y > enemy.y)) {
                        enemy.x -= 10; player.x += 10;
                    }
                    else {
                        player.x += 10;
                    }
                }
            }

            if ((player.x + player.h) > sizeWindow[0]) player.x = sizeWindow[0] - player.h;
            if ((enemy.x + enemy.h) > sizeWindow[0]) enemy.x = sizeWindow[0] - enemy.h;
            if ((player.x) < 0) player.x = 0;
            if ((enemy.x) < 0) enemy.x = 0;

            if (player.life <= 0) done = true;
            if (enemy.life <= 0) enemy.x = 832;

            draw = true;
        }

        if (draw) {
            draw = false;

            // desenha elementos do jogo
            draw_quad(&flor);
            draw_quad(&door);
            // desenhar marcador cinza sobre onde era o quadrado amarelo
            al_draw_filled_rectangle(markerX, markerY, markerX + markerW, markerY + markerH, al_map_rgb(80, 80, 80));
            // desenha player/enemy/vidas/porta etc
            draw_quad(&player);
            draw_quad(&enemy);
            draw_quad(&life_player);
            draw_quad(&life_enemy);
            // desenhar chave apenas se estiver visível (posicionada)
            if (ob.x > -500) draw_quad(&ob);

            // se player estiver perto do marcador (<=50 px) e puzzle ainda não resolvido, mostrar instrução
            float dx = (player.x + player.w / 2) - (markerX + markerW / 2);
            float dy = (player.y + player.h / 2) - (markerY + markerH / 2);
            float dist = sqrtf(dx * dx + dy * dy);
            if (dist <= 50.0f && !puzzle_solved) {
                // desenha um retângulo pequeno e texto [E] Interagir
                int tx = markerX;
                int ty = markerY - 24;
                al_draw_filled_rectangle(tx, ty, tx + 120, ty + 20, al_map_rgba(0, 0, 0, 200));
                al_draw_text(font, al_map_rgb(255, 255, 255), tx + 4, ty + 2, 0, "[E] Interagir");
            }

            // se puzzle estiver aberto, desenhe a tela do puzzle por cima
            if (puzzle_open) {
                // desenha overlay e o puzzle (puzzle_draw usa o display atual)
                puzzle_draw(sizeWindow[0], sizeWindow[1]);
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    puzzle_destroy();
    al_destroy_font(font);
    al_destroy_display(window);
    al_destroy_timer(timer);
    al_destroy_event_queue(events);

    return 0;
}
