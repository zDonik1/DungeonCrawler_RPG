#include "state_mainmenu.h"

// Initializer functions

void State_MainMenu::initVariables()
{

}

void State_MainMenu::initFonts()
{
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::STATE_MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
}

void State_MainMenu::initKeyBinds()
{
    std::ifstream ifs("Config/state_mainmenu_keybinds.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void State_MainMenu::initGui()
{
    const sf::VideoMode& vm = stateData->gfxSettings->resolution;

    // Background
    background.setSize(sf::Vector2f(
                           static_cast<float>(vm.width),
                           static_cast<float>(vm.height)
                           ));

    if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png")) {
        std::cout << "ERROR::STATE_MAINMENU::FAILED TO LOAD BACKGROUND TEXTURE" << std::endl;
    }
    background.setTexture(&backgroundTexture);

    // Button background
    buttonBackground.setSize(sf::Vector2f(
                                 static_cast<float>(vm.width / 5),
                                 static_cast<float>(vm.height)
                                 ));
    buttonBackground.setPosition(gui::pTpX(11.5f, vm), 0.f);
    buttonBackground.setFillColor(sf::Color(10, 10, 10, 220));

    // Buttons
    buttons["STATE_GAME"] = new gui::Button(
                gui::pTpX(50.f, vm) - gui::pTpX(13.f, vm) / 2, gui::pTpY(40.f, vm),
                gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), &font, "New Game", gui::calcCharSize(vm),
                sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
                );
    buttons["STATE_SETTINGS"] = new gui::Button(
                gui::pTpX(50.f, vm) - gui::pTpX(13.f, vm) / 2, gui::pTpY(50.f, vm),
                gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), &font, "Settings", gui::calcCharSize(vm),
                sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
                );
    buttons["STATE_EDITOR"] = new gui::Button(
                gui::pTpX(50.f, vm) - gui::pTpX(13.f, vm) / 2, gui::pTpY(60.f, vm),
                gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), &font, "Editor", gui::calcCharSize(vm),
                sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
                );
    buttons["STATE_EXIT"] = new gui::Button(
                gui::pTpX(50.f, vm) - gui::pTpX(13.f, vm) / 2, gui::pTpY(70.f, vm),
                gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), &font, "Quit", gui::calcCharSize(vm),
                sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
                );
}

void State_MainMenu::resetGui()
{
    for (auto itr = buttons.begin(); itr != buttons.end(); ++itr) {
        delete itr->second;
    }
    buttons.clear();

    initGui();
}

// Constructor / Destructor

State_MainMenu::State_MainMenu(StateData *stateData)
    : State(stateData)
{
    initVariables();
    initFonts();
    initKeyBinds();
    initGui();
}

State_MainMenu::~State_MainMenu()
{
    for (auto itr = buttons.begin(); itr != buttons.end(); ++itr) {
        delete itr->second;
    }
}

// Functions

void State_MainMenu::updateInput(const float &dt)
{

}

void State_MainMenu::updateButtons()
{
    for (auto &itr : buttons) {
        itr.second->update(mousePosWindow);
    }

    if (buttons["STATE_GAME"]->isPressed()) {
        states->push(new State_Game(stateData));
    }

    if (buttons["STATE_SETTINGS"]->isPressed()) {
        states->push(new State_Settings(stateData));
    }

    if (buttons["STATE_EDITOR"]->isPressed()) {
        states->push(new State_Editor(stateData));
    }

    if (buttons["STATE_EXIT"]->isPressed()) {
        endState();
    }
}

void State_MainMenu::update(const float &dt)
{
    updateMousePositions();
    updateInput(dt);

    updateButtons();
}

void State_MainMenu::renderButtons(sf::RenderTarget &target)
{
    for (auto &itr : buttons) {
        itr.second->render(target);
    }
}

void State_MainMenu::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    target->draw(background);

    renderButtons(*target);

    // REMOVE LATER
//    sf::Text mouseText;
//    mouseText.setPosition(mousePosView);
//    mouseText.setFont(font);
//    mouseText.setCharacterSize(12);
//    std::stringstream ss;
//    ss << mousePosView.x << " " << mousePosView.y;
//    mouseText.setString(ss.str());

//    target->draw(mouseText);
}
