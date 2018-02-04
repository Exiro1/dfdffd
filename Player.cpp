#include "Player.h"
#include <iostream>


Player::Player(std::string name,sf::Vector2i posCase,int vie,int argent,TileMapManager *tileMapManager) :  m_playerSprite(0),m_moving(false),m_speed(150.0f)
{

    m_tileMapManager = tileMapManager;
    m_playerSprite = new PlayerSprite();
    m_name = name;
    m_posCase = posCase;
    m_pos = caseToPosition(m_posCase);
    m_posCaseDir = m_posCase;
    m_vie = vie;
    m_argent = argent;
    m_oldDir = Direction::EST;

    if(m_playerSprite->load("File/perso.png"))
    {
        std::cout << "charger" << std::endl;


    }
    m_playerSprite->setOrigin(16,16);
    m_playerSprite->setPosition(m_pos);


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

bool Player::getMoving()
{
    return m_moving;
}

Player::~Player()
{

    delete m_playerSprite;
    m_playerSprite = 0;

}








