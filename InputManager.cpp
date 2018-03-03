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
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                player.addCaseDir(1,0);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());
            }
            else if(x+1 > 31*(mapManager.getCurrentTileMapPos().x+1) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x+1,mapManager.getCurrentTileMapPos().y)->isAccessible(x+1,y))// case non accesible sur une Tilemap diferente -> passage a la prochaine TileMap
            {
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x+1,mapManager.getCurrentTileMapPos().y);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(1,0);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());
            }
            else  //bloqué
            {
                int xmap = (player.getCase().x+1)/32;
                int ymap = (player.getCase().y)/32;
                std::cout << " front "<< player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)) << std::endl;
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            newDir = Direction::OUEST;
            if(mapManager.getCurrentTileMapManager()->isAccessible(x-1,y))
            {
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                player.addCaseDir(-1,0);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());
            }
            else if(x-1 < 32*(mapManager.getCurrentTileMapPos().x) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x-1,mapManager.getCurrentTileMapPos().y)->isAccessible(x-1,y))
            {
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x-1,mapManager.getCurrentTileMapPos().y);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(-1,0);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());

            }
            else
            {
                int xmap = (player.getCase().x-1)/32;
                int ymap = (player.getCase().y)/32;
                std::cout << " front "<< player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)) << std::endl;
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down))
        {
            newDir = Direction::SUD;
            if(mapManager.getCurrentTileMapManager()->isAccessible(x,y+1))
            {
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                player.addCaseDir(0,1);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());
            }
            else if(y+1 > 31*(1+mapManager.getCurrentTileMapPos().y) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y+1)->isAccessible(x,y+1))
            {
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y+1);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(0,1);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());
            }
            else
            {
                int xmap = (player.getCase().x)/32;
                int ymap = (player.getCase().y+1)/32;
                std::cout << " front "<< player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)) << std::endl;
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            newDir = Direction::NORD;
            if(mapManager.getCurrentTileMapManager()->isAccessible(x,y-1))
            {
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                player.addCaseDir(0,-1);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());
            }
            else if(y-1 < 32*(mapManager.getCurrentTileMapPos().y) && mapManager.getTileMap(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y-1)->isAccessible(x,y-1))
            {
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCase()).x,player.getCaseRelative(player.getCase()).y,0);
                mapManager.changeCurrentTileMapManager(mapManager.getCurrentTileMapPos().x,mapManager.getCurrentTileMapPos().y-1);
                player.setTileMap(mapManager.getCurrentTileMapManager());
                player.addCaseDir(0,-1);
                player.getTileMap()->updateEntityCase(player.getCaseRelative(player.getCaseDir()).x,player.getCaseRelative(player.getCaseDir()).y,player.getID());
            }
            else
            {
                int xmap = (player.getCase().x)/32;
                int ymap = (player.getCase().y-1)/32;
                std::cout << " front "<< player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)) << std::endl;
            }
        }
    }
    player.setNewDir(newDir);
}
