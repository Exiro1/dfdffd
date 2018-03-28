#include "GameManager.h"

using namespace std;

/*vector<string> split(string phrase, string delimiter)
{
    vector<string> list;
    string s = phrase;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return list;
}*/

GameManager::GameManager(Player* p,Map* mapManager,sf::RenderWindow* window) : m_window(0) , m_mapManager(0), m_player(0)
{

   // textManager m_textManager;
    m_window = window;
    m_mapManager = mapManager;
    m_player = p;
    m_PlayerView = sf::View(sf::FloatRect(0,0,256,192));
    m_inputManager = new InputManager;
    m_textManager = new textManager;

    //File structure pseudo;x;y;x2;y2;vie;argent;file;ID;bot(1/0);1,0/1,0/...
    ifstream mapFile("File/PlayerPackage.dp",std::ios::in);
    if(mapFile)
    {
        if(mapFile)
        {

            int x =0;
            int x2 = 0;
            int y2 = 0;
            string test;
            string line;
            while(getline(mapFile, line))
            {
                vector<string> list = textManager::split(line,";");
                string pseudo = list[0];
                int x = stoi(list[1]);
                int y = stoi(list[2]);
                int x2 = stoi(list[5]);
                int y2 = stoi(list[6]);
                int vie = stoi(list[3]);
                int argent = stoi(list[4]);
                string file = list[7];
                int ID = stoi(list[8]);
                bool bot = true;

                std::vector< sf::Vector2i> patternPlayer;
                vector<string> pattern = textManager::split(list[10],"/");
                for(int i =0; i<pattern.size(); i++)
                {

                    vector<string> coord = textManager::split(pattern[i],",");

                    patternPlayer.push_back(sf::Vector2i(stoi(coord[0]),stoi(coord[1])));
                }
                cout << pseudo<< " " <<x << " " <<y << " " <<vie << " " <<argent <<" " <<x2 << " " <<y2 << " " <<file << " " <<ID << " " <<bot << endl;
                m_playerList.push_back(new Player(mapManager,pseudo,sf::Vector2i(x,y),vie,argent,m_mapManager->getTileMapList()[x2][y2],file,ID,bot,patternPlayer));
                m_playerListMap[ID] = m_playerList.back();
            }
        }
        mapFile.close();
        //m_textManager.openNewTextByID(10);
    }
}




GameManager::~GameManager()
{
    for(int i=0; i<m_playerList.size(); i++)
    {
        delete m_playerList[i];
        m_playerList[i] = 0;
    }
    delete m_inputManager;
    m_inputManager = 0;
    delete m_textManager;
    m_textManager = 0;
}

Player* GameManager::getPlayer()
{
    return m_player;
}
sf::View* GameManager::getView()
{
    return &m_PlayerView;
}
Map* GameManager::getMapManager()
{
    return m_mapManager;
}
std::vector<Player*> GameManager::getPlayerList()
{
    return m_playerList;
}

void GameManager::viewMessageBox(std::string message){

m_rectangleShape.clear();
m_textToDraw.clear();
int x = m_PlayerView.getSize().x;
int y = m_PlayerView.getSize().y;

 int y1 = y - (y/7) - y/100;
 int x1 = x/100;
 int y2 = y - y/100;
 int x2 = x - x/100;
 std::cout << x << " " << y << std::endl;
 std::cout << x1 << " " << y1 << std::endl;
 std::cout << x2 << " " << y2 << std::endl;
 int relativex = m_player->getPosition().x-(x/2)+x1;
 int relativey = m_player->getPosition().y-(y/2)+y1;
 std::cout << relativex << " " << relativey << std::endl;

sf::Font font = m_textManager->getPreloadedFont("8bit");
sf::Text text = m_textManager->createText("8bit",18,sf::Color::Black,message);

text.setPosition(relativex,relativey);
m_textToDraw.push_back(text);

sf::RectangleShape rectangle(sf::Vector2f(x2-x1, y2-y1));
rectangle.setPosition(relativex,relativey);
rectangle.setFillColor(sf::Color::White);
m_rectangleShape.push_back(rectangle);

}

void GameManager::update(sf::Time t)
{
    m_inputManager->keyboardManager(*m_player,*m_mapManager);
    m_player->update(t.asSeconds());
    m_PlayerView.setCenter(m_player->getPosition());
}

void GameManager::drawOverLay()
{
    for(int i =0;i<m_rectangleShape.size();i++){
       m_window->draw(m_rectangleShape[i]);
    }
    for(int i =0;i<m_textToDraw.size();i++){

       m_window->draw(m_textToDraw[i]);//erreur

    }

}






