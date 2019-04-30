#pragma once

#include "component_movement.h"
#include "component_animation.h"
#include "component_hitbox.h"
#include "component_attribute.h"

class Component_Movement;
class Component_Hitbox;
class Component_Animation;
class Component_Attribute;

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    Component_Movement *movementComponent;
    Component_Animation *animationComponent;
    Component_Hitbox *hitboxComponent;
    Component_Attribute *attributeComponent;

public:
    Entity();
    virtual ~Entity();

    // Component functions
    void setTexture(sf::Texture &l_texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture &textureSheet);
    void createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height);
    void createAttributeComponent(int level);

    // Accessors
    virtual const sf::Vector2f &getPosition() const;
    virtual sf::Vector2f getCenter() const;
    virtual sf::Vector2i getGridPosition(int gridSizeI) const;
    virtual sf::FloatRect getGlobalBounds() const;
    virtual sf::FloatRect getNextPositionBounds(const float &dt) const;

    // Modifiers
    virtual void setPosition(const float x, const float y);

    // Functions
    virtual void move(const float dir_x, const float dir_y, const float &dt);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget &target, sf::Shader *shader, bool showHitBox) = 0;
};
