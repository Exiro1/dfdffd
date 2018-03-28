#include "InputManager.h"


using namespace sf;


InputManager::InputManager(){
    m_keyMap[Keyboard::E] = false;
}

InputManager::~InputManager(){
}

void InputManager::actionManager(Player &player,Map &mapManager)
{



    if(Keyboard::isKeyPressed(Keyboard::E) && !m_keyMap[Keyboard::E])
    {
        std::cout << "touche E appuye" << std::endl;
        m_keyMap[Keyboard::E] = true;
        Direction dir = player.getOldDir();
        int xmap;
        int ymap;
        switch(dir)
        {
        case Direction::EST:
            xmap = (player.getCase().x+1)/32;
            ymap = (player.getCase().y)/32;
            break;
        case Direction::OUEST:
            xmap = (player.getCase().x-1)/32;
            ymap = (player.getCase().y)/32;
            break;
        case Direction::SUD:
            xmap = (player.getCase().x)/32;
            ymap = (player.getCase().y+1)/32;
            break;
        case Direction::NORD:
            xmap = (player.getCase().x)/32;
            ymap = (player.getCase().y-1)/32;

            break;
        }
        int type = player.getFrontType(player.getOldDir(),mapManager.getTileMap(xmap,ymap));
        BlockType block = TileMapManager::getBlockType(type);
        if(block == BlockType::PLAYER)
        {
            Player* p = player.getGameManager()->getMapPlayer()[type];
            if(!player.isInteracting()){
            std::cout << "Interact with " << p->getPseudo()<< std::endl;
            player.getGameManager()->viewMessageBox(player.getGameManager()->getTextManager()->getNextText(p->getID()));
            p->setInteracting(true);
            player.setInteracting(true);
            }else{
            // continuer a parler ou arreter le dialogue (si dialogue finit
            std::string text = player.getGameManager()->getTextManager()->getNextText(p->getID());
            if(text == "EOF"){
            p->setInteracting(false);
            player.setInteracting(false);
            player.getGameManager()->getTextBox()->clear();
            player.getGameManager()->getTextToDraw()->clear();
            }else{
                std::cout << "no EOF"<< std::endl;
            player.getGameManager()->viewMessageBox(text);
            }
            }
        }

    }else if(Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Z) || Keyboard::isKeyPressed(Keyboard::Q) || Keyboard::isKeyPressed(Keyboard::S))
    {
        if(player.isInteracting()){ //pour arreter l'interaction
        Direction dir = player.getOldDir();
        int xmap;
        int ymap;
        switch(dir)
        {
        case Direction::EST:
            xmap = (player.getCase().x+1)/32;
            ymap = (player.getCase().y)/32;
            break;
        case Direction::OUEST:
            xmap = (player.getCase().x-1)/32;
            ymap = (player.getCase().y)/32;
            break;
        case Direction::SUD:
            xmap = (player.getCase().x)/32;
            ymap = (player.getCase().y+1)/32;
            break;
        case Direction::NORD:
            xmap = (player.getCase().x)/32;
            ymap = (player.getCase().y-1)/32;

            break;
        }
        int type = player.getFrontType(player.getOldDir(),mapManager.getTileMap(xmap,ymap));
        BlockType block = TileMapManager::getBlockType(type);
        if(block == BlockType::PLAYER)
        {
            Player* pToInteract = player.getGameManager()->getMapPlayer()[type];
            std::cout << "stop interact with " << pToInteract->getPseudo()<< std::endl;
            pToInteract->setInteracting(false);
            player.setInteracting(false);
            player.getGameManager()->getTextBox()->clear();
            player.getGameManager()->getTextToDraw()->clear();
            std::cout <<  player.getGameManager()->getTextBox()->size()<< std::endl;
            }
        }
    }

    if(!Keyboard::isKeyPressed(Keyboard::E)){
    m_keyMap[Keyboard::E] = false;
    }
}
void InputManager::keyboardManager(Player &player,Map &mapManager)
{
    actionManager(player,mapManager);
    movementManager(player,mapManager);

}

void InputManager::movementManager(Player &player,Map &mapManager)
{

    Direction newDir = player.getOldDir();

    if(player.getPosition() == player.caseToPosition(player.getCaseDir()))
    {
        int x = player.getCase().x;
        int y = player.getCase().y;

        if(Keyboard::isKeyPressed(Keyboard::D) )
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
                player.actionByBlocking(player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)));
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Q))
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
                player.actionByBlocking(player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)));
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::S))
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
                player.actionByBlocking(player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)));
            }
        }
        else if(Keyboard::isKeyPressed(Keyboard::Z))
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

                player.actionByBlocking(player.getFrontType(newDir,mapManager.getTileMap(xmap,ymap)));
            }
        }
    }
    player.setNewDir(newDir);
}
