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

using namespace sf;


Direction manageDir(Player &player,Map &mapManager,Direction newDir);

int main()
{
    RenderWindow window;

    CircleShape cercle;
    VideoMode videoMode(800,600);
    window.create(videoMode,"Test");
    window.setPosition(Vector2i(0,0));
    window.setFramerateLimit(144);
    std::cout << "Fenetre créé" << std::endl;
    float speed = 100;

    //map en 1D 64*64
    std::vector<int> level00 =
    {

        7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
        7,8,5,5,5,5,5,5,5,5,5,5,5,1,5,5,
        7,7,7,7,7,7,7,7,7,7,7,7,6,4,7,7,
        7,7,7,7,7,7,6,6,6,7,7,7,6,4,7,7,
        7,7,7,6,0,5,5,5,5,5,5,5,5,3,7,7,
        7,7,7,6,4,6,7,7,7,7,7,7,7,7,7,7,
        7,7,7,6,4,6,7,7,7,7,8,0,5,1,7,7,
        7,7,7,6,4,6,7,7,7,7,6,4,7,4,7,7,
        7,7,7,6,4,6,6,9,6,6,6,4,7,4,7,7,
        7,7,7,6,2,5,5,5,5,5,5,3,7,4,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,7,4,7,7,
        7,7,6,6,6,6,7,7,7,7,6,7,6,4,7,7,
        7,6,0,5,5,5,5,5,5,5,5,5,5,3,7,7,
        7,6,4,6,6,6,7,7,7,7,7,7,7,7,7,7,
        7,6,4,6,6,7,7,7,7,7,7,7,7,7,7,7,
        7,6,4,6,7,7,7,7,7,7,7,7,7,7,7,6
    };
    std::vector<int> level01 =
    {

        7,6,4,6,7,7,7,7,7,7,7,7,7,7,7,6,
        7,6,2,5,5,5,5,5,5,5,5,5,5,1,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,6,4,7,7,
        7,7,7,7,7,7,6,6,6,7,7,7,6,4,7,7,
        7,7,7,6,0,5,5,5,5,5,5,5,5,3,7,7,
        7,7,7,6,4,6,7,7,7,7,7,7,7,7,7,7,
        7,7,7,6,4,6,7,7,7,7,8,0,5,1,7,7,
        7,7,7,6,4,6,7,7,7,7,6,4,7,4,7,7,
        7,7,7,6,4,6,6,9,6,6,6,4,7,4,7,7,
        7,7,7,6,2,5,5,5,5,5,5,3,7,4,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,7,4,7,7,
        7,7,6,6,6,6,7,7,7,7,6,7,6,4,7,7,
        7,6,0,5,5,5,5,5,5,5,5,5,5,3,7,7,
        7,6,4,6,6,6,7,7,7,7,7,7,7,7,7,7,
        7,6,4,6,6,7,7,7,7,7,7,7,7,7,7,7,
        7,6,4,6,7,7,7,7,7,7,7,7,7,7,7,7
    };

    std::vector<int> level10 =
    {

        7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
        5,5,5,5,5,5,5,5,5,5,5,5,5,1,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,6,4,7,7,
        7,7,7,7,7,7,6,6,6,7,7,7,6,4,7,7,
        7,7,7,6,0,5,5,5,5,5,5,5,5,3,7,7,
        7,7,7,6,4,6,7,7,7,7,7,7,7,7,7,7,
        7,7,7,6,4,6,7,7,7,7,8,0,5,1,7,7,
        7,7,7,6,4,6,7,7,7,7,6,4,7,4,7,7,
        7,7,7,6,4,6,6,9,6,6,6,4,7,4,7,7,
        7,7,7,6,2,5,5,5,5,5,5,3,7,4,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,7,4,7,7,
        7,7,6,6,6,6,7,7,7,7,6,7,6,4,7,7,
        7,6,0,5,5,5,5,5,5,5,5,5,5,3,7,7,
        7,6,4,6,6,6,7,7,7,7,7,7,7,7,7,7,
        7,6,4,6,6,7,7,7,7,7,7,7,7,7,7,7,
        6,6,4,6,7,7,7,7,7,7,7,7,7,7,7,7
    };

    std::vector<int> level11 =
    {

        6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
        5,5,5,5,5,5,5,5,5,5,5,5,5,1,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,6,4,7,7,
        7,7,7,7,7,7,6,6,6,7,7,7,6,4,7,7,
        7,7,7,6,0,5,5,5,5,5,5,5,5,3,7,7,
        7,7,7,6,4,6,7,7,7,7,7,7,7,7,7,7,
        7,7,7,6,4,6,7,7,7,7,8,0,5,1,7,7,
        7,7,7,6,4,6,7,7,7,7,6,4,7,4,7,7,
        7,7,7,6,4,6,6,9,6,6,6,4,7,4,7,7,
        7,7,7,6,2,5,5,5,5,5,5,3,7,4,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,7,4,7,7,
        7,7,6,6,6,6,7,7,7,7,6,7,6,4,7,7,
        7,6,0,5,5,5,5,5,5,5,5,5,5,3,7,7,
        7,6,4,6,6,6,7,7,7,7,7,7,7,7,7,7,
        7,6,4,6,6,7,7,7,7,7,7,7,7,7,7,7,
        7,6,4,6,7,7,7,7,7,7,7,7,7,7,7,7
    };
    std::vector<int> leveltest =
    {

        6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
        6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,6,6,6,6,6,6,6,6,6,6,6,6,5,6,
        6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,
        6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
    };


    std::cout << "creation de l object Map" << std::endl;
    Map mapManager;
    mapManager.loadMap();
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



    /* mapManager.addTileMapManager(new TileMapManager("File/image.png",Vector2u(64,64),level00,16,16,0,0),0,0);
    mapManager.addTileMapManager(new TileMapManager("File/image.png",Vector2u(64,64),level01,16,16,0,1),0,1);
     mapManager.addTileMapManager(new TileMapManager("File/image.png",Vector2u(64,64),level10,16,16,1,0),1,0);
     mapManager.addTileMapManager(new TileMapManager("File/image.png",Vector2u(64,64),level10,16,16,1,1),1,1);

     for(int i=2; i<32; i++)
     {
         for(int i2=0; i2<32; i2++)
         {
             mapManager.addTileMapManager(new TileMapManager("File/image.png",Vector2u(64,64),leveltest,16,16,i,i2),i,i2);

         }
     }
     for(int i=0; i<2; i++)
     {
         for(int i2=2; i2<32; i2++)
         {
             mapManager.addTileMapManager(new TileMapManager("File/image.png",Vector2u(64,64),leveltest,16,16,i,i2),i,i2);

         }
     }*/

    mapManager.changeCurrentTileMapManager(0,0);
    mapManager.getCurrentTileMapManager()->getTileMap()->setPosition(0,0);
    std::cout << "object TileMapManager ajouté a Map" << std::endl;

    /*  for(int x=0; x<32; x++)
      {
          for(int y=0; y<32; y++)
          {
              std::cout << mapManager.getCurrentTileMapManager()->getTileMap2D()[x][y];
          }
          std::cout << std::endl;
      }*/


    sf::View view1(sf::FloatRect(0,0,256,192));
    Clock clock;
    Time t;


    Player player("Exiro",sf::Vector2i(4,2),100,100,mapManager.getCurrentTileMapManager());
    std::cout << "joueur créé" << std::endl;


    mapManager.getCurrentTileMapManager()->getTileMap()->setOrigin(0,0);

    while(window.isOpen())
    {
        Event event;

        Vector2f newPosi(player.getPosition());

        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        keyboardManager(player,mapManager);
        player.update(t.asSeconds());

        view1.setCenter(player.getPosition());
        t = clock.restart();

        window.clear();
        window.setView(view1);

        mapManager.checkVisibility(player.getPosition().x,player.getPosition().y); // ajoute les tiles visible
        for(int i=0; i<mapManager.getTileMapManagerToDraw().size(); i++)
        {

            //  std::cout <<  mapManager.getTileMapManagerToDraw()[i]->getIndex() << " vrai ID : "<< i << std::endl;
            TileMapManager tile = *mapManager.getTileMapManagerToDraw()[i];

            if(!tile.isActive(player.getPosition().x,player.getPosition().y))
            {

                mapManager.removeTileFromDraw(tile.getIndex());
                std::cout << tile.getIndex() << " removed Position : " << tile.getTilePos().x << " , " <<tile.getTilePos().y << std::endl;
                i = i-1;
            }
            else
            {

                tile.getTileMap()->setPosition(tile.getTilePos().x*1024,tile.getTilePos().y*1024);
                window.draw(*tile.getTileMap());
            }
        }
        window.draw(player.getSprite());
        window.display();

    }



    return 0;
}





























