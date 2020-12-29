#include "GameRender.h"

GameRender::GameRender(int width, int height) : m_vertices(sf::Quads, 4)
{
    m_vertices[0].position = sf::Vector2f(0,0);
    m_vertices[1].position = sf::Vector2f(width,0);
    m_vertices[2].position = sf::Vector2f(width,height);
    m_vertices[3].position = sf::Vector2f(0,height);

    m_vertices[0].texCoords = sf::Vector2f(0,0);
    m_vertices[1].texCoords = sf::Vector2f(width,0);
    m_vertices[2].texCoords = sf::Vector2f(width,height);
    m_vertices[3].texCoords = sf::Vector2f(0,height);
}

void GameRender::setTexture(const sf::Texture& texture)
{
    m_texture = &texture;
}

void GameRender::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    states.texture = m_texture;
    target.draw(m_vertices,states);
}
