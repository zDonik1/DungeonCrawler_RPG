#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "tile.h"
#include "entity.h"

class Tile;
class Entity;

class TileMap
{
private:
    // Variables
    float gridSizeF;
    int gridSizeI;
    sf::Vector2i maxSizeWorldGrid;
    sf::Vector2f maxSizeWorld;
    int layers;
    std::vector< std::vector< std::vector <std::vector <Tile*> > > > map;
    std::stack<Tile*> deferredRenderStack;
    std::string textureFile;
    sf::Texture tileSheet;
    sf::RectangleShape collisionBox;

    // Culling
    int fromX;
    int toX;
    int fromY;
    int toY;
    unsigned layer;

    // Private functions
    void clear();

public:
    // Constructor / Destructor
    TileMap(float gridSize, int width, int height, std::string l_textureFile);
    virtual ~TileMap();

    // Accessors
    const sf::Texture *getTileSheet() const;
    int getLayerSize(unsigned x, unsigned y, unsigned layer) const;

    // Functions
    void addTile(unsigned x, unsigned y, unsigned z, const sf::IntRect &textureRect, bool collision, short type);
    void removeTile(unsigned x, unsigned y, unsigned z);
    void saveToFile(const std::string &filename);
    void loadFromFile(const std::string &filename);

    void updateCollision(Entity *entity, const float &dt);

    void update();
    void renderDeferred(sf::RenderTarget &target, sf::Shader *shader = nullptr, sf::Vector2f playerPosition = sf::Vector2f());
    void render(sf::RenderTarget &target, const sf::Vector2i &gridPosition,
                sf::Shader *shader = nullptr, sf::Vector2f playerPosition = sf::Vector2f(), bool showCollisionBox = false);
};
