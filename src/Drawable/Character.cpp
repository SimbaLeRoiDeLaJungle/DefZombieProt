#include "Character.h"

Character::Character(int line, int col, int squareSize, float velocity) : sdaa::Entity(line,col,squareSize,velocity), m_vertices(sf::Quads,4)
{
    m_vertices[0].position = sf::Vector2f(col*squareSize,line*squareSize);
    m_vertices[1].position = sf::Vector2f((col+1)*squareSize,line*squareSize);
    m_vertices[2].position = sf::Vector2f((col+1)*squareSize,(line+1)*squareSize);
    m_vertices[3].position = sf::Vector2f(col*squareSize,(line+1)*squareSize);

    setTextureRect(0,0);
    m_texture = nullptr;
    m_dir = Character::DOWN;
}

void Character::subUpdate()
{
    updateEntityPosition();
    sdaa::VectFloat pos = getFullPosition();
    int s = getSquareSize();
    int padding = 5;
    m_vertices[0].position = sf::Vector2f(pos.x-5,pos.y-5);
    m_vertices[1].position = sf::Vector2f(pos.x +s+5,pos.y-5);
    m_vertices[2].position = sf::Vector2f(pos.x+s+5,pos.y +s+5);
    m_vertices[3].position = sf::Vector2f(pos.x -5, pos.y+s+5);

    if(getPathSize()>0)
    {
        sdaa::VectInt dest = getPath(0);
        sdaa::VectInt pos = getPositionInMetric();
        if(dest.line-pos.line >0)
        {
            m_dir = Character::DOWN;
        }
        else if(dest.line-pos.line<0)
        {
            m_dir = Character::UP;
        }
        else if(dest.col - pos.col<0)
        {
            m_dir =  Character::RIGHT;
        }
        else
        {
            m_dir = Character::LEFT;
        }
    }
}

void Character::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    if(m_texture)
        states.texture = m_texture;
    target.draw(m_vertices,states);
}

void Character::setTexture(const sf::Texture& texture)
{
    m_texture = &texture;
}

void Character::setTextureRect(int posX, int posY,bool turn)
{
    int s = 32;
    if(!turn)
    {
        m_vertices[0].texCoords = sf::Vector2f(posX*s,posY*s);
        m_vertices[1].texCoords = sf::Vector2f((posX+1)*s,posY*s);
        m_vertices[2].texCoords = sf::Vector2f((posX+1)*s,(posY+1)*s);
        m_vertices[3].texCoords = sf::Vector2f(posX*s,(posY+1)*s);
    }
    else
    {
        m_vertices[0].texCoords = sf::Vector2f((posX+1)*s,posY*s);
        m_vertices[1].texCoords = sf::Vector2f(posX*s,posY*s);
        m_vertices[2].texCoords = sf::Vector2f(posX*s,(posY+1)*s);
        m_vertices[3].texCoords = sf::Vector2f((posX+1)*s,(posY+1)*s);
    }
}
