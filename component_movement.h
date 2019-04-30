#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "movementstate.h"

class Component_Movement
{
private:
    sf::Sprite &sprite;

    float maxVelocity;

    float acceleration;
    float deceleration;
    sf::Vector2f velocity;

    // Initialization


public:
    Component_Movement(sf::Sprite &l_sprite, float l_maxVelocity, float l_acceleration, float l_deceleration);
    virtual ~Component_Movement();

    // Accessors
    const sf::Vector2f &getVelocity() const;
    const float &getMaxVelocity() const;

    // Functions
    bool getState(MovementState state) const;
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();

    void move(const float dir_x, const float dir_y, const float &dt);
    void update(const float &dt);
};

