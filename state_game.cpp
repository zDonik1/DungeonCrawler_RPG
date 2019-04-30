#include "state_game.h"

// Initializer functions

void State_Game::initDeferredRender()
{
    renderTexture.create(stateData->gfxSettings->resolution.width, stateData->gfxSettings->resolution.height);

    renderSprite.setTexture(renderTexture.getTexture());
    renderSprite.setTextureRect(sf::IntRect(
                                    0,
                                    0,
                                    static_cast<int>(stateData->gfxSettings->resolution.width),
                                    static_cast<int>(stateData->gfxSettings->resolution.height)
                                    ));
}

void State_Game::initView()
{
    view.setSize(sf::Vector2f(
                     static_cast<float>(stateData->gfxSettings->resolution.width),
                     static_cast<float>(stateData->gfxSettings->resolution.height)
                     ));
    view.setCenter(sf::Vector2f(stateData->gfxSettings->resolution.width / 2.f, stateData->gfxSettings->resolution.height / 2.f));
}

void State_Game::initKeyBinds()
{
    std::ifstream ifs("Config/state_game_keybinds.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void State_Game::initFonts()
{
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::STATE_MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
}

void State_Game::initTextures()
{
    if (!textures["PLAYER_SHEET2"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET2.png")) {
        std::cout << "ERROR::STATE_GAME::COULD NOT LOAD PLAYER TEXTURE SHEET" << std::endl;
    }
}

void State_Game::initPauseMenu()
{
    const sf::VideoMode &vm = stateData->gfxSettings->resolution;

    pmenu = new PauseMenu(stateData->gfxSettings->resolution, font);

    pmenu->addButton("QUIT", gui::pTpY(74.f, vm), gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), gui::calcCharSize(vm), "Quit");
}

void State_Game::initShaders()
{
    if (!coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag")) {
        std::cout << "ERROR::STATE_GAME::COULD NOT LOAD SHADER" << std::endl;
    }
}

void State_Game::initPlayers()
{
    player = new Player(0.f, 64.f, textures["PLAYER_SHEET2"]);
}

void State_Game::initPlayerGUI()
{
    playerGUI = new PlayerGUI(player, stateData->gfxSettings->resolution);
}

void State_Game::initTileMap()
{
    tileMap = new TileMap(stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet1.png");
    tileMap->loadFromFile("Maps/map.map");
}

// Constructors / Destructors

State_Game::State_Game(StateData *stateData)
    : State(stateData)
{
    initDeferredRender();
    initView();
    initKeyBinds();
    initFonts();
    initTextures();
    initPauseMenu();
    initShaders();
    initPlayers();
    initPlayerGUI();
    initTileMap();
}

State_Game::~State_Game()
{
    delete pmenu;
    delete player;
    delete playerGUI;
    delete tileMap;
}

// Functions

void State_Game::updateView(const float &dt)
{
    view.setCenter(
                std::floor(player->getPosition().x + (static_cast<float>(mousePosWindow.x) - static_cast<float>(stateData->gfxSettings->resolution.width / 2)) / 5.f),
                std::floor(player->getPosition().y + (static_cast<float>(mousePosWindow.y) - static_cast<float>(stateData->gfxSettings->resolution.height / 2)) / 5.f)
                );
}

void State_Game::updateInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE"))) && getKeytime()) {
        if (!paused) {
            pauseState();
        }
        else {
            unpauseState();
        }
    }
}

void State_Game::updatePlayerInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_LEFT"))))
        player->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_RIGHT"))))
        player->move(1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_UP"))))
        player->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_DOWN"))))
        player->move(0.f, 1.f, dt);
}

void State_Game::updatePlayerGUI(const float &dt)
{
    playerGUI->update(dt);
}

void State_Game::updatePauseMenuButtons()
{
    if (pmenu->isButtonPressed("QUIT")) {
        endState();
    }
}

void State_Game::updateTileMap(const float &dt)
{
    tileMap->update();
    tileMap->updateCollision(player, dt);
}

void State_Game::update(const float &dt)
{
    updateMousePositions(&view);
    updateKeytime(dt);
    updateInput(dt);

    if (!paused) {
        updateView(dt);

        updatePlayerInput(dt);

        updateTileMap(dt);

        player->update(dt);

        playerGUI->update(dt);
    }
    else {
        pmenu->update(mousePosWindow);
        updatePauseMenuButtons();
    }
}

void State_Game::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    renderTexture.clear();

    renderTexture.setView(view);
    tileMap->render(renderTexture, player->getGridPosition(static_cast<int>(stateData->gridSize)),
                    &coreShader, player->getCenter(), false);

    player->render(renderTexture, &coreShader, false);

    tileMap->renderDeferred(renderTexture, &coreShader, player->getCenter());

    renderTexture.setView(renderTexture.getDefaultView());
    playerGUI->render(renderTexture);

    if (paused) {
        //renderTexture.setView(renderTexture.getDefaultView());
        pmenu->render(renderTexture);
    }

    // Final render
    renderTexture.display();
    renderSprite.setTexture(renderTexture.getTexture());
    target->draw(renderSprite);
}
