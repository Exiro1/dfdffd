#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

class textManager
{
public:
    textManager();
    ~textManager();
    sf::Font loadFont(std::string font);
    sf::Text createText(sf::Font font,int charSize,sf::Color,std::string text);
    sf::Font getPreloadedFont(std::string font){return m_preLoadedFont[font];}


protected:

private:

 std::unordered_map<std::string,sf::Font> m_preLoadedFont;

 sf::Font m_basic;

};






#endif // TEXTMANAGER_H_INCLUDED
