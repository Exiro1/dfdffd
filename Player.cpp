#include "Player.h"
#include <iostream>


Player::Player(Map* mapManager,std::string name,sf::Vector2i posCase,int vie,int argent,TileMapManager* tileMapManager,std::string file,int ID,bool isBot) :m_mapManager(0), m_movePattern(std::vector<sf::Vector2i>()),m_playerSprite(0),m_moving(false),m_speed(150.0f)
{

    m_mapManager = mapManager;
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
    m_bot = isBot;
    m_isInteracting = false;
    if(m_playerSprite->load(file))
    {
        std::cout << "charger" << std::endl;
    }
    m_playerSprite->setOrigin(16,16);
    m_playerSprite->setPosition(m_pos);
    m_tileMapManager->updateEntityCase(getCaseRelative(m_posCase).x,getCaseRelative(m_posCase).y,m_ID);
}
Player::Player(Map* mapManager,std::string name,sf::Vector2i posCase,int vie,int argent,TileMapManager* tileMapManager,std::string file,int ID,bool isBot,std::vector<sf::Vector2i> Pattern) :  m_mapManager(0),m_movePattern(Pattern),m_playerSprite(0),m_moving(false),m_speed(150.0f)
{
    m_mapManager = mapManager;
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
    m_bot = isBot;
    m_isInteracting = false;
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


void Player::moveBot()// que pour les obt
{
    if(m_pos == this->caseToPosition(this->getCaseDir()) && !m_isInteracting)
    {
        sf::Vector2i v = m_movePattern.getNextCase();
        int x = m_posCase.x;
        int y = m_posCase.y;
        Direction newDir;

        if(v.x == 1)
            newDir = Direction::EST;
        if(v.x == -1)
            newDir = Direction::OUEST;
        if(v.y == 1)
            newDir = Direction::SUD;
        if(v.y == -1)
            newDir = Direction::NORD;

        if(this->getTileMap()->isAccessible(x+v.x,y+v.y))
        {
            this->getTileMap()->updateEntityCase(getCaseRelative(this->getCase()).x,this->getCaseRelative(this->getCase()).y,0);
            this->addCaseDir(v.x,v.y);
            m_movePattern.add();
            this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCaseDir()).x,this->getCaseRelative(this->getCaseDir()).y,this->getID());
            this->setNewDir(newDir);

        }
        else
        {
            switch(newDir)
            {
            case Direction::EST :
                if(x+1 > 31*(m_tileMapManager->getTilePos().x+1) && m_mapManager->getTileMap(m_tileMapManager->getTilePos().x+1,m_tileMapManager->getTilePos().y)->isAccessible(x+1,y))
                {
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCase()).x,this->getCaseRelative(this->getCase()).y,0);
                    this->setTileMap(m_mapManager->getTileMap(m_tileMapManager->getTilePos().x+1,m_tileMapManager->getTilePos().y));
                    this->addCaseDir(1,0);
                    m_movePattern.add();
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCaseDir()).x,this->getCaseRelative(this->getCaseDir()).y,this->getID());
                }
                break;
            case Direction::OUEST:
                if(x-1 < 32*(m_tileMapManager->getTilePos().x) && m_mapManager->getTileMap(m_tileMapManager->getTilePos().x-1,m_tileMapManager->getTilePos().y)->isAccessible(x-1,y))
                {
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCase()).x,this->getCaseRelative(this->getCase()).y,0);
                    this->setTileMap(m_mapManager->getTileMap(m_tileMapManager->getTilePos().x-1,m_tileMapManager->getTilePos().y));
                    this->addCaseDir(-1,0);
                    m_movePattern.add();
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCaseDir()).x,this->getCaseRelative(this->getCaseDir()).y,this->getID());
                }
                break;
            case Direction::NORD :
                if(y-1 < 32*(m_tileMapManager->getTilePos().y) && m_mapManager->getTileMap(m_tileMapManager->getTilePos().x,m_tileMapManager->getTilePos().y-1)->isAccessible(x,y-1))

                {
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCase()).x,this->getCaseRelative(this->getCase()).y,0);
                    this->setTileMap(m_mapManager->getTileMap(m_tileMapManager->getTilePos().x,m_tileMapManager->getTilePos().y-1));
                    this->addCaseDir(0,-1);
                    m_movePattern.add();
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCaseDir()).x,this->getCaseRelative(this->getCaseDir()).y,this->getID());
                }
                break;
            case Direction::SUD :
                if(y+1 > 31*(1+m_tileMapManager->getTilePos().y) && m_mapManager->getTileMap(m_tileMapManager->getTilePos().x,m_tileMapManager->getTilePos().y+1)->isAccessible(x,y+1))
                {
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCase()).x,this->getCaseRelative(this->getCase()).y,0);
                    this->setTileMap(m_mapManager->getTileMap(m_tileMapManager->getTilePos().x,m_tileMapManager->getTilePos().y+1));
                    this->addCaseDir(0,1);
                    m_movePattern.add();
                    this->getTileMap()->updateEntityCase(this->getCaseRelative(this->getCaseDir()).x,this->getCaseRelative(this->getCaseDir()).y,this->getID());
                }
                break;

            }


        }



    }
}

void Player::actionByBlocking(int blockType)
{
 BlockType block = TileMapManager::getBlockType(blockType);
 if(block == BlockType::PLAYER){

 }
}




Player::~Player()
{
    delete m_playerSprite;
    m_playerSprite = 0;
}
