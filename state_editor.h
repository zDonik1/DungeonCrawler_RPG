#pragma once

#include "state.h"
#include "gui.h"
#include "pausemenu.h"
#include "tilemap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class State_Editor : public State
{
private:
    // Variables
    sf::View view;

    sf::Font font;
    sf::Text cursorText;
    PauseMenu *pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap *tileMap;

    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    gui::TextureSelector *textureSelector;

    sf::IntRect textureRect;
    bool collision;
    short type;
    float cameraSpeed;
    int layer;

    // Initialization
    void initVariables();
    void initView();
    void initFonts();
    void initText();
    void initKeyBinds();
    void initPauseMenu();
    void initGui();
    void initTileMap();

public:
    // Constructor / Destructor
    State_Editor(StateData *stateData);
    virtual ~State_Editor();

    // Functions
    void updateInput(const float &dt);
    void updateEditorInput(const float &dt);
    void updateButtons();
    void updateGui(const float &dt);
    void updatePauseMenuButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget &target);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};
