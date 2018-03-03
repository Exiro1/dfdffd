#ifndef PLAYERSPRITE_H_INCLUDED
#define PLAYERSPRITE_H_INCLUDED

#include <SFML/Graphics.hpp>

class PlayerSprite : public sf::Drawable, public sf::Transformable
{

public :

    bool load(std::string file);

private :

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    sf::Texture m_texture;
    sf::VertexArray m_vArray;

};


#endif // PLAYERSPRITE_H_INCLUDED
