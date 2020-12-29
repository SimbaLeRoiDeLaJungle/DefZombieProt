#include "TileMap.h"
#include <ctime>
#include <stdlib.h>

TileMap::TileMap(int tileSize,int width, int height) : sf::Drawable(),m_render(sf::Quads,4)
{
    m_tileSize = tileSize;
    m_back.create(width,height);
}


void TileMap::load(sf::Texture const& texture)
{
    int width = m_back.getSize().x;
    int height = m_back.getSize().y;
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    m_render[0].position = sf::Vector2f(0,0);
    m_render[0].texCoords = sf::Vector2f(0,0);
    m_render[1].position = sf::Vector2f(width,0);
    m_render[1].texCoords = sf::Vector2f(width,0);
    m_render[2].position = sf::Vector2f(width,height);
    m_render[2].texCoords = sf::Vector2f(width,height);
    m_render[3].position = sf::Vector2f(0,height);
    m_render[3].texCoords = sf::Vector2f(0,height);
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    srand(time(nullptr));

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////On prepare le dessin de la map ////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    sf::VertexArray vertices(sf::Quads, width*height*4);

    for(int line = 0;line<width; line++)
    {
        for(int col = 0; col < height; col++)
        {
            int tileNumber = rand()%12;
            if(tileNumber>3)
                tileNumber = 3;
            sf::Vertex* quad = &vertices[(line+col*width)*4];
            quad[0].position = sf::Vector2f(col*m_tileSize,line*m_tileSize);
            quad[1].position = sf::Vector2f((col+1)*m_tileSize,line*m_tileSize);
            quad[2].position = sf::Vector2f((col+1)*m_tileSize,(line+1)*m_tileSize);
            quad[3].position = sf::Vector2f(col*m_tileSize,(line+1)*m_tileSize);

            quad[0].texCoords = sf::Vector2f(tileNumber*m_tileSize,0);
            quad[1].texCoords = sf::Vector2f((tileNumber+1)*m_tileSize,0);
            quad[2].texCoords = sf::Vector2f((tileNumber+1)*m_tileSize,m_tileSize);
            quad[3].texCoords = sf::Vector2f(tileNumber*m_tileSize,m_tileSize);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////On applique le dessin sur notre texture m_back/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    sf::RenderStates states= sf::RenderStates::Default;
    m_back.clear();
    states.texture = &texture;
    m_back.draw(vertices,states);
    m_back.display();
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &m_back.getTexture();
    target.draw(m_render,states);

}
