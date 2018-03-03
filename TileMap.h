#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string.h>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{

public :

    bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;


};



#endif // TILEMAP_H_INCLUDED
