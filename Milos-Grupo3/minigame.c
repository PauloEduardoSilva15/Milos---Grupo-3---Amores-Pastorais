#include "minigame.h"

minigame loadMinigame(ALLEGRO_FONT* font){
    minigame m;
    m.font = font;
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
            strcpy(menu->texto, "Você acertou, agora você poderá se casar com marília!");
            al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2), (SCREEN_WIDTH/2) + 200, ALLEGRO_ALIGN_CENTER, "Clique em E para voltar no menu ->>");
        }else{
            menu->marcou = true;
            strcpy(menu->texto, "Você perdeu, mas o npc aletório da primeira fase encontrou o cajado!");
            
            
        }

        

    }
    if(!menu->marcou){
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-300, 100, 0, "Complete o soneto com a palavra certa");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-300, 110, 0, "Lembrando que um soneto tem 4 estrofes");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-300, 120, 0, "com as duas primeiras tendo 4 versos e as duas ultimas 3 versos.");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-300, 130, 0, "E possui 10 silábas poéticas no total.");

        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 200, 0, "É gentil, é ---- a minha Altéia;");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 210, 0, "As graças, a modéstia de seu rosto");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 220, 0, "Inspiram no meu peito maior gosto");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 230, 0, "Que ver o próprio trigo quando ondeia.");

        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 250, 0, "Mas, vendo o lindo gesto de Dircéia");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 260, 0, "A nova sujeição me vejo exposto;");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 270, 0, "Ah! que é mais engraçado, mais composto");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 280, 0, "Que a pura esfera, de mil astros cheia!");

        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 300, 0, "Prender as duas com grilhões estritos");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 310, 0, "É uma ação, ó deuses, inconstante,");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 320, 0, "ndigna de sinceros, nobres peitos.");

        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 340, 0, "Cupido, se tens dó de um triste amante,");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 350, 0, "Ou forma de Lorino dois sujeitos,");
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2)-200, 360, 0, "Ou forma desses dois um só semblante.");

        
    }
    
    if(menu->marcou){
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2), (SCREEN_WIDTH/2) - 100, ALLEGRO_ALIGN_CENTER, menu->texto);
        al_draw_text(menu->font, TEXT_COLOR, (SCREEN_WIDTH/2), (SCREEN_WIDTH/2)+200, ALLEGRO_ALIGN_CENTER, "[E] ->>");
    }
    
    drawButton(&menu->resposta1);
    drawButton(&menu->resposta2);
    drawButton(&menu->resposta3);
}