#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include "Player.h"
#include "Map.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
class Player;
void movementManager(Player &player,Map &mapManager);
void actionManager(Player &player,Map &mapManager);
void keyboardManager(Player &player,Map &mapManager);



#endif // INPUTMANAGER_H_INCLUDED
