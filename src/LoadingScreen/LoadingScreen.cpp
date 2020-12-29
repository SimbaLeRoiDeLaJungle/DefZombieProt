#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(int width, int height,sf::Font const& font): m_vertices(sf::Quads,4)
{
    int padding = 15;
    m_vertices[0].position = sf::Vector2f(0,0);
    m_vertices[0].color = sf::Color::Black;
    m_vertices[1].position = sf::Vector2f(width,0);
    m_vertices[1].color = sf::Color::Black;
    m_vertices[2].position = sf::Vector2f(width,height);
    m_vertices[2].color = sf::Color::Black;
    m_vertices[3].position = sf::Vector2f(0,height);
    m_vertices[3].color = sf::Color::Black;
    m_font = &font;
    m_text.setFont(*m_font);
    m_text.setString("Chargement ");
    m_text.setCharacterSize(30);
    m_text.setPosition(padding, height-padding-m_text.getGlobalBounds().height);
    m_clock.restart();
}

void LoadingScreen::update()
{
    float time = m_clock.getElapsedTime().asMilliseconds();
    std::string point;
    float maxTime = 1000;
    if(time>maxTime)
        m_clock.restart();
    else if(time < maxTime/3)
        point = ".";
    else if(time<maxTime*2/3)
        point = "..";
    else
        point = "...";
    m_text.setString("Chargement " + point);
}

void LoadingScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vertices,states);
    target.draw(m_text);
}
