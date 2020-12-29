#include "TextureHolder.h"
/*------------------------------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////
TextureHolder::TextureHolder()
{

}
/*------------------------------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////
void TextureHolder::load(Textures::ID const& id, std::string const& filePath)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if(!texture->loadFromFile(filePath))
        throw std::runtime_error("TextureHolder::load - Failed to load " + filePath);
    insertTexture(id,std::move(texture));
}
/*------------------------------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////
sf::Texture& TextureHolder::get(Textures::ID const& id) const
{
    auto found = m_textureMap.find(id);
    assert(found != m_textureMap.end());

    return *found->second;
}
/*------------------------------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////
void TextureHolder::insertTexture(Textures::ID const& id, std::unique_ptr<sf::Texture> texture)
{
    auto inserted = m_textureMap.insert(std::make_pair(id,std::move(texture)));
    assert(inserted.second);
}
