#pragma once

#include "state.h"
#include "gui.h"

class State_Settings : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    // Initialization
    void initVariables();
    void initFonts();
    void initKeyBinds();
    void initGui();
    void resetGui();

public:
    // Constructor / Destructor
    State_Settings(StateData *stateData);
    virtual ~State_Settings();

    // Functions
    void updateInput(const float &dt);
    void updateGui(const float &dt);
    void update(const float &dt);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};
