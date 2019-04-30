#pragma once

#include "player.h"
#include "graphicssettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
    // Variables
    float gridSize;
    int textureSize;
    sf::RenderWindow *window;
    GraphicsSettings *gfxSettings;
    std::map<std::string, int> *suppKeys;
    std::map<std::string, State*> *states;
};

class State
{
protected:
    StateData *stateData;
    std::stack<State*> *states;
    sf::RenderWindow *window;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keyBinds;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    // Resources
    std::map<std::string, sf::Texture> textures;

    // Initialization
    virtual void initKeyBinds() = 0;

public:
    // Constructor / Destructor
    State(StateData *l_stateData);
    virtual ~State();

    // Accessors
    const bool &getQuit() const;
    bool getKeytime();

    // Functions
    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateKeytime(const float &dt);
    virtual void updateMousePositions(sf::View *view = nullptr);
    virtual void updateInput(const float &dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};
