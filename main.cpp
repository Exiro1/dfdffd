#include <iostream>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"
#include "TileMapManager.h"
#include <vector>
#include "Map.h"
#include "InputManager.h"
#include <iostream>
#include <fstream>
#include "GameManager.h"
#include "textManager.h"

using namespace sf;

//generation du fichier map

//std::cout << "creation de l object TileMapManager" << std::end;
/*td::ofstream fichier("File/MapPackage.tml", std::ios::out | std::ios::trunc);
 if(fichier){
 for(int i=0; i<32; i++)
 {
     for(int i2=0; i2<32; i2++)
     {
         fichier << "6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6," << std::endl;
         fichier << "6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6," << std::endl;
         fichier << "6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6," << std::endl;
         fichier << "6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6," << std::endl;
     }
 }
 }*/

Direction manageDir(Player &player,Map &mapManager,Direction newDir);

static int tes = 2;

int main()
{
    RenderWindow window;

    CircleShape cercle;
    VideoMode videoMode(800,600);
    window.create(videoMode,"SHOAH III");
    window.setPosition(Vector2i(0,0));
    window.setFramerateLimit(144);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);
    std::cout << "Fenetre créé" << std::endl;
    float speed = 100;

    std::cout << "creation de l object Map" << std::endl;

    Map mapManager;
    Map* mapPtr(0);
    mapPtr = &mapManager;
    mapManager.loadMap();
    mapManager.changeCurrentTileMapManager(0,0);
    mapManager.getCurrentTileMapManager()->getTileMap()->setPosition(0,0);
    std::cout << "object TileMapManager ajouté a Map" << std::endl;
    Player p(mapPtr,"Exiro",sf::Vector2i(6,2),100,100,mapManager.getCurrentTileMapManager(),"File/perso.png",1,false);
    RenderWindow* windowPtr(0);
    windowPtr = &window;
    GameManager gm(&p,mapPtr,windowPtr);
    p.setGameManager(&gm);
    Clock clock;
    Time t;



    //Player player("Exiro",sf::Vector2i(4,2),100,100,mapManager.getCurrentTileMapManager(),"File/perso.png");


    std::cout << "joueurs créés" << std::endl;


    gm.getMapManager()->getCurrentTileMapManager()->getTileMap()->setOrigin(0,0);

    while(window.isOpen())
    {
        Event event;

        //Vector2f newPosi(player.getPosition());

        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        // keyboardManager(player,mapManager);
        //   player.update(t.asSeconds());

        //  view1.setCenter(player.getPosition());



        window.clear();
        gm.update(t);
        window.setView(*gm.getView());

        gm.getMapManager()->checkVisibility(gm.getPlayer()->getPosition().x,gm.getPlayer()->getPosition().y); // ajoute les tiles visible
        for(int i=0; i< gm.getMapManager()->getTileMapManagerToDraw().size(); i++)
        {
            TileMapManager tile = *gm.getMapManager()->getTileMapManagerToDraw()[i];
            if(!tile.isActive(gm.getPlayer()->getPosition().x,gm.getPlayer()->getPosition().y))
            {
                gm.getMapManager()->removeTileFromDraw(tile.getIndex());
                std::cout << tile.getIndex() << " removed Position : " << tile.getTilePos().x << " , " <<tile.getTilePos().y << std::endl;
                i = i-1;
            }
            else
            {
                tile.getTileMap()->setPosition(tile.getTilePos().x*1024,tile.getTilePos().y*1024);
                window.draw(*tile.getTileMap());
            }
        }





        window.draw(gm.getPlayer()->getSprite());
        gm.getPlayer()->getTileMap()->getTilePos();

        for(int i =0; i<gm.getPlayerList().size(); i++)
        {

            if(gm.getPlayerList()[i]->isBot())
            {
                gm.getPlayerList()[i]->moveBot();
                gm.getPlayerList()[i]->update(t.asSeconds());
            }
            if(gm.getPlayerList()[i]->getTileMap()->isActivated())
            {
                //  std::cout << gm.getPlayerList()[i]->getTileMap() << " : "<< gm.getPlayer()->getTileMap() << std::endl;
                window.draw(gm.getPlayerList()[i]->getSprite());
            }
        }

        gm.drawOverLay();
        t = clock.restart();
        window.display();

    }



    return 0;
}
