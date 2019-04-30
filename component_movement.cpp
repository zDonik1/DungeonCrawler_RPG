#include "component_movement.h"

// Constructors / Destructors

Component_Movement::Component_Movement(sf::Sprite &l_sprite, float l_maxVelocity, float l_acceleration, float l_deceleration)
    : sprite(l_sprite)
    , maxVelocity(l_maxVelocity)
    , acceleration(l_acceleration)
    , deceleration(l_deceleration)
{
    maxVelocity = l_maxVelocity;
}

Component_Movement::~Component_Movement()
{

}

// Accessors

const sf::Vector2f &Component_Movement::getVelocity() const
{
    return velocity;
}

const float &Component_Movement::getMaxVelocity() const
{
    return maxVelocity;
}

// Functions

bool Component_Movement::getState(MovementState state) const
{
    switch (state) {
    case MovementState::IDLE:
        if (velocity.x == 0.f && velocity.y == 0.f) {
            return true;
        }

        break;

    case MovementState::MOVING:
        if (velocity.x != 0.f && velocity.y != 0.f) {
            return true;
        }

        break;

    case MovementState::MOVING_LEFT:
        if (velocity.x < 0.f) {
            return true;
        }

        break;

    case MovementState::MOVING_RIGHT:
        if (velocity.x > 0.f) {
            return true;
        }

        break;

    case MovementState::MOVING_UP:
        if (velocity.y < 0.f) {
            return true;
        }

        break;

    case MovementState::MOVING_DOWN:
        if (velocity.y > 0.f) {
            return true;
        }

        break;
    }

    return false;
}

void Component_Movement::stopVelocity()
{
    velocity.x = 0;
    velocity.y = 0;
}

void Component_Movement::stopVelocityX()
{
    velocity.x = 0;
}

void Component_Movement::stopVelocityY()
{
    velocity.y = 0;
}

void Component_Movement::move(const float dir_x, const float dir_y, const float &dt)
{
    velocity.x += acceleration * dir_x * dt;
    velocity.y += acceleration * dir_y * dt;
}

void Component_Movement::update(const float &dt)
{
    if (velocity.x > 0.f) { // Check for positive x
        // Max velocity check
        if (velocity.x > maxVelocity) {
            velocity.x = maxVelocity;
        }

        // Deceleration
        velocity.x -= deceleration * dt;
        if (velocity.x < 0.f) {
            velocity.x = 0;
        }
    }
    else if (velocity.x < 0.f) { // Check for negative x
        // Max velocity check
        if (velocity.x < -maxVelocity) {
            velocity.x = -maxVelocity;
        }

        // Deceleration
        velocity.x += deceleration * dt;
        if (velocity.x > 0.f) {
            velocity.x = 0;
        }
    }

    if (velocity.y > 0.f) { // Check for positive y
        // Max velocity check x positive
        if (velocity.y > maxVelocity) {
            velocity.y = maxVelocity;
        }

        // Deceleration x positive
        velocity.y -= deceleration * dt;
        if (velocity.y < 0.f) {
            velocity.y = 0;
        }
    }
    else if (velocity.y < 0.f) { // Check for negative y
        // Max velocity check x negative
        if (velocity.y < -maxVelocity) {
            velocity.y = -maxVelocity;
        }

        // Deceleration x negative
        velocity.y += deceleration * dt;
        if (velocity.y > 0.f) {
            velocity.y = 0;
        }
    }

    sprite.move(velocity * dt);
}
