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
    std::vector<std::vector<int> > getTileMap2D();//map2D pour les decors
    std::vector<std::vector<int> > getTileMap2DEntity();//map2D pour les entité
    std::vector<int> getTileMap1D();
    TileMap* getTileMap();
    bool isAccessible(int x,int y);
    sf::Vector2i getTilePos();
    int getIndex();
    void setIndex(int index);
    bool isActive(int x, int y);
    bool isActivated();
    void setActivated(bool activated);
    void updateEntityCase(int x,int y,int type); //change le type a la location [x,y] de la map2D des entité par "type"

private:


    std::vector<std::vector<int> > m_TileMap2D; // matrice de la TileMap avec les sous case (32*32)
    std::vector<std::vector<int> > m_TileMap2DEntity;
    std::vector<int> m_TileMap1D;   //vector de la map 16*16
    TileMap m_tileMap;   //TileMap lié
    sf::Vector2i m_currentTileMapManagerPos; //position de la tileMap dans la Map
    int m_index; //index de la TileMap dans la Map
    bool m_activated;  // indique si la TileMap

};

#endif // TILEMAPMANAGER_H_INCLUDED
