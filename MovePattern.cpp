#include "MovePattern.h"


MovePattern::MovePattern(std::vector<sf::Vector2i> pattern) : m_currentIndex(0)
{
    m_pattern = pattern;
}
MovePattern::~MovePattern()
{
}

sf::Vector2i MovePattern::getNextCase()
{
    sf::Vector2i nextDir = m_pattern[m_currentIndex];
    return nextDir;
}
void MovePattern::setPattern(std::vector<sf::Vector2i> newPattern){
    m_pattern = newPattern;
}
void MovePattern::add()
{
m_currentIndex++;
    if(m_currentIndex==m_pattern.size())
        m_currentIndex = 0;
}
