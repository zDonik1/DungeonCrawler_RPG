#include "state_editor.h"

// Initializer functions

void State_Editor::initVariables()
{
    textureRect = sf::IntRect(0, 0, static_cast<int>(stateData->textureSize), static_cast<int>(stateData->textureSize));
    collision = false;
    type = static_cast<short>(TileType::DEFAULT);
    cameraSpeed = 150.f;
    layer = 0;
}

void State_Editor::initView()
{
    view.setSize(sf::Vector2f(
                     static_cast<float>(stateData->gfxSettings->resolution.width),
                     static_cast<float>(stateData->gfxSettings->resolution.height)
                     ));
    view.setCenter(
                static_cast<float>(stateData->gfxSettings->resolution.width) / 2.f,
                static_cast<float>(stateData->gfxSettings->resolution.height) / 2.f
                );
}

void State_Editor::initFonts()
{
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::STATE_EDITOR::COULD NOT LOAD FONT" << std::endl;
    }
}

void State_Editor::initText()
{
    cursorText.setFont(font);
    cursorText.setCharacterSize(15);
    cursorText.setPosition(mousePosView);
    std::stringstream ss;
    ss << mousePosView.x << " " << mousePosView.y << "\n" << textureRect.left << " " << textureRect.top;
    cursorText.setString(ss.str());
}

void State_Editor::initKeyBinds()
{
    std::ifstream ifs("Config/state_editor_keybinds.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void State_Editor::initPauseMenu()
{
    const sf::VideoMode &vm = stateData->gfxSettings->resolution;

    pmenu = new PauseMenu(stateData->gfxSettings->resolution, font);

    pmenu->addButton("QUIT", gui::pTpY(74.f, vm), gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), gui::calcCharSize(vm), "Quit");
    pmenu->addButton("SAVE", gui::pTpY(46.f, vm), gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), gui::calcCharSize(vm), "Save");
    pmenu->addButton("LOAD", gui::pTpY(37.f, vm), gui::pTpX(13.f, vm), gui::pTpY(6.f, vm), gui::calcCharSize(vm), "Load");
}

void State_Editor::initGui()
{
    sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(stateData->gfxSettings->resolution.height)));
    sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    sidebar.setOutlineThickness(1.f);

    selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
    selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    selectorRect.setOutlineThickness(1.f);
    selectorRect.setOutlineColor(sf::Color::Green);

    selectorRect.setTexture(tileMap->getTileSheet());
    selectorRect.setTextureRect(textureRect);

    sf::Vector2i tileSheetSize = sf::Vector2i(tileMap->getTileSheet()->getSize().x, tileMap->getTileSheet()->getSize().y);
    textureSelector = new gui::TextureSelector(20.f, 20.f,
                                               tileSheetSize.x / stateData->textureSize * gridSize,
                                               tileSheetSize.y / stateData->textureSize * gridSize,
                                               stateData->gridSize, stateData->textureSize, tileMap->getTileSheet(), font, "TS");
}

void State_Editor::initTileMap()
{
    tileMap = new TileMap(stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");
}

// Constructor / Destructor

State_Editor::State_Editor(StateData *stateData)
    : State(stateData)
{
    initVariables();
    initView();
    initFonts();
    initText();
    initKeyBinds();
    initPauseMenu();
    initTileMap();
    initGui();
}

State_Editor::~State_Editor()
{
    for (auto itr = buttons.begin(); itr != buttons.end(); ++itr) {
        delete itr->second;
    }

    delete pmenu;
    delete tileMap;
    delete textureSelector;
}

// Functions

void State_Editor::updateInput(const float &dt)
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

void State_Editor::updateEditorInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_CAMERA_UP")))) {
        view.move(0.f, -cameraSpeed * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_CAMERA_DOWN")))) {
        view.move(0.f, cameraSpeed * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_CAMERA_LEFT")))) {
        view.move(-cameraSpeed * dt, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_CAMERA_RIGHT")))) {
        view.move(cameraSpeed * dt, 0.f);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeytime()) {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow))) {
            if (!textureSelector->getActive()) {
                tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect, collision, type);
            }
            else {
                textureRect = textureSelector->getTextureRect();
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeytime()) {
        if (!textureSelector->getActive() && !sidebar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow))) {
            tileMap->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("TOGGLE_COLLISION"))) && getKeytime()) {
        if (collision) {
            collision = false;
        }
        else {
            collision = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("INCREASE_TYPE"))) && getKeytime()) {
        ++type;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("DECREASE_TYPE"))) && getKeytime()) {
        if (type > 0)
            --type;
    }
}

void State_Editor::updateButtons()
{
    for (auto &itr : buttons) {
        itr.second->update(mousePosWindow);
    }
}

void State_Editor::updateGui(const float &dt)
{
    textureSelector->update(mousePosWindow, dt);

    if (!textureSelector->getActive()) {
        selectorRect.setTextureRect(textureRect);
        selectorRect.setPosition(mousePosGrid.x * stateData->gridSize, mousePosGrid.y * stateData->gridSize);
    }

    cursorText.setPosition(mousePosView.x + 100.f, mousePosView.y - 50.f);
    std::stringstream ss;
    ss << mousePosGrid.x << " " << mousePosGrid.y << "\n"
       << textureRect.left << " " << textureRect.top << "\n"
       << "Collision: " << collision << "\n"
       << "Type: " << type << "\n"
       << "Tiles: " << tileMap->getLayerSize(static_cast<unsigned>(mousePosGrid.x),
                                             static_cast<unsigned>(mousePosGrid.y),
                                             static_cast<unsigned>(layer));
    cursorText.setString(ss.str());
}

void State_Editor::updatePauseMenuButtons()
{
    if (pmenu->isButtonPressed("QUIT")) {
        endState();
    }

    if (pmenu->isButtonPressed("SAVE")) {
        tileMap->saveToFile("Maps/map.map");
    }

    if (pmenu->isButtonPressed("LOAD")) {
        tileMap->loadFromFile("Maps/map.map");
    }
}

void State_Editor::update(const float &dt)
{
    updateMousePositions(&view);
    updateKeytime(dt);
    updateInput(dt);

    if (!paused) {
        updateButtons();
        updateGui(dt);
        updateEditorInput(dt);
    }
    else {
        pmenu->update(mousePosWindow);
        updatePauseMenuButtons();
    }
}

void State_Editor::renderButtons(sf::RenderTarget &target)
{
    for (auto &itr : buttons) {
        itr.second->render(target);
    }
}

void State_Editor::renderGui(sf::RenderTarget &target)
{
    if (!textureSelector->getActive()) {
        target.setView(view);
        target.draw(selectorRect);
    }

    target.setView(window->getDefaultView());
    textureSelector->render(target);
    target.draw(sidebar);

    target.setView(view);
    target.draw(cursorText);
}

void State_Editor::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    target->setView(view);
    tileMap->render(*target, mousePosGrid, nullptr, sf::Vector2f(), true);
    tileMap->renderDeferred(*target);

    target->setView(window->getDefaultView());
    renderButtons(*target);

    renderGui(*target);

    if (paused) {
        target->setView(window->getDefaultView());
        pmenu->render(*target);
    }
}
