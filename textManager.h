#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <iostream>
#include <fstream>

class textManager
{
public:
    textManager();
    ~textManager();
    sf::Font loadFont(std::string font);
    sf::Text createText(std::string font,int charSize,sf::Color,std::string text);
    sf::Font getPreloadedFont(std::string font){return m_preLoadedFont[font];}
    void openNewTextByID(int ID,std::string pseudo);
    std::string getNextText(int ID,std::string pseudo);
    static std::vector<std::string> split(std::string phrase, std::string delimiter);
    void reset();
protected:

private:

 std::unordered_map<std::string,sf::Font> m_preLoadedFont;

 sf::Font m_basic;
 std::string m_currentText;
 int m_ID;
 int m_index;
 std::vector<std::string> m_currentTextSplitted;
 std::vector<std::string> m_currentTextSplittedbySize;

 std::unordered_map<int,std::string> m_allTextMap;
};






#endif // TEXTMANAGER_H_INCLUDED
