#include "TileMapManager.h"

TileMapManager::~TileMapManager()
{

}

TileMapManager::TileMapManager(const std::string& tileset, sf::Vector2u tileSize,  std::vector<int> &tiles, unsigned int width, unsigned int height,int x,int y)
{
    m_activated = false;
    m_TileMap1D = tiles;
    m_currentTileMapManagerPos = sf::Vector2i(x,y);
    for(int i= 0; i < 32; i++)
    {
        m_TileMap2D.push_back(std::vector<int>(32));
        m_TileMap2DEntity.push_back(std::vector<int>(32));
    }
    //std::cout << "map 2D initilaliseé" << std::endl;
    for(int x=0; x<16; x++)
    {
        for(int y=0; y<16; y++)
        {
            int valeur =m_TileMap1D[x*16+y];
            for(int x2=0; x2<2; x2++)
            {
                for(int y2=0; y2<2; y2++)
                {
                    //    std::cout << x*2+x2 << " "<< y*2+y2 << ":" << valeur<<std::endl;
                    m_TileMap2DEntity[x*2+x2][y*2+y2] = 0;
                    m_TileMap2D[x*2+x2][y*2+y2] = valeur;
                }
            }
        }
    }
    //std::cout << "map 2d cree" << std::endl;
    if(m_tileMap.load(tileset,tileSize,tiles,width,height))
    {
      //  std::cout << "object tileMap créé" << std::endl;
    }

}

bool TileMapManager::isActive(int x,int y)
{
    int marge = 64;
    int xR = x+128;
    int xL = x-128;
    int yU = y-96;
    int yD = y+96;
    //std::cout << "position : " << x << " " << y <<" "<< m_currentTileMapManagerPos.x << " " << m_currentTileMapManagerPos.y << std::endl;
    if((((m_currentTileMapManagerPos.x)*1024)-marge < xR) && (((m_currentTileMapManagerPos.x+1)*1024)+marge > xL))
    {
        //   std::cout << "x  : " << x << " " << y <<" "<< m_currentTileMapManagerPos.x << " " << m_currentTileMapManagerPos.y << std::endl;
        if(((m_currentTileMapManagerPos.y)*1024)-marge < yD && ((m_currentTileMapManagerPos.y+1)*1024)+marge > yU)
        {
            //        std::cout << "y  : " << x << " " << y <<" "<< m_currentTileMapManagerPos.x << " " << m_currentTileMapManagerPos.y << std::endl;
            //    std::cout << "Active "<< std::endl;
            return true;
        }
    }
    // std::cout << "Inactive "<< std::endl;
    return false;

}


int TileMapManager::getIndex()
{
    return m_index;
}
void TileMapManager::setIndex(int index)
{
    m_index = index;
}
void TileMapManager::updateEntityCase(int x,int y,int type)
{
    m_TileMap2DEntity[x][y] = type;
}
TileMap* TileMapManager::getTileMap()
{
    return &m_tileMap;
}
std::vector<int> TileMapManager::getTileMap1D()
{
    return m_TileMap1D;
}
std::vector<std::vector<int> > TileMapManager::getTileMap2D()
{
    return m_TileMap2D;
}
std::vector<std::vector<int> > TileMapManager::getTileMap2DEntity()
{
    return m_TileMap2DEntity;
}
sf::Vector2i TileMapManager::getTilePos()
{
    return m_currentTileMapManagerPos;
}
bool TileMapManager::isAccessible(int x,int y)
{

    if(x<32*(m_currentTileMapManagerPos.x+1) && x>32*(m_currentTileMapManagerPos.x)-1 && y <32*(m_currentTileMapManagerPos.y+1) && y > 32*(m_currentTileMapManagerPos.y)-1)
    {
        int type = m_TileMap2D[y-(32*m_currentTileMapManagerPos.y)][x-(32*m_currentTileMapManagerPos.x)];
        int entity = m_TileMap2DEntity[x-(32*m_currentTileMapManagerPos.x)][y-(32*m_currentTileMapManagerPos.y)];
        if(type == 7 || type == 8 || type == 9 || entity != 0)
        {
            //   std::cout << entity << std::endl;
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }

}
bool TileMapManager::isActivated()
{
    return m_activated;
}
void TileMapManager::setActivated(bool activated)
{
    m_activated = activated;
}

BlockType TileMapManager::getBlockType(int blocknumber){
  if(blocknumber == 0 || blocknumber == 1 ||blocknumber == 2 ||blocknumber == 3 || blocknumber == 4 || blocknumber == 5)
    return BlockType::ROAD; //road
  if(blocknumber == 6)
    return BlockType::PASSALE; //vide (grass etc...)
  if(blocknumber == 7)
    return BlockType::SOLID; //(blcok fix non passable (arbre objet deco...)
  if(blocknumber == 8 || blocknumber == 9)
    return BlockType::BUILDING; //(maison , batiment entrable)
  if(blocknumber >= 1000)
    return BlockType::PLAYER;//player

    return BlockType::SOLID;
}



