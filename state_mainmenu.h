#pragma once

#include "state_game.h"
#include "state_editor.h"
#include "state_settings.h"
#include "gui.h"

class State_MainMenu : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    sf::RectangleShape buttonBackground;
    std::map<std::string, gui::Button*> buttons;

    // Initialization
    void initVariables();
    void initFonts();
    void initKeyBinds();
    void initGui();
    void resetGui();

public:
    State_MainMenu(StateData *stateData);
    virtual ~State_MainMenu();

    // Functions
    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};
