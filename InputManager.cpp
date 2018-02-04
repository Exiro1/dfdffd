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
            if(mapManager.getCurrentTileMapManager()->isAccessible(x+1,y))
            {
                player.addCaseDir(1,0);
            }
            else if(x+1 > 31*(mapManager.getCurrentTileMapPos().x+1) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x+1,mapManager.getCurrentTileMapPos().y)->isAccessible(x+1,y))
            {
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x+1,mapManager.getCurrentTileMapPos().y);
                player.addCaseDir(1,0);
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
                player.addCaseDir(-1,0);

            }
            else
            {

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
                player.addCaseDir(0,1);
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
                player.addCaseDir(0,-1);
            }
        }
    }
    player.setNewDir(newDir);
}
