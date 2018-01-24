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
enum class Direction {EST,OUEST,NORD,SUD};

class Player
{

public :

    Player(std::string name,sf::Vector2i posCase,int vie,int argent,TileMapManager *tileMapManager );


    PlayerSprite getSprite();
    sf::Vector2f getPosition();
    sf::Vector2i getCase();
    sf::Vector2i getCaseDir();
    Direction getOldDir();
    void setNewDir(Direction newDir);
    sf::Vector2f caseToPosition(sf::Vector2i m_posCase);
    void update(float deltaTime);
    void addCaseDir(int x,int y);
    ~Player();
    void setMoving(bool moving);
    bool getMoving();
    int getGround();


private :


    std::string m_name;
    sf::Vector2f m_pos;
    sf::Vector2i m_posCase;
    int m_vie;
    float m_speed;
    int m_argent;
    PlayerSprite *m_playerSprite;
    bool m_moving;
    TileMapManager *m_tileMapManager;
    sf::Vector2i m_posCaseDir;
    Direction m_oldDir;

};





#endif // PLAYER_H_INCLUDED
