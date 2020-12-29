#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <memory>
#include <assert.h>
#include<utility>
#include<stdexcept>
#include<cassert>
namespace Textures
{
    enum ID {BUTTON,TILESET,CHARACTER,ZOMBIE};
}

class TextureHolder
{
    public:
        TextureHolder();
        void load(Textures::ID const& id, std::string const& filePath);
        sf::Texture& get(Textures::ID const& id) const;

    protected:
        void insertTexture(Textures::ID const& id, std::unique_ptr<sf::Texture> texture);

    private:
        std::map<Textures::ID,std::unique_ptr<sf::Texture>> m_textureMap;
};

#endif // TEXTUREHOLDER_H
