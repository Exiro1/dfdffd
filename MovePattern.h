#ifndef MOVEPATTERN_H_INCLUDED
#define MOVEPATTERN_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

class MovePattern
{

public:

    MovePattern(std::vector<sf::Vector2i> pattern);
    ~MovePattern();
    sf::Vector2i getNextCase();
    std::vector<sf::Vector2i> getPattern(){return m_pattern;};
    void setPattern(std::vector<sf::Vector2i> newPattern);
    void add();


protected:


private:

    std::vector<sf::Vector2i> m_pattern;
    int m_currentIndex;

};




#endif // MOVEPATTERN_H_INCLUDED
