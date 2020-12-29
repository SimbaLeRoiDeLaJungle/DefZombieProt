#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(): m_metric(2000,2000,25),m_tileMap(64,2000,2000) , metricShape(m_metric)
{
    m_texture.create(2000,2000);

    m_entitySelect = -1;

    m_isReady = false;

    m_zombieUpdateCount =0;
}

void GameEngine::update()
{
    metricShape.update(m_metric);

    for(int i = 0 ; i< m_entities.size(); i++)
    {
        m_entities[i].update();
        m_entities[i].animation();
        if(m_entities[i].getState() == PlayerChar::SHOOT)
        {
            if(m_entities[i].shoot())
            {
                sdaa::VectFloat pos = m_entities[i].getFullPosition();
                sdaa::VectFloat targetPos = m_entities[i].getTargetFullPosition();
                int s = m_metric.getSquareSize();
                m_bullets.push_back(Bullets(pos.x+s/2.f,pos.y+s/2.f,sf::Vector2f(targetPos.x+s/2.f,targetPos.y+s/2.f)));
            }
        }
    }
    m_zombieUpdateCount++;
    for(int i = 0 ; i< m_zombies.size(); i++)
    {
        m_zombies[i].update();
        m_zombies[i].animation();
        int indice=-1;
        if(m_zombieUpdateCount > 100)
        {
            m_zombieUpdateCount = 0;
            for(int j = 0 ; j< m_entities.size(); j++)
            {
                float viewDistance = 10*32;
                float tempDistance=viewDistance;

                if(m_metric.distance(m_zombies[i],m_entities[j])<tempDistance)
                {
                    tempDistance = m_metric.distance(m_zombies[i],m_entities[j]);
                    indice = j;
                }

            }
            if(indice !=-1)
                m_metric.follow(m_zombies[i],m_entities[indice]);
            else
                m_zombies[i].stopToFollow();

        }
        int size = m_bullets.size();
        for(int j = 0; j< size; j++)
        {
            if(m_zombies[i].collide(m_bullets[j]))
            {
                m_bullets.erase(m_bullets.begin()+j);
                j--;
                std::cout<<"collide"<<std::endl;
            }
        }

    }

    for(int i = 0 ; i< m_bullets.size(); i++)
    {
        m_bullets[i].update();
    }

    m_metric.dynamicPathControl();
    updateRender();
}

const sf::Texture& GameEngine::getRender() const
{
    return m_texture.getTexture();
}

void GameEngine::importTexture(const TextureHolder& textures)
{
    m_characterTexture = &textures.get(Textures::CHARACTER);
    m_tilesTexture = &textures.get(Textures::TILESET);
    m_zombieTexture = &textures.get(Textures::ZOMBIE);
}

void GameEngine::addCharacter(int line , int col)
{
    m_entities.push_back(PlayerChar(line,col));
    m_entities[m_entities.size()-1].setTexture(*m_characterTexture);
    m_metric.addEntity(m_entities[m_entities.size()-1]);
}

void GameEngine::addZombie(int line , int col)
{
    m_zombies.push_back(Zombie(line,col));
    m_zombies[m_zombies.size()-1].setTexture(*m_zombieTexture);
    m_metric.addEntity(m_zombies[m_zombies.size()-1]);

}

void GameEngine::leftButton(bool mouseLeft,sf::Vector2i const& mousePos)
{
    if(mouseLeft)
    {
        ////////////////////////////////////////////////////////////////
        // select a character
        bool b=false;
        for(int i =0 ; i< m_entities.size(); i++)
        {
            sdaa::VectFloat pos = m_entities[i].getFullPosition();
            int s = m_metric.getSquareSize();
            if(mousePos.x>pos.x && mousePos.x<pos.x+s && mousePos.y > pos.y && mousePos.y < pos.y +s)
            {
                b= true;
                m_entitySelect = i;
            }
        }
        if(!b)
            m_entitySelect = -1;
        ////////////////////////////////////////////////////////////////

    }
}

void GameEngine::rightButton(bool mouseRight,sf::Vector2i const& mousePos)
{
    if(mouseRight)
    {
        ////////////////////////////////////////////////////////////////
        //attack a zombie
        bool b = false;
        if(m_entitySelect != -1)
        {
            for(int i = 0 ; i < m_zombies.size(); i++)
            {
                sdaa::VectFloat pos = m_zombies[i].getFullPosition();
                int s = m_metric.getSquareSize();
                if(mousePos.x>pos.x && mousePos.x<pos.x+s && mousePos.y > pos.y && mousePos.y < pos.y +s)
                {
                    m_metric.follow(m_entities[m_entitySelect],m_zombies[i]);
                    b=true;
                }
            }
        }
        ////////////////////////////////////////////////////////////////
        // move a character
        if(!b)
        {
            int s = m_metric.getSquareSize();
            int line = mousePos.y / s;
            int col = mousePos.x / s;
            if(m_entitySelect != -1 && m_metric.isIn(line,col))
            {
                m_metric.setPath(m_entities[m_entitySelect],sdaa::VectInt(line,col));
                m_entities[m_entitySelect].setState(PlayerChar::MOVE);
            }
        }

    }
}

// doit etre mis dans un thread a part
void GameEngine::loadGame()
{
    m_tileMap.load(*m_tilesTexture);

    m_isReady = true;
}

void GameEngine::updateRender()
{
    m_texture.clear();
    m_texture.draw(m_tileMap);
    for(int i = 0 ; i<m_entities.size(); i++)
        m_texture.draw(m_entities[i]);
    for(int i = 0; i< m_zombies.size() ; i++)
        m_texture.draw(m_zombies[i]);
    for(int i = 0 ; i < m_bullets.size() ; i++)
        m_texture.draw(m_bullets[i]);
    m_texture.draw(metricShape);
    m_texture.display();
}

bool GameEngine::getIsReady() const
{
    return m_isReady;
}
