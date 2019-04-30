#include "component_animation.h"

// Constructor / Destructor

Component_Animation::Component_Animation(sf::Sprite &l_sprite, sf::Texture &l_textureSheet)
    : sprite(l_sprite)
    , textureSheet(l_textureSheet)
    , lastAnimation(nullptr)
    , priorityAnimation(nullptr)
{

}

Component_Animation::~Component_Animation()
{
    for (auto &itr : animations) {
        delete itr.second;
    }
}

// Accessors

const bool &Component_Animation::isDone(const std::string key)
{
    return animations[key]->isDone();
}

// Functions

void Component_Animation::addAnimation(const std::string key, float l_animationTimer,
                                       int startFrame_x, int startFrame_y, int frames_x, int frames_y, int l_width, int l_height)
{
    animations[key] = new Animation(sprite, textureSheet, l_animationTimer,
                                startFrame_x, startFrame_y, frames_x, frames_y, l_width, l_height);
}


const bool &Component_Animation::play(const std::string key, const float &dt, const bool priority)
{
    if (priorityAnimation) {
        if (priorityAnimation == animations[key]) {
            if (lastAnimation != animations[key]) {
                if (lastAnimation == nullptr) {
                    lastAnimation = animations[key];
                }
                else {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            // If priority animation is done, remove it
            if (animations[key]->play(dt)) {
                priorityAnimation = nullptr;
            }
        }
    }
    else {
        if (priority) {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key]) {
            if (lastAnimation == nullptr) {
                lastAnimation = animations[key];
            }
            else {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }

        animations[key]->play(dt);
    }

    return animations[key]->isDone();
}

const bool &Component_Animation::play(const std::string key, const float &dt, const float &modifier, const float &modifierMax, const bool priority)
{
    if (priorityAnimation) {
        if (priorityAnimation == animations[key]) {
            if (lastAnimation != animations[key]) {
                if (lastAnimation == nullptr) {
                    lastAnimation = animations[key];
                }
                else {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            // If priority animation is done, remove it
            if (animations[key]->play(dt, abs(modifier / modifierMax))) {
                priorityAnimation = nullptr;
            }
        }
    }
    else {
        if (priority) {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key]) {
            if (lastAnimation == nullptr) {
                lastAnimation = animations[key];
            }
            else {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }

        animations[key]->play(dt, abs(modifier / modifierMax));
    }

    return animations[key]->isDone();
}
