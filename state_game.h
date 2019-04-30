#pragma once

#include "state.h"
#include "pausemenu.h"
#include "tilemap.h"
#include "playergui.h"

class PauseMenu;
class Player;
class PlayerGUI;
class TileMap;

class State_Game : public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu *pmenu;

    sf::Shader coreShader;

    Player *player;
    PlayerGUI *playerGUI;

    TileMap *tileMap;

    // Initialization
    void initDeferredRender();
    void initView();
    void initKeyBinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initShaders();
    void initPlayers();
    void initPlayerGUI();
    void initTileMap();

public:
    State_Game(StateData *stateData);
    virtual ~State_Game();

    // Functions
    void updateView(const float &dt);
    void updateInput(const float &dt);
    void updatePlayerInput(const float &dt);
    void updatePlayerGUI(const float &dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);
};
