#include "Bullets.h"
#include <cmath>
Bullets::Bullets(float posX, float posY, sf::Vector2f const& dest): m_vertices(sf::Quads,4)
{
    int width = 2;
    m_InitPosition = sf::Vector2f(posX,posY);
    m_vertices[0].position = sf::Vector2f(posX,posY);
    m_vertices[1].position = sf::Vector2f(posX+width,posY);
    m_vertices[2].position = sf::Vector2f(posX+width,posY+width);
    m_vertices[3].position = sf::Vector2f(posX,posY+width);
    float  deltaX = dest.x - posX;
    float  deltaY = dest.y - posY;
    float distance = sqrt(pow(deltaX,2)+pow(deltaY,2));
    if(distance!=0)
    {
        m_dir.x = deltaX/distance;
        m_dir.y = deltaY/distance;
    }
}

void Bullets::update()
{
    float velocity = 4;
    float dvx = velocity*m_dir.x;
    float dvy = velocity*m_dir.y;
    move(dvx,dvy);
}
void Bullets::move(float dx, float dy)
{
    m_vertices[0].position.x+=dx;
    m_vertices[0].position.y+=dy;
    m_vertices[1].position.x+=dx;
    m_vertices[1].position.y+=dy;
    m_vertices[2].position.x+=dx;
    m_vertices[2].position.y+=dy;
    m_vertices[3].position.x+=dx;
    m_vertices[3].position.y+=dy;
}

void Bullets::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vertices,states);
}

sf::FloatRect Bullets::getGlobalBounds() const
{
    sf::FloatRect rect;
    rect.width = 3;
    rect.height = 3;
    rect.left = m_vertices[0].position.x;
    rect.top = m_vertices[0].position.y;
}
