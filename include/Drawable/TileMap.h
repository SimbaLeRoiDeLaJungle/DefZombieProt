#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable
{
    public:
        TileMap(int tileSize, int width, int height);
        void load(sf::Texture const& texture);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        int m_tileSize;
        sf::RenderTexture m_back;
        sf::VertexArray m_render;

};

#endif // TILEMAP_H
