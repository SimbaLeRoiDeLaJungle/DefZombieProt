#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "SDAA.h"
#include "MetricShape.h"
#include <SFML/Graphics.hpp>
#include "PlayerChar.h"
#include "Zombie.h"
#include "TileMap.h"
#include "TextureHolder.h"
#include "Bullets.h"
class GameEngine
{
    public:
        GameEngine();
        void update();
        const sf::Texture& getRender() const;
        void importTexture(const TextureHolder& texture);
        void addCharacter(int line, int col);
        void addZombie(int line , int col);

        void leftButton(bool mouseRight,sf::Vector2i const& mousePos);
        void rightButton(bool mouseRight,sf::Vector2i const& mousePos);
        void loadGame();
        void updateRender();


        bool getIsReady() const;
    protected:

    private:
        sdaa::Metric m_metric;
        sdaa::MetricShape metricShape;
        std::vector<PlayerChar> m_entities;
        std::vector<Zombie> m_zombies;
        std::vector<Bullets> m_bullets;
        sf::RenderTexture m_texture;
        TileMap m_tileMap;
        int m_entitySelect;
        bool m_isReady;
        int m_zombieUpdateCount;
        // pointeur vers les textures
        const sf::Texture* m_characterTexture;
        const sf::Texture* m_tilesTexture;
        const sf::Texture* m_zombieTexture;

};

#endif // GAMEENGINE_H
