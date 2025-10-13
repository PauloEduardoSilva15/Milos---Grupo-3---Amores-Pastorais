#include "hud.h"


hud newHud(int life, bool getKey){
    hud hud;
    hud.displayLife = displayLifeLoad(life);
    hud.getKey = getKey;
    hud.key = newItem(KEY_ITEM_X, KEY_ITEM_Y_0, hud.getKey);
    
    return hud;
}

void drawHud(hud * hud){
    displayLifeDraw(&hud->displayLife);
    if(hud->getKey) itemDraw(&hud->key);
}