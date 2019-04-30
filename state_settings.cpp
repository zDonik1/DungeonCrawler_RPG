#include "state_settings.h"

// Initializer functions

void State_Settings::initVariables()
{
    modes = sf::VideoMode::getFullscreenModes();
}

void State_Settings::initFonts()
{
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::STATE_MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
}

void State_Settings::initKeyBinds()
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

void State_Settings::initGui()
{
    const sf::VideoMode &vm = stateData->gfxSettings->resolution;

    // Background
    background.setSize(sf::Vector2f(
                           static_cast<float>(vm.width),
                           static_cast<float>(vm.height)
                           ));

    if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png")) {
        std::cout << "ERROR::STATE_MAINMENU::FAILED TO LOAD BACKGROUND TEXTURE" << std::endl;
    }
    background.setTexture(&backgroundTexture);

    // Buttons
    buttons["BACK"] = new gui::Button(
                gui::pTpX(72.f, vm), gui::pTpY(81.5f, vm), gui::pTpX(8.f, vm), gui::pTpY(6.f, vm),
                &font, "Back", gui::calcCharSize(vm),
                sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
                );

    buttons["APPLY"] = new gui::Button(
                gui::pTpX(62.f, vm), gui::pTpY(81.5f, vm), gui::pTpX(8.f, vm), gui::pTpY(6.f, vm),
                &font, "Apply", gui::calcCharSize(vm),
                sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
                );

    // Modes
    std::vector<std::string> modesStr;
    for (auto &itr : modes) {
        modesStr.push_back(std::to_string(itr.width) + 'x' + std::to_string(itr.height));
    }

    // DropDownLists
    dropDownLists["RESOLUTION"] = new gui::DropDownList(gui::pTpX(42.f, vm), gui::pTpY(42.f, vm),
                                                        gui::pTpX(10.4f, vm), gui::pTpY(4.5f, vm),
                                                        font, modesStr.data(), modesStr.size());

    // Text
    optionsText.setFont(font);
    optionsText.setPosition(sf::Vector2f(gui::pTpX(6.3f, vm), gui::pTpY(42.f, vm)));
    optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
    optionsText.setFillColor(sf::Color(255, 255, 255, 200));
    optionsText.setString("Resolution \n\nFullscreen \n\nV-Sync \n\nAntialiasing\n");
}

void State_Settings::resetGui()
{
    for (auto itr = buttons.begin(); itr != buttons.end(); ++itr) {
        delete itr->second;
    }
    buttons.clear();

    for (auto itr = dropDownLists.begin(); itr != dropDownLists.end(); ++itr) {
        delete itr->second;
    }
    dropDownLists.clear();

    initGui();
}

// Constructor / Destructor

State_Settings::State_Settings(StateData *stateData)
    : State(stateData)
{
    initVariables();
    initFonts();
    initKeyBinds();
    initGui();
}

State_Settings::~State_Settings()
{
    for (auto itr = buttons.begin(); itr != buttons.end(); ++itr) {
        delete itr->second;
    }

    for (auto itr2 = dropDownLists.begin(); itr2 != dropDownLists.end(); ++itr2) {
        delete itr2->second;
    }
}

// Accessors

// Functions

void State_Settings::updateInput(const float &dt)
{

}

void State_Settings::updateGui(const float &dt)
{
    // Buttons
    for (auto &itr : buttons) {
        itr.second->update(mousePosWindow);
    }

    if (buttons["BACK"]->isPressed()) {
        endState();
    }
    if (buttons["APPLY"]->isPressed()) {

        // REMOVE LATER
        stateData->gfxSettings->resolution = modes[dropDownLists["RESOLUTION"]->getActiveElementId()];
        window->create(stateData->gfxSettings->resolution, stateData->gfxSettings->title, sf::Style::Default);
        resetGui();
    }

    // DropDown Lists
    for (auto &itr : dropDownLists) {
        itr.second->update(mousePosWindow, dt);
    }
}

void State_Settings::update(const float &dt)
{
    updateMousePositions();
    updateInput(dt);

    updateGui(dt);
}

void State_Settings::renderGui(sf::RenderTarget &target)
{
    for (auto &itr : buttons) {
        itr.second->render(target);
    }

    for (auto &itr : dropDownLists) {
        itr.second->render(target);
    }
}

void State_Settings::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    target->draw(background);

    renderGui(*target);

    target->draw(optionsText);

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
