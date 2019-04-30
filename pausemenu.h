#pragma once

#include <SFML/Graphics.hpp>
#include "gui.h"

class PauseMenu
{
private:
    sf::Font &font;
    sf::Text menuText;
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;

public:
    // Constructors / Destructors
    PauseMenu(sf::VideoMode &vm, sf::Font &l_font);
    virtual ~PauseMenu();

    // Accessors
    std::map<std::string, gui::Button*> &getButtons();

    // Functions
    bool isButtonPressed(const std::string key);
    void addButton(const std::string &key, float l_y, float width, float height, unsigned charSize, const std::string &text);
    void update(const sf::Vector2i &mousePosWindow);
    void render(sf::RenderTarget &target);
};
