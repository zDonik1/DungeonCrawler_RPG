#include "game.h"

// Static funcitons

// Initializer functions

void Game::initVariables()
{
    window = nullptr;

    dt = 0.f;

    gridSize = 64.f;
    textureSize = 64;
}

void Game::initGraphicsSettings()
{
    gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initStateData()
{
    stateData.window = window;
    stateData.gfxSettings = &gfxSettings;
    stateData.suppKeys = &supportedKeys;
    stateData.states = &states;
    stateData.gridSize = gridSize;
    stateData.textureSize = textureSize;
}

void Game::initWindow()
{
    if (gfxSettings.fullscreen) {
        window = new sf::RenderWindow(gfxSettings.resolution, gfxSettings.title, sf::Style::Fullscreen, gfxSettings.contextSettings);
    }
    else {
        window = new sf::RenderWindow(gfxSettings.resolution, gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, gfxSettings.contextSettings);
    }
    window->setFramerateLimit(static_cast<unsigned>(gfxSettings.frameRateLimit));
    window->setVerticalSyncEnabled(gfxSettings.verticalSync);
}

void Game::initKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int keyValue = 0;
        while (ifs >> key >> keyValue) {
            supportedKeys[key] = keyValue;
        }
    }

    ifs.close();

    // debug
    for (auto i : supportedKeys) {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

void Game::initStates()
{
    states.push(new State_MainMenu(&stateData));
}

// Constructors / Destructors

Game::Game()
{
    initVariables();
    initGraphicsSettings();
    initWindow();
    initKeys();
    initStateData();
    initStates();
}

Game::~Game()
{
    delete window;

    while (!states.empty()) {
        delete states.top();
        states.pop();
    }
}

 // Functions

void Game::endApplication()
{

}

void Game::updateDt()
{
    dt = dtClock.restart().asSeconds();
}

void Game::updateSFMLevents()
{
    while (window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Game::update()
{
    updateSFMLevents();

    if (!states.empty()) {
        if (window->hasFocus()) {
            states.top()->update(dt);

            if (states.top()->getQuit()) {
                states.top()->endState();
                delete states.top();
                states.pop();
            }
        }
    }
    else {
        endApplication();
        window->close();
    }
}

void Game::render()
{
    window->clear();

    // Render stuff here
    if (!states.empty()) {
        states.top()->render(window);
    }

    window->display();
}

void Game::run()
{
    while (window->isOpen()) {
        updateDt();
        update();
        render();
    }
}
