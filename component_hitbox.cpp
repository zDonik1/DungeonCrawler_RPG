#include "component_hitbox.h"

// Constructor / Destructor

Component_Hitbox::Component_Hitbox(sf::Sprite &l_sprite, float l_offsetX, float l_offsetY, float width, float height)
    : sprite(l_sprite)
    , offsetX(l_offsetX)
    , offsetY(l_offsetY)
{
    nextPosition.left = 0.f;
    nextPosition.top = 0.f;
    nextPosition.width = width;
    nextPosition.height = height;

    hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
    hitbox.setSize(sf::Vector2f(width, height));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(-1.f);
    hitbox.setOutlineColor(sf::Color::Green);
}

Component_Hitbox::~Component_Hitbox()
{

}

// Accessors

const sf::Vector2f &Component_Hitbox::getPosition() const
{
    return hitbox.getPosition();
}

sf::FloatRect Component_Hitbox::getGlobalBounds() const
{
    return hitbox.getGlobalBounds();
}

const sf::FloatRect &Component_Hitbox::getNextPosition(const sf::Vector2f &velocity)
{
    nextPosition.left = hitbox.getPosition().x + velocity.x;
    nextPosition.top = hitbox.getPosition().y + velocity.y;

    return nextPosition;
}

// Modifiers

void Component_Hitbox::setPosition(const sf::Vector2f &position)
{
    hitbox.setPosition(position);
    sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void Component_Hitbox::setPosition(float x, float y)
{
    hitbox.setPosition(x, y);
    sprite.setPosition(x - offsetX, y - offsetY);
}

// Functions

bool Component_Hitbox::intersects(const sf::FloatRect &rect)
{
    if (hitbox.getGlobalBounds().intersects(rect)) {
        return true;
    }

    return false;
}

void Component_Hitbox::update()
{
    hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void Component_Hitbox::render(sf::RenderTarget &target)
{
    target.draw(hitbox);
}
