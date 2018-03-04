#include "GameManager.h"

GameManager::GameManager(Player* p,Map* mapManager)
{
    m_mapManager = mapManager;
    m_player = p;
    m_PlayerView = sf::View(sf::FloatRect(0,0,256,192));
    std::vector< sf::Vector2i> pattern;
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(0,1));
    pattern.push_back(sf::Vector2i(-1,0));
    pattern.push_back(sf::Vector2i(-1,0));
    pattern.push_back(sf::Vector2i(-1,0));
    pattern.push_back(sf::Vector2i(0,-1));

    m_playerList.push_back(new Player("Alex6",sf::Vector2i(8,2),100,100,m_mapManager->getTileMapList()[0][0],"File/perso2.png",2,true,pattern));

    pattern.clear();
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(1,0));
    pattern.push_back(sf::Vector2i(-1,0));
    pattern.push_back(sf::Vector2i(-1,0));
    pattern.push_back(sf::Vector2i(-1,0));
    pattern.push_back(sf::Vector2i(-1,0));
    pattern.push_back(sf::Vector2i(-1,0));


    m_playerList.push_back(new Player("Alex7",sf::Vector2i(12,3),100,100,m_mapManager->getTileMapList()[0][0],"File/perso3.png",3,true,pattern));

    //m_playerList.push_back(new Player("Alex8",sf::Vector2i(7,3),100,100,m_mapManager->getTileMapList()[1][0],"File/perso3.png",4,true));

}

GameManager::~GameManager()
{
    for(int i=0; i<m_playerList.size(); i++)
    {
        delete m_playerList[i];
        m_playerList[i] = 0;
    }
}

Player* GameManager::getPlayer()
{
    return m_player;
}
sf::View* GameManager::getView()
{
    return &m_PlayerView;
}
Map* GameManager::getMapManager()
{
    return m_mapManager;
}
std::vector<Player*> GameManager::getPlayerList()
{
    return m_playerList;
}

void GameManager::update(sf::Time t)
{

    keyboardManager(*m_player,*m_mapManager);
    m_player->update(t.asSeconds());
    m_PlayerView.setCenter(m_player->getPosition());

}
