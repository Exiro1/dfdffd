#include "Map.h"


Map::Map()
{
    for(int i= 0; i < 32; i++)
    {
        m_tileMapList.push_back(std::vector<TileMapManager*>(32));
    }
}

Map::~Map()
{

}
TileMapManager* Map::getCurrentTileMapManager()
{
    return m_currentTileMapManager;
}

void Map::removeTileFromDraw(int index)
{
    m_tileMapListToDraw[index]->setActivated(false);
    std::cout << m_tileMapListToDraw.size() << std::endl;
    m_tileMapListToDraw.erase(m_tileMapListToDraw.begin() + index);
    for(int i = 0; i<m_tileMapListToDraw.size(); i++)
    {
        m_tileMapListToDraw[i]->setIndex(i);
       //std::cout << m_tileMapListToDraw[i]->getTilePos().x << " " << m_tileMapListToDraw[i]->getTilePos().y << " " << m_tileMapListToDraw[i]->isActivated() << std::endl;
    }


}



sf::Vector2i Map::getCurrentTileMapPos()
{
    return m_currentTileMapManagerPos;
}
void Map::addTileMapManager(TileMapManager* tMap,int x, int y)
{
    m_tileMapList[x][y] = tMap;
 //   tMap->setIndex(m_tileMapListToDraw.size());
  //  m_tileMapListToDraw.push_back(tMap);// a chnager pr l affichage dynamique
    tMap->setActivated(false);
}
TileMapManager* Map::getTileMap(int x, int y)
{
    return m_tileMapList[x][y];
}
void Map::changeCurrentTileMapManager(int x,int y)
{
    m_currentTileMapManager = m_tileMapList[x][y];
    m_currentTileMapManagerPos = sf::Vector2i(x,y);
    std::cout << "MapTile change to " << x << " : "<< y <<std::endl;
}
std::vector<TileMapManager*> Map::getTileMapManagerToDraw()
{
    return m_tileMapListToDraw;
}

void Map::checkVisibility(int x2,int y2){
    int x = m_currentTileMapManagerPos.x-1;
    int y = m_currentTileMapManagerPos.y-1;
    for(int i=x;i<x+3;i++){
        for(int i2=y;i2<y+3;i2++){
                //std::cout << i << " "<< i2 << std::endl;
        if(i > -1 && i2 > -1 && i < m_tileMapList.size() && i2 < m_tileMapList[i].size()){

            TileMapManager *tm = m_tileMapList[i][i2];
           // std::cout << tm->getTilePos().x << " "<< tm->getTilePos().y << " " << tm->isActivated()<< std::endl;
            if(tm->isActive(x2,y2) ){
              //  std::cout << tm->getTilePos().x << " "<< tm->getTilePos().y << " is visible and state : "<< tm->isActivated() << std::endl;
                    if(!tm->isActivated()){
                tm->setIndex(m_tileMapListToDraw.size());
                m_tileMapListToDraw.push_back(tm);// a chnager pr l affichage dynamique
                tm->setActivated(true);
                std::cout << "Activate " << tm->getIndex() << " " << tm->getTilePos().x << " " << tm->getTilePos().y << std::endl;
               }}

        }
        }
    }









}


