 #pragma once

#include "state_game.h"
#include "state_mainmenu.h"

class Game
{
private:
    // Variables
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt; // delta time

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    float gridSize;
    int textureSize;

    // Initialization
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();

public:
    //Constructors / Destructors
    Game();
    virtual ~Game();

    // Functions
    void endApplication();
    void updateDt();
    void updateSFMLevents();
    void update();

    void render();

    void run();
};
