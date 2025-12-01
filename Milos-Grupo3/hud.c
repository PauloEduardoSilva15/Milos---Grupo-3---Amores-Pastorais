#include "hud.h"


hud newHud(int life, bool getKey){
    hud hud;
    hud.AtacarDefender = al_load_bitmap("./imgs/sprites/HUD.png");
    hud.displayLife = displayLifeLoad(life);
    hud.getKey = getKey;
    hud.key = newItem("./imgs/sprites/key.png", KEY_ITEM_X, KEY_ITEM_Y_0, hud.getKey);
    
    return hud;
}

void drawHud(hud * hud, ALLEGRO_FONT * Font){
    // Tutorial Controls
	/*al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 50, 0, "Controles:");
	al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 60, 0, "Esc - Pause");
	al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 70, 0, "W - Pular");
	al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 80, 0, "A - Esquerda");
	al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 90, 0, "D - Direita");
	al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 100, 0, "E - Interagir");
	al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 110, 0, "J - Ataque");
	al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 120, 120, 0, "K - Defesa");*/
    al_draw_bitmap_region(hud->AtacarDefender, 0, 0, QUAD_SIZE*2, QUAD_SIZE*2, SCREEN_WIDTH - 200, 50, 0);
    al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 168, 105, ALLEGRO_ALIGN_CENTER, "[J]");
    al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 168, 115, ALLEGRO_ALIGN_CENTER, "ATACAR");

    al_draw_bitmap_region(hud->AtacarDefender, QUAD_SIZE*2, 0, QUAD_SIZE*2, QUAD_SIZE*2, SCREEN_WIDTH - 100, 50, 0);
    al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 68, 105, ALLEGRO_ALIGN_CENTER, "[K]");
    al_draw_text(Font, TEXT_COLOR, SCREEN_WIDTH - 68, 115, ALLEGRO_ALIGN_CENTER, "DEFENDER");

    al_draw_text(Font, TEXT_COLOR, 50, SCREEN_HEIGHT - 50, ALLEGRO_ALIGN_CENTER, "[A]");
    al_draw_text(Font, TEXT_COLOR, 50, SCREEN_HEIGHT - 40, ALLEGRO_ALIGN_CENTER, "ESQUERDA");
    al_draw_text(Font, TEXT_COLOR, 90, SCREEN_HEIGHT - 70, ALLEGRO_ALIGN_CENTER, "[W]");
    al_draw_text(Font, TEXT_COLOR, 90, SCREEN_HEIGHT - 60, ALLEGRO_ALIGN_CENTER, "PULAR");
    al_draw_text(Font, TEXT_COLOR, 120, SCREEN_HEIGHT - 50, ALLEGRO_ALIGN_CENTER, "[D]");
    al_draw_text(Font, TEXT_COLOR, 120, SCREEN_HEIGHT - 40, ALLEGRO_ALIGN_CENTER, "DIREITA");
    displayLifeDraw(&hud->displayLife);
    if(hud->getKey) itemDraw(&hud->key);
}