#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

//
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"
#include "TileMapManager.h"
#include "Map.h"
#include "SFML/Window.hpp"
#include "MovePattern.h"

enum class Direction {EST,OUEST,NORD,SUD};

class Player
{

public :

    Player(std::string name,sf::Vector2i posCase,int vie,int argent,TileMapManager *tileMapManager,std::string file,int ID,bool isBot);
    Player(std::string name,sf::Vector2i posCase,int vie,int argent,TileMapManager *tileMapManager,std::string file,int ID,bool isBot,std::vector<sf::Vector2i> Pattern);

    PlayerSprite getSprite();
    sf::Vector2f getPosition();
    sf::Vector2i getCase();
    sf::Vector2i getCaseRelative(sf::Vector2i pos);
    sf::Vector2i getCaseRelative(sf::Vector2i pos,TileMapManager* tmap);
    sf::Vector2i getCaseDir();
    int getID()
    {
        return m_ID;
    }
    Direction getOldDir();
    void setNewDir(Direction newDir);
    sf::Vector2f caseToPosition(sf::Vector2i m_posCase);
    void update(float deltaTime);
    void addCaseDir(int x,int y);
    ~Player();
    void setMoving(bool moving);
    bool getMoving();
    int getGround();
    int getFrontType(Direction newDir,TileMapManager* tmap);
    TileMapManager* getTileMap();
    void setTileMap(TileMapManager* tileMap);
    bool isBot(){return m_bot;}
    void moveBot();


private :


    std::string m_name;
    sf::Vector2f m_pos;
    sf::Vector2i m_posCase;
    int m_vie;
    float m_speed;
    int m_argent;
    int m_ID;
    PlayerSprite *m_playerSprite;
    bool m_moving;
    TileMapManager *m_tileMapManager;
    sf::Vector2i m_posCaseDir;
    Direction m_oldDir;
    bool m_bot;
    MovePattern m_movePattern;


};





#endif // PLAYER_H_INCLUDED
