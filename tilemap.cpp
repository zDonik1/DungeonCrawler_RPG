#include "tilemap.h"

// Private functions

void TileMap::clear()
{
    for (unsigned x = 0; x < static_cast<unsigned>(maxSizeWorldGrid.x); ++x) {
        for (unsigned y = 0; y < static_cast<unsigned>(maxSizeWorldGrid.y); ++y) {
            for (unsigned z = 0; z < static_cast<unsigned>(layers); ++z) {
                for (unsigned k = 0; k < static_cast<unsigned>(map[x][y][z].size()); ++k) {
                    delete map[x][y][z][k];
                    map[x][y][z][k] = nullptr;
                }

                map[x][y][z].clear();
            }

            map[x][y].clear();
        }

        map[x].clear();
    }

    map.clear();
}

// Constructor / Destructor

TileMap::TileMap(float gridSize, int width, int height, std::string l_textureFile)
{
    gridSizeF = gridSize;
    gridSizeI = static_cast<int>(gridSizeF);
    maxSizeWorldGrid.x = width;
    maxSizeWorldGrid.y = height;
    maxSizeWorld.x = static_cast<float>(width * gridSize);
    maxSizeWorld.y = static_cast<float>(height * gridSize);
    layers = 1;
    textureFile = l_textureFile;

    fromX = 0;
    toX = 0;
    fromY = 0;
    toY = 0;
    layer = 0;

    map.resize(static_cast<unsigned>(maxSizeWorldGrid.x), std::vector< std::vector< std::vector<Tile*> > >());

    for (unsigned x = 0; x < static_cast<unsigned>(maxSizeWorldGrid.x); ++x) {

        for (unsigned y = 0; y < static_cast<unsigned>(maxSizeWorldGrid.y); ++y) {

            map[x].resize(static_cast<unsigned>(maxSizeWorldGrid.y), std::vector< std::vector<Tile*> >());

            for (unsigned z = 0; z < static_cast<unsigned>(layers); z++) {

                map[x][y].resize(static_cast<unsigned>(layers), std::vector<Tile*>());
            }
        }
    }

    if (!tileSheet.loadFromFile(textureFile)) {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE_TEXTURE_SHEET - filename: " << textureFile << std::endl;
    }

    collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    collisionBox.setOutlineColor(sf::Color::Red);
    collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
    clear();
}

// Accessors

const sf::Texture *TileMap::getTileSheet() const
{
    return &tileSheet;
}

int TileMap::getLayerSize(unsigned x, unsigned y, unsigned layer) const
{
    if (x < map.size() && y < map[x].size() && layer < map[x][y].size()) {
        return static_cast<int>(map[x][y][layer].size());
    }

    return -1;
}

// Functions

void TileMap::addTile(unsigned x, unsigned y, unsigned z, const sf::IntRect &textureRect, bool collision, short type)
{
    if (x < static_cast<unsigned>(maxSizeWorldGrid.x) &&
            y < static_cast<unsigned>(maxSizeWorldGrid.y) &&
            z < static_cast<unsigned>(layers))
    {
        map[x][y][z].push_back(new Tile(
                                   static_cast<int>(x), static_cast<int>(y), gridSizeF,
                                   tileSheet, textureRect, collision, static_cast<TileType>(type)
                                   ));
    }
}

void TileMap::removeTile(unsigned x, unsigned y, unsigned z)
{
    if (x < static_cast<unsigned>(maxSizeWorldGrid.x) &&
            y < static_cast<unsigned>(maxSizeWorldGrid.y) &&
            z < static_cast<unsigned>(layers))
    {
        if (!map[x][y][z].empty()) {
            delete map[x][y][z][map[x][y][z].size() - 1];
            map[x][y][z].pop_back();
        }
    }
}

void TileMap::saveToFile(const std::string &filename)
{
    std::ofstream outFile;

    outFile.open(filename);

    if (outFile.is_open()) {
        outFile << maxSizeWorldGrid.x << " " << maxSizeWorldGrid.y << std::endl;
        outFile << gridSizeI << std::endl;
        outFile << layers << std::endl;
        outFile << textureFile << std::endl;

        for (unsigned x = 0; x < static_cast<unsigned>(maxSizeWorldGrid.x); ++x) {
            for (unsigned y = 0; y < static_cast<unsigned>(maxSizeWorldGrid.y); ++y) {
                for (unsigned z = 0; z < static_cast<unsigned>(layers); ++z) {
                    if (!map[x][y][z].empty()) {
                        for (unsigned k = 0; k < map[x][y][z].size(); ++k) {
                            outFile << x << " " << y << " " << z << " "
                                    << map[x][y][z][k]->getAsString() << std::endl;
                        }
                    }
                }
            }
        }
    }
    else {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE - filename: " << filename << std::endl;
    }

    outFile.close();
}

void TileMap::loadFromFile(const std::string &filename)
{
    std::ifstream inFile;

    inFile.open(filename);

    if (inFile.is_open()) {
        sf::Vector2i size;
        int gridSize = 0;
        int inLayers = 0;
        std::string inTextureFile = "";
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        int trX = 0;
        int trY = 0;
        bool collision = false;
        short type = 0;

        inFile >> size.x >> size.y >> gridSize >> inLayers >> inTextureFile;

        gridSizeF = static_cast<float>(gridSize);
        gridSizeI = gridSize;
        maxSizeWorldGrid.x = size.x;
        maxSizeWorldGrid.y = size.y;
        layers = inLayers;
        textureFile = inTextureFile;

        clear();

        map.resize(static_cast<unsigned>(maxSizeWorldGrid.x), std::vector< std::vector< std::vector<Tile*> > >());
        for (unsigned x = 0; x < static_cast<unsigned>(maxSizeWorldGrid.x); ++x) {

            for (unsigned y = 0; y < static_cast<unsigned>(maxSizeWorldGrid.y); ++y) {

                map[x].resize(static_cast<unsigned>(maxSizeWorldGrid.y), std::vector< std::vector<Tile*> >());

                for (unsigned z = 0; z < static_cast<unsigned>(layers); z++) {

                    map[x][y].resize(static_cast<unsigned>(layers), std::vector<Tile*>());
                }
            }
        }

        std::cout << sizeof(map) << std::endl;

        if (!tileSheet.loadFromFile(textureFile)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE_TEXTURE_SHEET - filename: " << textureFile << std::endl;
        }

        // Loading tiles
        while (inFile >> x >> y >> z >> trX >> trY >> collision >> type) {
            map[x][y][z].push_back(new Tile(
                                       static_cast<int>(x), static_cast<int>(y), gridSizeF,
                                       tileSheet, sf::IntRect(trX, trY, gridSizeI, gridSizeI),
                                       collision, static_cast<TileType>(type)
                                       ));
        }
    }
    else {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE - filename: " << filename << std::endl;
    }

    inFile.close();
}

void TileMap::updateCollision(Entity *entity, const float &dt)
{
    // World bound collision check
    if (entity->getNextPositionBounds(dt).left < 0.f) {
        entity->setPosition(0.f, entity->getPosition().y);
        entity->stopVelocityX();
    }
    else if (entity->getNextPositionBounds(dt).left + entity->getNextPositionBounds(dt).width > maxSizeWorld.x) {
        entity->setPosition(maxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->stopVelocityX();
    }

    if (entity->getNextPositionBounds(dt).top < 0.f) {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->stopVelocityY();
    }
    else if (entity->getNextPositionBounds(dt).top + entity->getNextPositionBounds(dt).height > maxSizeWorld.y) {
        entity->setPosition(entity->getPosition().x, maxSizeWorld.y - entity->getGlobalBounds().height);
        entity->stopVelocityY();
    }

    // Tile collision check
    layer = 0;

    fromX = entity->getGridPosition(gridSizeI).x - 1;
    if (fromX < 0)
        fromX = 0;
    else if (fromX > maxSizeWorldGrid.x)
        fromX = maxSizeWorldGrid.x;

    toX = entity->getGridPosition(gridSizeI).x + 3;
    if (toX < 0)
        toX = 0;
    else if (toX > maxSizeWorldGrid.x)
        toX = maxSizeWorldGrid.x;

    fromY = entity->getGridPosition(gridSizeI).y - 1;
    if (fromY < 0)
        fromY = 0;
    else if (fromY > maxSizeWorldGrid.y)
        fromY = maxSizeWorldGrid.y;

    toY = entity->getGridPosition(gridSizeI).y + 3;
    if (toY < 0)
        toY = 0;
    else if (toY > maxSizeWorldGrid.y)
        toY = maxSizeWorldGrid.y;

    for (unsigned x = static_cast<unsigned>(fromX); x < static_cast<unsigned>(toX); ++x) {
        for (unsigned y = static_cast<unsigned>(fromY); y < static_cast<unsigned>(toY); ++y) {
            for (unsigned k = 0; k < map[x][y][layer].size(); ++k) {
                sf::FloatRect entityBounds = entity->getGlobalBounds();
                sf::FloatRect wallBounds = map[x][y][layer][k]->getGlobalBounds();
                sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

                if (map[x][y][layer][k]->getCollision() && map[x][y][layer][k]->intersects(nextPositionBounds)) {
                    // Bottom collision check
                    if (entityBounds.top < wallBounds.top
                            && entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
                            && entityBounds.left < wallBounds.left + wallBounds.width
                            && entityBounds.left + entityBounds.width > wallBounds.left
                            )
                    {
                        entity->stopVelocityY();
                        entity->setPosition(entityBounds.left, wallBounds.top - entityBounds.height);
                    }

                    // Top collision check
                    if (entityBounds.top > wallBounds.top
                            && entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
                            && entityBounds.left < wallBounds.left + wallBounds.width
                            && entityBounds.left + entityBounds.width > wallBounds.left
                            )
                    {
                        entity->stopVelocityY();
                        entity->setPosition(entityBounds.left, wallBounds.top + wallBounds.height);
                    }

                    // Right collision check
                    if (entityBounds.left < wallBounds.left
                            && entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
                            && entityBounds.top < wallBounds.top + wallBounds.height
                            && entityBounds.top + entityBounds.height > wallBounds.top
                            )
                    {
                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.left - entityBounds.width, entityBounds.top);
                    }

                    // Left collision check
                    if (entityBounds.left > wallBounds.left
                            && entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
                            && entityBounds.top < wallBounds.top + wallBounds.height
                            && entityBounds.top + entityBounds.height > wallBounds.top
                            )
                    {
                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.left + wallBounds.width, entityBounds.top);
                    }
                }
            }
        }
    }
}

void TileMap::update()
{

}

void TileMap::renderDeferred(sf::RenderTarget &target, sf::Shader *shader, sf::Vector2f playerPosition)
{
    while (!deferredRenderStack.empty()) {
        if (shader) {
            deferredRenderStack.top()->render(target, shader, playerPosition);
        }
        else {
            deferredRenderStack.top()->render(target);
        }
        deferredRenderStack.pop();
    }
}

void TileMap::render(sf::RenderTarget &target, const sf::Vector2i &gridPosition,
                     sf::Shader *shader, sf::Vector2f playerPosition, bool showCollisionBox)
{
    // Debug rendering culling
    layer = 0;

    fromX = gridPosition.x - 15;
    if (fromX < 0)
        fromX = 0;
    else if (fromX > maxSizeWorldGrid.x)
        fromX = maxSizeWorldGrid.x;

    toX = gridPosition.x + 16;
    if (toX < 0)
        toX = 0;
    else if (toX > maxSizeWorldGrid.x)
        toX = maxSizeWorldGrid.x;

    fromY = gridPosition.y - 9;
    if (fromY < 0)
        fromY = 0;
    else if (fromY > maxSizeWorldGrid.y)
        fromY = maxSizeWorldGrid.y;

    toY = gridPosition.y + 10;
    if (toY < 0)
        toY = 0;
    else if (toY > maxSizeWorldGrid.y)
        toY = maxSizeWorldGrid.y;

    for (unsigned x = static_cast<unsigned>(fromX); x < static_cast<unsigned>(toX); ++x) {

        for (unsigned y = static_cast<unsigned>(fromY); y < static_cast<unsigned>(toY); ++y) {

            for (unsigned k = 0; k < map[x][y][layer].size(); ++k) {

                if (map[x][y][layer][k]->getType() == TileType::DOODAD) {
                    deferredRenderStack.push(map[x][y][layer][k]);
                }
                else {
                    if (shader) {
                        map[x][y][layer][k]->render(target, shader, playerPosition);
                    }
                    else {
                        map[x][y][layer][k]->render(target);
                    }
                }

                if (showCollisionBox) {
                    if (map[x][y][layer][k]->getCollision()) {
                        collisionBox.setPosition(map[x][y][layer][k]->getPosition());
                        target.draw(collisionBox);
                    }
                }
            }
        }
    }
}
