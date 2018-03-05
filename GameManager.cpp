#include "GameManager.h"

using namespace std;

vector<string> split(string phrase, string delimiter)
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
}

GameManager::GameManager(Player* p,Map* mapManager) : m_mapManager(0), m_player(0)
{

    m_mapManager = mapManager;
    m_player = p;
    m_PlayerView = sf::View(sf::FloatRect(0,0,256,192));

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
                vector<string> list = split(line,";");
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
                vector<string> pattern = split(list[10],"/");
                for(int i =0; i<pattern.size(); i++)
                {

                    vector<string> coord = split(pattern[i],",");

                    patternPlayer.push_back(sf::Vector2i(stoi(coord[0]),stoi(coord[1])));
                }
                cout << pseudo<< " " <<x << " " <<y << " " <<vie << " " <<argent <<" " <<x2 << " " <<y2 << " " <<file << " " <<ID << " " <<bot << endl;
                m_playerList.push_back(new Player(mapManager,pseudo,sf::Vector2i(x,y),vie,argent,m_mapManager->getTileMapList()[x2][y2],file,ID,bot,patternPlayer));
            }
        }
        mapFile.close();
    }
}



GameManager::~GameManager()
{
    for(int i=0; i<m_playerList.size(); i++)
    {
        delete m_playerList[i];
        m_playerList[i] = 0;
    }
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

void GameManager::update(sf::Time t)
{

    keyboardManager(*m_player,*m_mapManager);
    m_player->update(t.asSeconds());
    m_PlayerView.setCenter(m_player->getPosition());

}
