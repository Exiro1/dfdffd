#include "InputManager.h"


using namespace sf;

void actionManager(Player &player,Map &mapManager)
{

}
void keyboardManager(Player &player,Map &mapManager)
{
    actionManager(player,mapManager);
    movementManager(player,mapManager);

}

void movementManager(Player &player,Map &mapManager)
{

    Direction newDir = player.getOldDir();

    if(player.getPosition() == player.caseToPosition(player.getCaseDir()))
    {
        int x = player.getCase().x;
        int y = player.getCase().y;

        if(Keyboard::isKeyPressed(Keyboard::Right) )
        {
            newDir = Direction::EST ;
            if(mapManager.getCurrentTileMapManager()->isAccessible(x+1,y))//case accesible (sur la current tilemap
            {
                player.addCaseDir(1,0);
            }
            else if(x+1 > 31*(mapManager.getCurrentTileMapPos().x+1) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x+1,mapManager.getCurrentTileMapPos().y)->isAccessible(x+1,y))// case non accesible sur une Tilemap diferente -> passage a la prochaine TileMap
            {
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x+1,mapManager.getCurrentTileMapPos().y);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(1,0);
            }else //bloqué
            {
               std::cout << player.getFrontType(newDir) << std::endl;
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            newDir = Direction::OUEST;
            if(mapManager.getCurrentTileMapManager()->isAccessible(x-1,y))
            {
                player.addCaseDir(-1,0);
            }
            else if(x-1 < 32*(mapManager.getCurrentTileMapPos().x) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x-1,mapManager.getCurrentTileMapPos().y)->isAccessible(x-1,y))
            {
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x-1,mapManager.getCurrentTileMapPos().y);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(-1,0);

            }
            else
            {
               std::cout << player.getFrontType(newDir) << std::endl;
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down))
        {
            newDir = Direction::SUD;
            if(mapManager.getCurrentTileMapManager()->isAccessible(x,y+1))
            {
                player.addCaseDir(0,1);
            }
            else if(y+1 > 31*(1+mapManager.getCurrentTileMapPos().y) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y+1)->isAccessible(x,y+1))
            {
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y+1);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(0,1);
            }else
            {
               std::cout << player.getFrontType(newDir) << std::endl;
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            newDir = Direction::NORD;
            if(mapManager.getCurrentTileMapManager()->isAccessible(x,y-1))
            {
                player.addCaseDir(0,-1);
            }
            else if(y-1 < 32*(mapManager.getCurrentTileMapPos().y) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y-1)->isAccessible(x,y-1))
            {
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y-1);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(0,-1);
            }else
            {
               std::cout << player.getFrontType(newDir) << std::endl;
            }
        }
    }
    player.setNewDir(newDir);
}
