#include "component_attribute.h"

// Constructor / Destructor

Component_Attribute::Component_Attribute(int l_level)
{
    level = l_level;
    exp = 0;
    expNext = static_cast<int>((50 / 3) * (pow(level + 1, 3) - 6 * pow(level, 2) +  ((level + 1) * 17) - 12));
    attributePoints = 2;

    vitality = 1;
    strength = 1;
    dexterity = 1;
    agility = 1;
    intelligence = 1;

    updateLevel();
    updateStats(true);
}

Component_Attribute::~Component_Attribute()
{

}

// Functions

void Component_Attribute::gainExp(const int l_exp)
{
    exp += l_exp;

    updateLevel();
}

void Component_Attribute::updateStats(bool reset)
{
    hpMax = vitality * 6 + strength / 2 + intelligence / 5;
    damageMin = strength * 2 + strength / 4 + intelligence / 5;
    damageMax = strength * 2 + strength / 2 + intelligence / 5;
    accuracy = dexterity * 5 + dexterity / 2 + intelligence / 5;
    defence = agility * 2 + agility / 4 + intelligence / 5;
    luck = intelligence * 2 + intelligence / 5;

    if (reset) {
        hp = hpMax;
    }
}

void Component_Attribute::updateLevel()
{
    while (exp >= expNext) {
        ++level;
        exp -= expNext;
        expNext = static_cast<int>((50 / 3) * (pow(level, 3) - 6 * pow(level, 2) + (level * 17) - 12));
        ++attributePoints;
    }
}

void Component_Attribute::update()
{
    updateLevel();
    updateStats(true);
}
