#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class Component_Animation
{
private:
    class Animation
    {
    private:
        // Variables
        sf::Sprite &sprite;
        sf::Texture &textureSheet;
        float animationTimer;
        float timer;
        bool done;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;

    public:
        // Constructors / Destructors
        Animation(sf::Sprite &l_sprite, sf::Texture &l_textureSheet, float l_animationTimer,
                  int startFrame_x, int startFrame_y, int frames_x, int frames_y, int l_width, int l_height)
            : sprite(l_sprite)
            , textureSheet(l_textureSheet)
            , animationTimer(l_animationTimer)
            , timer(0.f)
            , done(false)
            , width(l_width)
            , height(l_height)
        {
            timer = 0.f;
            startRect = sf::IntRect(startFrame_x * width, startFrame_y * height, width, height);
            currentRect = startRect;
            endRect = sf::IntRect((startFrame_x + frames_x) * width, (startFrame_y + frames_y) * height, width, height);

            sprite.setTexture(textureSheet, true);
            sprite.setTextureRect(startRect);
        }

        // Accessors
        const bool &isDone() const
        {
            return done;
        }

        // Functions
        const bool &play(const float &dt)
        {
            done = false;

            timer += 100.f * dt; // Animation timer
            if (timer >= animationTimer) {
                timer = 0.f; // Resetting timer

                // Animate
                if (currentRect != endRect) {
                    currentRect.left += width;
                }
                // Reset
                else {
                    currentRect.left = startRect.left;
                    done = true;
                }

                sprite.setTextureRect(currentRect);
            }

            return done;
        }

        const bool &play(const float &dt, float modPercent)
        {
            done = false;

            if (modPercent < 0.5f) {
                modPercent = 0.5f;
            }
            timer += modPercent * 100.f * dt; // Animation timer
            if (timer >= animationTimer) {
                timer = 0.f; // Resetting timer

                // Animate
                if (currentRect != endRect) {
                    currentRect.left += width;
                }
                // Reset
                else {
                    currentRect.left = startRect.left;
                    done = true;
                }

                sprite.setTextureRect(currentRect);
            }

            return done;
        }

        void reset()
        {
            timer = animationTimer;
            currentRect = startRect;
        }

    };

    sf::Sprite &sprite;
    sf::Texture &textureSheet;
    std::map<std::string, Animation*> animations;
    Animation* lastAnimation;
    Animation* priorityAnimation;

public:
    Component_Animation(sf::Sprite &l_sprite, sf::Texture &l_textureSheet);
    virtual ~Component_Animation();

    // Accessors
    const bool &isDone(const std::string key);

    // Functions
    void addAnimation(const std::string key, float l_animationTimer,
                      int startFrame_x, int startFrame_y, int frames_x, int frames_y, int l_width, int l_height);

    const bool &play(const std::string key, const float &dt, const bool priority = false);
    const bool &play(const std::string key, const float &dt, const float &modifier, const float &modifierMax, const bool priority = false);
};
