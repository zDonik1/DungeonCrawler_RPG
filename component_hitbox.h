#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class Component_Hitbox
{
private:
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;
    float offsetX;
    float offsetY;

public:
    // Construtor / Destructor
    Component_Hitbox(sf::Sprite &l_sprite, float l_offsetX, float l_offsetY, float width, float height);
    virtual ~Component_Hitbox();

    // Accessors
    const sf::Vector2f &getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect &getNextPosition(const sf::Vector2f &velocity);

    // Modifiers
    void setPosition(const sf::Vector2f &position);
    void setPosition(float x, float y);

    // Functions
    bool intersects(const sf::FloatRect &rect);

    void update();
    void render(sf::RenderTarget &target);
};
