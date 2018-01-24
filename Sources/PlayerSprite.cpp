#include "PlayerSprite.h"



void PlayerSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_texture;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vArray, states);
}

bool PlayerSprite::load(std::string file)
{
    if(m_texture.loadFromFile(file))
    {
        m_vArray.setPrimitiveType(sf::Quads);
        m_vArray.resize(4);
        sf::Vertex* quad = &m_vArray[0];

        quad[0].position = sf::Vector2f(0,0);
        quad[1].position = sf::Vector2f(32,0);
        quad[2].position = sf::Vector2f(32,32);
        quad[3].position = sf::Vector2f(0,32);

        // on définit ses quatre coordonnées de texture
        quad[0].texCoords = sf::Vector2f(0, 0);
        quad[1].texCoords = sf::Vector2f(32,0);
        quad[2].texCoords = sf::Vector2f(32, 32);
        quad[3].texCoords = sf::Vector2f(0,32);


        return true;
    }

    return false;
}


