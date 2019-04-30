#include "entity.h"

// Initializer functions

void Entity::initVariables()
{
    movementComponent = nullptr;
    animationComponent = nullptr;
    hitboxComponent = nullptr;
}

// Constructors / Destructors

Entity::Entity()
{
    initVariables();
}

Entity::~Entity()
{
    delete movementComponent;
    delete animationComponent;
    delete hitboxComponent;
    delete attributeComponent;
}

// Component functions

void Entity::setTexture(sf::Texture &l_texture)
{
    sprite.setTexture(l_texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    movementComponent = new Component_Movement(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &textureSheet)
{
    animationComponent = new Component_Animation(sprite, textureSheet);
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height)
{
    hitboxComponent = new Component_Hitbox(sprite, offsetX, offsetY, width, height);
}

void Entity::createAttributeComponent(int level)
{
    attributeComponent = new Component_Attribute(level);
}

// Accessors

const sf::Vector2f &Entity::getPosition() const
{
    if (hitboxComponent) {
        return hitboxComponent->getPosition();
    }

    return sprite.getPosition();
}

sf::Vector2f Entity::getCenter() const
{
    if (hitboxComponent) {
        return hitboxComponent->getPosition() + sf::Vector2f(hitboxComponent->getGlobalBounds().width / 2.f,
                                                             hitboxComponent->getGlobalBounds().height / 2.f);
    }

    return sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f,
                                               sprite.getGlobalBounds().height / 2.f);
}

sf::Vector2i Entity::getGridPosition(int gridSizeI) const
{
    if (hitboxComponent) {
        return sf::Vector2i(
                    static_cast<int>(hitboxComponent->getPosition().x) / gridSizeI,
                    static_cast<int>(hitboxComponent->getPosition().y) / gridSizeI
                    );
    }

    return sf::Vector2i(
                static_cast<int>(sprite.getPosition().x) / gridSizeI,
                static_cast<int>(sprite.getPosition().y) / gridSizeI
                );
}

sf::FloatRect Entity::getGlobalBounds() const
{
    if (hitboxComponent) {
        return hitboxComponent->getGlobalBounds();
    }
    return sprite.getGlobalBounds();
}

sf::FloatRect Entity::getNextPositionBounds(const float &dt) const
{
    if (hitboxComponent && movementComponent) {
        return hitboxComponent->getNextPosition(movementComponent->getVelocity() * dt);
    }

    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}


// Functions

void Entity::setPosition(const float x, const float y)
{
    if (hitboxComponent) {
        hitboxComponent->setPosition(x, y);
    }
    else {
        sprite.setPosition(x, y);
    }
}

void Entity::move(const float dir_x, const float dir_y, const float &dt)
{
    if (movementComponent) {
        movementComponent->move(dir_x, dir_y, dt); // sets velocity
    }
    else {
    }
}

void Entity::stopVelocity()
{
    if (movementComponent) {
        movementComponent->stopVelocity();
    }
}

void Entity::stopVelocityX()
{
    if (movementComponent) {
        movementComponent->stopVelocityX();
    }
}

void Entity::stopVelocityY()
{
    if (movementComponent) {
        movementComponent->stopVelocityY();
    }
}

void Entity::update(const float &dt)
{

}
