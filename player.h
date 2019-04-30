#pragma once

#include "entity.h"

class Entity;

class Player : public Entity
{
private:
    // Variables
    bool attacking;

    // Initialization
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture &textureSheet);
    virtual ~Player();

    // Accessors
    Component_Attribute *getAttributeComponent();

    // Functions
    void loseHP(int hp);
    void gainHP(int hp);
    void loseEXP(int exp);
    void gainEXP(int exp);
    void updateAttack();
    void updateAnimation(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, bool showHitBox = false);
};
