#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

enum class TileType
{
     DEFAULT = 0,
     DAMAGING,
     DOODAD
};

class Tile
{
private:


protected:
    // Variables
    sf::Sprite shape;
    bool collision;
    TileType type;

public:
    // Constructor / Destructor
    Tile();
    Tile(int gridX, int gridY, float gridSizeF, sf::Texture &l_texture, sf::IntRect textureRect,
         bool l_collision = false, TileType l_type = TileType::DEFAULT);
    virtual ~Tile();

    // Accessors
    const sf::Vector2f &getPosition() const;
    bool getCollision() const;
    sf::FloatRect getGlobalBounds() const;
    const std::string getAsString() const;
    TileType getType() const;

    // Functions
    bool intersects(const sf::FloatRect &bounds) const;
    void update();
    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, sf::Vector2f playerPosition = sf::Vector2f());
};
