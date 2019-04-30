#include "pausemenu.h"

// Constructors / Destructors

PauseMenu::PauseMenu(sf::VideoMode &vm, sf::Font &l_font)
    : font(l_font)
{
    background.setSize(sf::Vector2f(
                           static_cast<float>(vm.width),
                           static_cast<float>(vm.height)
                           ));
    background.setFillColor(sf::Color(20, 20, 20, 100));

    container.setSize(sf::Vector2f(vm.width / 4.f, vm.height - gui::pTpY(9.3f, vm)));
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(vm.width / 2.f - container.getSize().x / 2.f, 50.f);

    menuText.setFont(font);
    menuText.setFillColor(sf::Color(255, 255, 255, 200));
    menuText.setCharacterSize(gui::calcCharSize(vm));
    menuText.setString("PAUSED");
    menuText.setPosition(
                container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f,
                container.getPosition().y + gui::pTpY(4.f, vm)
                );
}

PauseMenu::~PauseMenu()
{
    for (auto itr = buttons.begin(); itr != buttons.end(); ++itr) {
        delete itr->second;
    }
}

std::map<std::string, gui::Button *> &PauseMenu::getButtons()
{
    return buttons;
}

// Functions

bool PauseMenu::isButtonPressed(const std::string key)
{
    return buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string &key, float y, float width, float height, unsigned charSize, const std::string &text)
{
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
    buttons[key] = new gui::Button(
                x, y, width, height, &font, text, charSize,
                sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
                );
}

void PauseMenu::update(const sf::Vector2i &mousePosWindow)
{
    for (auto &itr : buttons) {
        itr.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);

    for (auto &itr : buttons) {
        itr.second->render(target);
    }

    target.draw(menuText);
}
