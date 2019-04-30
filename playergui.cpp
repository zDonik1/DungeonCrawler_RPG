#include "playergui.h"

// Initializer functions

void PlayerGUI::initFont()
{
    font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initLevelBar()
{
    float width = gui::pTpX(1.6f, vm);
    float height = gui::pTpY(2.8f, vm);
    float x = gui::pTpX(1.f, vm);
    float y = gui::pTpY(1.9f, vm);;

    levelBarBack.setSize(sf::Vector2f(width, height));
    levelBarBack.setFillColor(sf::Color(50, 100, 50, 200));
    levelBarBack.setPosition(x, y);

    levelBarText.setFont(font);
    levelBarText.setCharacterSize(gui::calcCharSize(vm, 150));
    levelBarText.setPosition(levelBarBack.getPosition().x + gui::pTpX(0.53f, vm),
                          levelBarBack.getPosition().y + gui::pTpY(0.5f, vm));
}

void PlayerGUI::initEXPBar()
{
    float width = gui::pTpX(10.4f, vm);
    float height = gui::pTpY(1.9f, vm);
    float x = gui::pTpX(1.f, vm);
    float y = gui::pTpY(5.6f, vm);

    expBarMaxWidth = width;

    expBarBack.setSize(sf::Vector2f(width, height));
    expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    expBarBack.setPosition(x, y);

    expBarInner.setSize(sf::Vector2f(width, height));
    expBarInner.setFillColor(sf::Color(20, 20, 250, 200));
    expBarInner.setPosition(expBarBack.getPosition());

    expBarText.setFont(font);
    expBarText.setCharacterSize(gui::calcCharSize(vm, 200));
    expBarText.setPosition(expBarInner.getPosition().x + gui::pTpX(0.53f, vm),
                          expBarInner.getPosition().y + gui::pTpY(0.15f, vm));
}

void PlayerGUI::initHpBar()
{
    float width = gui::pTpX(10.4f, vm);
    float height = gui::pTpY(2.8f, vm);
    float x = gui::pTpX(1.f, vm);
    float y = gui::pTpY(8.3f, vm);

    hpBarMaxWidth = width;

    hpBarBack.setSize(sf::Vector2f(width, height));
    hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
    hpBarBack.setPosition(x, y);

    hpBarInner.setSize(sf::Vector2f(width, height));
    hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
    hpBarInner.setPosition(hpBarBack.getPosition());

    hpBarText.setFont(font);
    hpBarText.setCharacterSize(gui::calcCharSize(vm, 120));
    hpBarText.setPosition(hpBarInner.getPosition().x + gui::pTpX(0.53f, vm),
                          hpBarInner.getPosition().y + gui::pTpY(0.15f, vm));
}

// Constructor / Destructor

PlayerGUI::PlayerGUI(Player* l_player, sf::VideoMode &l_vm)
    : vm(l_vm)
{
    player = l_player;

    initFont();
    initLevelBar();
    initEXPBar();
    initHpBar();
}

PlayerGUI::~PlayerGUI()
{

}

// Functions

void PlayerGUI::updateLevelBar()
{
    levelBarString = std::to_string(player->getAttributeComponent()->level);
    levelBarText.setString(levelBarString);
}

void PlayerGUI::updateEXPBar()
{
    float expPercent = static_cast<float>(player->getAttributeComponent()->exp) / static_cast<float>(player->getAttributeComponent()->expNext);
    expBarInner.setSize(sf::Vector2f(
                           static_cast<float>(std::floor(expBarMaxWidth * expPercent)),
                           expBarInner.getSize().y
                           ));

    expBarString = std::to_string(player->getAttributeComponent()->exp) + " / " + std::to_string(player->getAttributeComponent()->expNext);
    expBarText.setString(expBarString);
}

void PlayerGUI::updateHpBar()
{
    float hpPercent = static_cast<float>(player->getAttributeComponent()->hp) / static_cast<float>(player->getAttributeComponent()->hpMax);
    hpBarInner.setSize(sf::Vector2f(
                           static_cast<float>(std::floor(hpBarMaxWidth * hpPercent)),
                           hpBarInner.getSize().y
                           ));

    hpBarString = std::to_string(player->getAttributeComponent()->hp) + " / " + std::to_string(player->getAttributeComponent()->hpMax);
    hpBarText.setString(hpBarString);
}

void PlayerGUI::update(const float &dt)
{
    updateLevelBar();
    updateEXPBar();
    updateHpBar();
}

void PlayerGUI::renderLevelBar(sf::RenderTarget &target)
{
    target.draw(levelBarBack);
    target.draw(levelBarText);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget &target)
{
    target.draw(expBarBack);
    target.draw(expBarInner);
    target.draw(expBarText);
}

void PlayerGUI::renderHpBar(sf::RenderTarget &target)
{
    target.draw(hpBarBack);
    target.draw(hpBarInner);
    target.draw(hpBarText);
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    renderLevelBar(target);
    renderEXPBar(target);
    renderHpBar(target);
}
