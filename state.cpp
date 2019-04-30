#include "state.h"

// Constructor / Destructor

State::State(StateData *l_stateData)
{
    stateData = l_stateData;
    window = stateData->window;
    supportedKeys = stateData->suppKeys;
    quit = false;
    paused = false;
    states = stateData->states;
    keytime = 0.f;
    keytimeMax = 20.f;
    gridSize = stateData->gridSize;
}

State::~State()
{

}

// Accessors

const bool &State::getQuit() const
{
    return quit;
}

bool State::getKeytime()
{
    if (keytime >= keytimeMax) {
        keytime = 0.f;
        return true;
    }

    return false;
}

// Functions

void State::endState()
{
    quit = true;
}

void State::pauseState()
{
    paused = true;
}

void State::unpauseState()
{
    paused = false;
}

void State::updateKeytime(const float &dt)
{
    if (keytime < keytimeMax) {
        keytime += 100.f * dt;
    }
}

void State::updateMousePositions(sf::View *view)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);

    if (view)
        window->setView(*view);

    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mousePosGrid = sf::Vector2i(
                static_cast<int>(mousePosView.x) / static_cast<int>(gridSize),
                static_cast<int>(mousePosView.y) / static_cast<int>(gridSize)
                );

    window->setView(window->getDefaultView());
}
