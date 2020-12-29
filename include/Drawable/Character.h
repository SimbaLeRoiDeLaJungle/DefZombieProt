#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "SDAA.h"


class Character : public sf::Drawable , public sdaa::Entity
{
    public:
        enum Direction {LEFT,UP,RIGHT,DOWN};
        Character(int line, int col, int squareSize, float velocity);
        void subUpdate();
        void setTexture(const sf::Texture& texture);
        void setTextureRect(int posX, int posY,bool turn = false);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Direction m_dir;
    private:
        sf::VertexArray m_vertices;
        const sf::Texture* m_texture;

};

#endif // CHARACTER_H
