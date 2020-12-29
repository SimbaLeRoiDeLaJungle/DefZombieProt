#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <SFML/Graphics.hpp>

class LoadingScreen : public sf::Drawable
{
    public:
        LoadingScreen(int width, int height,sf::Font const& font);
        void update();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::VertexArray m_vertices;
        sf::Text m_text;
        const sf::Font* m_font;
        std::string m_point;
        sf::Clock m_clock;
};

#endif // LOADINGSCREEN_H
