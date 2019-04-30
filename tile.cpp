#include "tile.h"

// Constructor / Destructor

Tile::Tile()
{
    collision = false;
    type = TileType::DEFAULT;
}

Tile::Tile(int gridX, int gridY, float gridSizeF, sf::Texture &l_texture, sf::IntRect textureRect,
           bool l_collision, TileType l_type)
{
    //shape.setOutlineThickness(1.f);
    //shape.setOutlineColor(sf::Color::Black);
    shape.setPosition(gridX * gridSizeF, gridY * gridSizeF);
    shape.setTexture(l_texture);
    shape.setTextureRect(textureRect);

    collision = l_collision;
    type = l_type;
}

Tile::~Tile()
{

}

// Accessors

const sf::Vector2f &Tile::getPosition() const
{
    return shape.getPosition();
}

bool Tile::getCollision() const
{
    return collision;
}

sf::FloatRect Tile::getGlobalBounds() const
{
    return shape.getGlobalBounds();
}

// Functions

bool Tile::intersects(const sf::FloatRect &bounds) const
{
    return shape.getGlobalBounds().intersects(bounds);
}

const std::string Tile::getAsString() const
{
    std::stringstream ss;

    ss << shape.getTextureRect().left << " " << shape.getTextureRect().top << " " << collision << " " << static_cast<short>(type);

    return ss.str();
}

TileType Tile::getType() const
{
    return type;
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target, sf::Shader *shader, sf::Vector2f playerPosition)
{
    if (shader) {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", playerPosition);

        target.draw(shape, shader);
    }
    else {
        target.draw(shape);
    }
}
