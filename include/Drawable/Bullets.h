#ifndef BULLETS_H
#define BULLETS_H

#include <SFML/Graphics.hpp>

class Bullets : public sf::Drawable
{
    public:
        Bullets(float posX, float posY, sf::Vector2f const& dest);
        void update();
        void move(float dx, float dy);
        sf::FloatRect getGlobalBounds() const;

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Vector2f m_dir;
        sf::Vector2f m_InitPosition;
        sf::VertexArray m_vertices;
};

#endif // BULLETS_H
