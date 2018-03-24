#include "textManager.h"

textManager::textManager(){
    m_preLoadedFont["basic"] = loadFont("File/EnchantedLand.otf");
    m_basic = loadFont("File/arial.ttf");
}
textManager::~textManager(){
}

sf::Font textManager::loadFont(std::string fontFile){
 sf::Font font;
 if (!font.loadFromFile(fontFile))
 {
    std::cout << "erreur lors du chargement de "<< fontFile << std::endl;
 }else{
    std::cout << "succes lors du chargement de "<< fontFile << std::endl;
 return font;
 }
}

sf::Text textManager::createText(sf::Font font,int charsize,sf::Color color,std::string textToWrite){
sf::Text text;
text.setFont(m_basic);
text.setString(textToWrite);
text.setCharacterSize(charsize);
text.setFillColor(color);
return text;
}


