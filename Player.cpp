#include "Player.h"
#include <iostream>


Player::Player(std::string name,sf::Vector2i posCase,int vie,int argent,TileMapManager* tileMapManager,std::string file,int ID) :  m_playerSprite(0),m_moving(false),m_speed(150.0f)
{
    m_tileMapManager = tileMapManager;
    m_playerSprite = new PlayerSprite();
    m_name = name;
    m_posCase.x = m_tileMapManager->getTilePos().x*32+posCase.x;
    m_posCase.y = m_tileMapManager->getTilePos().y*32+posCase.y;
    m_pos = caseToPosition(m_posCase);
    m_posCaseDir = m_posCase;
    m_vie = vie;
    m_argent = argent;
    m_ID = ID;
    m_oldDir = Direction::EST;

    if(m_playerSprite->load(file))
    {
        std::cout << "charger" << std::endl;
    }
    m_playerSprite->setOrigin(16,16);
    m_playerSprite->setPosition(m_pos);
    m_tileMapManager->updateEntityCase(getCaseRelative(m_posCase).x,getCaseRelative(m_posCase).y,m_ID);
}


TileMapManager* Player::getTileMap()
{
    return m_tileMapManager;
}

void Player::setTileMap(TileMapManager* tileMap)
{
    m_tileMapManager = tileMap;
}

PlayerSprite Player::getSprite()
{
    return *m_playerSprite;
}
void Player::setMoving(bool moving)
{
    m_moving = moving;
}
Direction Player::getOldDir()
{
    return m_oldDir;
}
void Player::setNewDir(Direction newDir)
{
    m_oldDir = newDir;
}
void Player::update(float deltaTime)
{


    Direction dir = m_oldDir;
    float speed = deltaTime*m_speed;
    switch (dir)
    {

    case Direction::OUEST:
        m_playerSprite->setRotation(180);
        if(m_pos.x>(caseToPosition(m_posCaseDir).x+speed))
        {
            m_pos.x -= speed;
        }
        else
        {
            m_pos = caseToPosition(m_posCaseDir);
            m_posCase = m_posCaseDir;
        }
        break;
    case Direction::EST:
        m_playerSprite->setRotation(0);
        if(m_pos.x<(caseToPosition(m_posCaseDir).x-speed))
        {
            m_pos.x += speed;
        }
        else
        {
            m_pos = caseToPosition(m_posCaseDir);
            m_posCase = m_posCaseDir;
        }
        break;
    case Direction::NORD:
        m_playerSprite->setRotation(270);
        if(m_pos.y>(caseToPosition(m_posCaseDir).y+speed))
        {
            m_pos.y -= speed;
        }
        else
        {
            m_posCase = m_posCaseDir;
            m_pos = caseToPosition(m_posCaseDir);
        }
        break;

    case Direction::SUD:
        m_playerSprite->setRotation(90);
        if(m_pos.y<(caseToPosition(m_posCaseDir).y-speed))
        {
            m_pos.y += speed;
        }
        else
        {
            m_posCase = m_posCaseDir;
            m_pos = caseToPosition(m_posCaseDir);
        }
        break;



    }
//std::cout << getGround()<< std::endl;

    m_playerSprite->setPosition(m_pos);



}
int Player::getGround()
{

    return m_tileMapManager->getTileMap2D()[m_posCase.y][m_posCase.x];
}

void Player::addCaseDir(int x, int y)
{

    m_posCaseDir.x+=x;
    m_posCaseDir.y+=y;

}
sf::Vector2f Player::getPosition()
{
    return m_pos;
}
sf::Vector2i Player::getCase()
{
    return m_posCase;
}
sf::Vector2i Player::getCaseDir()
{
    return m_posCaseDir;
}
sf::Vector2f Player::caseToPosition(sf::Vector2i case1)
{
    return sf::Vector2f(case1.x*32+16,case1.y*32+16);
}
sf::Vector2i Player::getCaseRelative(sf::Vector2i pos)
{
    int x = pos.x-m_tileMapManager->getTilePos().x*32;
    int y = pos.y-m_tileMapManager->getTilePos().y*32;
    return sf::Vector2i(x,y);
}
sf::Vector2i Player::getCaseRelative(sf::Vector2i pos,TileMapManager* tmap)
{
    int x = pos.x-tmap->getTilePos().x*32;
    int y = pos.y-tmap->getTilePos().y*32;
    return sf::Vector2i(x,y);
}

bool Player::getMoving()
{
    return m_moving;
}

int Player::getFrontType(Direction newDir,TileMapManager* tmap)
{
    int type;
    int y = getCaseRelative(m_posCase,tmap).y;
    int x = getCaseRelative(m_posCase,tmap).x;

    switch(newDir)
    {

    case Direction::EST:
        type = tmap->getTileMap2D()[y][x+1];
        if(tmap->getTileMap2DEntity()[x+1][y] != 0)
            type = tmap->getTileMap2DEntity()[x+1][y];
        break;
    case Direction::OUEST:
        type = tmap->getTileMap2D()[y][x-1];
        if(tmap->getTileMap2DEntity()[x-1][y] != 0)
            type = tmap->getTileMap2DEntity()[x-1][y];
        break;
    case Direction::NORD:
        type = tmap->getTileMap2D()[y-1][x];
        if(tmap->getTileMap2DEntity()[x][y-1] != 0)
            type = tmap->getTileMap2DEntity()[x][y-1];
        break;
    case Direction::SUD:
        type = tmap->getTileMap2D()[y+1][x];
        if(tmap->getTileMap2DEntity()[x][y+1] != 0)
            type = tmap->getTileMap2DEntity()[x][y+1];
        break;
    }
    return type;
}

Player::~Player()
{
    delete m_playerSprite;
    m_playerSprite = 0;
}
