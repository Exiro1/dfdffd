#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "Map.h"
#include "Player.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "textManager.h"
class Player;
class GameManager
{
public:

    GameManager(Player *player,Map *mapManager,sf::RenderWindow* window);
    ~GameManager();

    Player* getPlayer();
    Map* getMapManager();
    sf::View* getView();
    void update(sf::Time t);
    std::vector<Player*> getPlayerList();
     void viewMessageBox(std::string message);
     std::vector<sf::RectangleShape>* getTextBox(){return &m_rectangleShape;}
     std::vector<sf::Text>* getTextToDraw(){return &m_textToDraw;}
     std::unordered_map<int, Player*> getMapPlayer(){return m_playerListMap;}// list of player
     void drawOverLay();

protected:



private:

    Player* m_player;
    Map* m_mapManager;
    sf::View m_PlayerView;
    std::unordered_map<int, Player*> m_playerListMap;
    std::vector<Player*> m_playerList;
    std::vector<sf::RectangleShape> m_rectangleShape;
    std::vector<sf::Text> m_textToDraw;
    sf::RenderWindow* m_window;
    textManager m_textManager;


};


#endif // GAMEMANAGER_H_INCLUDED
