#pragma once

#include "player.h"
#include "gui.h"

class Player;

class PlayerGUI
{
private:
    Player *player;

    sf::VideoMode &vm;
    sf::Font font;

    // Level Bar
    std::string levelBarString;
    sf::Text levelBarText;
    sf::RectangleShape levelBarBack;

    // EXP bar
    std::string expBarString;
    sf::Text expBarText;
    float expBarMaxWidth;
    sf::RectangleShape expBarBack;
    sf::RectangleShape expBarInner;

    // HP bar
    std::string hpBarString;
    sf::Text hpBarText;
    float hpBarMaxWidth;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;

    // Initializer
    void initFont();
    void initLevelBar();
    void initEXPBar();
    void initHpBar();

public:
    // Constructor / Destructor
    PlayerGUI(Player* l_player, sf::VideoMode &l_vm);
    virtual ~PlayerGUI();

    // Functions
    void updateLevelBar();
    void updateEXPBar();
    void updateHpBar();
    void update(const float &dt);
    void renderLevelBar(sf::RenderTarget &target);
    void renderEXPBar(sf::RenderTarget &target);
    void renderHpBar(sf::RenderTarget &target);
    void render(sf::RenderTarget & target);
};
