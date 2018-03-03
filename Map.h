#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include "TileMapManager.h"
#include <string.h>
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>

class Map
{

public :

    Map();
    ~Map();

    TileMapManager* getCurrentTileMapManager();
    std::vector<TileMapManager*> getTileMapManagerToDraw();
    sf::Vector2i getCurrentTileMapPos();
    void addTileMapManager(TileMapManager* tMap,int x, int y);
    void changeCurrentTileMapManager(int x, int y);
    TileMapManager* getTileMap(int x,int y);
    void removeTileFromDraw(int index);
    void checkVisibility(int x,int y);
    void loadMap();
    std::vector<std::vector<TileMapManager*> > getTileMapList(){return m_tileMapList;}

private :


    std::vector<std::vector<TileMapManager*> > m_tileMapList;// tileMap de 16*16 case de 64*64 pixel soit TileMap de 1024*1024 pixels
    std::vector<TileMapManager*> m_tileMapListToDraw;
    TileMapManager* m_currentTileMapManager;
    sf::Vector2i m_currentTileMapManagerPos;


};


#endif // MAP_H_INCLUDED
