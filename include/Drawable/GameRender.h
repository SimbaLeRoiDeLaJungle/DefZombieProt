#ifndef GAMERENDER_H
#define GAMERENDER_H

#include <SFML/Graphics.hpp>

class GameRender: public sf::Drawable
{
    public:
        GameRender(int width, int height);
        void setTexture(const sf::Texture& texture);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::VertexArray m_vertices;
        const sf::Texture* m_texture;
};

#endif // GAMERENDER_H
