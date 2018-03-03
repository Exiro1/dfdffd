#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "Map.h"
#include "Player.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GameManager
{
public:
    GameManager(Player *player,Map *mapManager);


    ~GameManager();

    Player* getPlayer();
    Map* getMapManager();
    sf::View* getView();
    void update(sf::Time t);
    std::vector<Player*> getPlayerList();


protected:



private:

Player* m_player;
Map* m_mapManager;
sf::View m_PlayerView;
std::vector<Player*> m_playerList;


};


#endif // GAMEMANAGER_H_INCLUDED
