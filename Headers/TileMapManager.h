#ifndef TILEMAPMANAGER_H_INCLUDED
#define TILEMAPMANAGER_H_INCLUDED
#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
class TileMapManager
{

public :

    TileMapManager(const std::string& tileset, sf::Vector2u tileSize,  std::vector<int> &tiles, unsigned int width, unsigned int height,int x,int y);
    ~TileMapManager();
    std::vector<std::vector<int> > getTileMap2D();
    std::vector<int> getTileMap1D();
    TileMap* getTileMap();
    bool isAccessible(int x,int y);
    sf::Vector2i getTilePos();
    int getIndex();
    void setIndex(int index);
    bool isActive(int x, int y);
    bool isActivated();
    void setActivated(bool activated);

private:


    std::vector<std::vector<int> > m_TileMap2D;
    std::vector<int> m_TileMap1D;
    TileMap m_tileMap;
    sf::Vector2i m_currentTileMapManagerPos;
    int m_index;
    bool m_activated;

};

#endif // TILEMAPMANAGER_H_INCLUDED
