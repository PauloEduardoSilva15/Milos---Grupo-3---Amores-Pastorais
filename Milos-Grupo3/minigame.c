#include "minigame.h"

minigame loadMinigame(ALLEGRO_FONT* font){
    minigame m;
    m.font = font;
    m.poema = al_load_bitmap("./imgs/poema.png");
    m.respostaMarcada = 0;
    m.respostaMarcada = 0;
    m.resposta1 = newButton(((SCREEN_WIDTH / 2)-100)-200, (SCREEN_HEIGHT / 2)+200, "prendada", font);
    m.resposta2 = newButton(((SCREEN_WIDTH / 2)-100), (SCREEN_HEIGHT / 2)+200, "chão", font);
    m.resposta3 = newButton(((SCREEN_WIDTH / 2)-100)+200, (SCREEN_HEIGHT / 2)+200, "semblante", font);
    return m;
}
void drawMinigame(minigame * menu,  ALLEGRO_MOUSE_STATE* mouseState){

    if(button_contains_point(&menu->resposta1, mouseState->x, mouseState->y)) {
        menu->resposta1.color = BUTTON_COLOR_HOVER;
        menu->resposta2.color = BUTTON_COLOR_NORMAL;
		menu->resposta3.color = BUTTON_COLOR_NORMAL;

    } else{
        if(button_contains_point(&menu->resposta2, mouseState->x, mouseState->y)) {
        menu->resposta2.color = BUTTON_COLOR_HOVER;
        menu->resposta1.color = BUTTON_COLOR_NORMAL;
		menu->resposta3.color = BUTTON_COLOR_NORMAL;
        }else{
			if(button_contains_point(&menu->resposta3, mouseState->x, mouseState->y)) {
			menu->resposta3.color = BUTTON_COLOR_HOVER;
        	menu->resposta1.color = BUTTON_COLOR_NORMAL;
        	menu->resposta2.color = BUTTON_COLOR_NORMAL;
			}else{
				menu->resposta1.color = BUTTON_COLOR_NORMAL;
				menu->resposta2.color = BUTTON_COLOR_NORMAL;
            	menu->resposta3.color = BUTTON_COLOR_NORMAL;
			}
        }
    } 
    if(menu->respostaMarcada != 0 && !menu->marcou){
        if(menu->respostaMarcada == 1){
            menu->marcou = true;
            strcpy(menu->texto, "Você acertou, Dirceu se casou com marília e viveram felizes para sempre");
            al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2), (SCREEN_WIDTH/2) + 200, ALLEGRO_ALIGN_CENTER, "Clique em E para voltar no menu ->>");
        }else{
            menu->marcou = true;
            strcpy(menu->texto, "Você perdeu, mas o npc aletório da primeira fase encontrou o cajado!");
            
            
        }

        

    }
    if(!menu->marcou){

        al_draw_bitmap(menu->poema, 96, 94, 0);
        drawButton(&menu->resposta1);
        drawButton(&menu->resposta2);
        drawButton(&menu->resposta3);
        
    }

    
    
    if(menu->marcou){
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2), (SCREEN_WIDTH/2) - 100, ALLEGRO_ALIGN_CENTER, menu->texto);
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2), (SCREEN_WIDTH/2), ALLEGRO_ALIGN_CENTER, "[E] Tela de título->>");
    }
    
    
}