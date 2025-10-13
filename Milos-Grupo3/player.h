#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "gameConstants.h"
#include "entity.h"

entity playerLoad();

void playerDraw(entity * player, int Camerax, int flip);

#endif // !PLAYER_H
