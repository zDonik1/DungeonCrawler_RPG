#pragma once

#include <math.h>

class Component_Attribute
{
public:
    // Leveling
    int level;
    int exp;
    int expNext;
    int attributePoints;

    // Attributes
    int vitality;
    int strength;
    int dexterity;
    int agility;
    int intelligence;

    // Stats
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;
    int accuracy;
    int defence;
    int luck;

    // Constructor / Destructor
    Component_Attribute(int l_level);
    virtual ~Component_Attribute();

    // Functions
    void gainExp(const int l_exp);

    void updateStats(bool reset);
    void updateLevel();

    void update();
};
