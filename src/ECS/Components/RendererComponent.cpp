#include "RendererComponent.h"

RendererComponent::RendererComponent(std::string textureName, sf::Vector2f scale, int layer)
:textureName(textureName), scale(scale), layer(layer)
{}

RendererComponent::~RendererComponent()
{}

ComponentID RendererComponent::getTypeId() const
{
    return ID;
}

std::string RendererComponent::getTextureName() const
{
    return textureName;
}

sf::Vector2f RendererComponent::getScale() const
{
    return scale;
}

sf::Sprite& RendererComponent::getSpriteRef()
{
    return sprite;
}

int RendererComponent::getLayer() const
{
    return layer;
}

bool RendererComponent::hasSpriteTextured() const
{
    return sprite.getTexture() != nullptr;
}

std::string RendererComponent::str() const
{
    std::stringstream sstr;
    sstr << ID << " (renderer) : " << textureName << " scale : (" << scale.x << ", " << scale.y << ")";
    return sstr.str();
}
