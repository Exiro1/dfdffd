#include "textManager.h"

textManager::textManager()
{
    m_preLoadedFont["basic"] = loadFont("File/EnchantedLand.otf");
    m_preLoadedFont["8bit"] = loadFont("File/8bit.ttf");
    m_basic = loadFont("File/arial.ttf");

    std::ifstream textFile("File/BotText.txt",std::ios::in);
    if(textFile)
    {
        std::string line;
        while(getline(textFile, line))
        {
            std::cout << line << std::endl;
            std::vector<std::string> list = split(line,"/");// / est le delimiteur : ID/text
            std::cout << list.size() << std::endl;
            int id = stoi(list[0]);
            std::string text= list[1];
            m_allTextMap[id] = text;
        }
        textFile.close();

    }






}
textManager::~textManager()
{
}

sf::Font textManager::loadFont(std::string fontFile)
{
    sf::Font font;
    if (!font.loadFromFile(fontFile))
    {
        std::cout << "erreur lors du chargement de "<< fontFile << std::endl;
    }
    else
    {
        std::cout << "succes lors du chargement de "<< fontFile << std::endl;
        return font;
    }
}

std::vector<std::string> textManager::split(std::string phrase, std::string delimiter)
{
    std::vector<std::string> list;
    std::string s = phrase;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return list;
}

sf::Text textManager::createText(std::string font,int charsize,sf::Color color,std::string textToWrite)
{
    sf::Text text;
    text.setFont(m_preLoadedFont[font]);
    text.setString(textToWrite);
    text.setCharacterSize(charsize);
    text.setFillColor(color);
    return text;
}
std::string textManager::getNextText(int ID,std::string pseudo)
{
    if(ID == m_ID)
    {
        m_index++;
        if(m_index < m_currentTextSplittedbySize.size())
        {
            return m_currentTextSplittedbySize[m_index];
        }
        else
        {
            m_ID = 0;
            return "EOF";
        }
    }
    else
    {
        openNewTextByID(ID,pseudo);
        return m_currentTextSplittedbySize[0];
    }
}
void textManager::reset(){
m_ID = 0;
}

void textManager::openNewTextByID(int ID,std::string pseudo)
{
    m_ID = ID;
    std::string textLoaded = m_allTextMap[ID];
    m_currentText = pseudo +": "+ textLoaded;

    m_currentTextSplitted = split(m_currentText," ");

    m_currentTextSplittedbySize.clear();
    m_currentTextSplittedbySize.push_back("");
    int index(0);
    m_index = 0;
    for(int i=0; i<m_currentTextSplitted.size(); i++)
    {

        if(m_currentTextSplittedbySize[index].size() + m_currentTextSplitted[i].size() <= 30)
        {
            m_currentTextSplittedbySize[index] += m_currentTextSplitted[i]+" ";
        }
        else
        {
            index++;
            m_currentTextSplittedbySize.push_back("");
            i--;
        }
    }
    std::cout << "text splitted "<< std::endl;
    for(int i=0; i<m_currentTextSplittedbySize.size(); i++)
    {
        std::cout << m_currentTextSplittedbySize[i] << "    " << m_currentTextSplittedbySize[i].size() << std::endl;
    }
}








