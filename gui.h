#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

enum class ButtonState {
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

namespace gui
{
// Functions
float pTpX(float perc, const sf::VideoMode& vm);
float pTpY(float perc, const sf::VideoMode& vm);
unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

// Classes
class Button
{
private:
    ButtonState buttonState;
    unsigned short id;

    sf::RectangleShape shape;
    sf::Font *font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    sf::Color outlineIdleColor;
    sf::Color outlineHoverColor;
    sf::Color outlineActiveColor;

public:
    Button(float x, float y, float width, float height, sf::Font *l_font, std::string l_text, unsigned characterSize,
           sf::Color l_textIdleColor, sf::Color l_textHoverColor, sf::Color l_textActiveColor,
           sf::Color l_idleColor, sf::Color l_hoverColor, sf::Color l_activeColor,
           sf::Color l_outlineIdleColor = sf::Color::Transparent, sf::Color l_outlineHoverColor = sf::Color::Transparent, sf::Color l_outlineActiveColor = sf::Color::Transparent,
           unsigned short l_id = 0);
    ~Button();

    // Accessors
    bool isPressed() const;
    std::string getText() const;
    unsigned short getId() const;

    // Modifiers
    void setText(std::string l_text);
    void setId(unsigned short l_id);

    // Functions
    void update(const sf::Vector2i &mousePosWindow);
    void render(sf::RenderTarget &target);
};

class DropDownList
{
private:
    // Variables
    float keytime;
    float keytimeMax;
    sf::Font &font;
    gui::Button *activeElement;
    std::vector<gui::Button*> list;
    bool showList;

public:
    // Constructor / Destructor
    DropDownList(float x, float y, float width, float height,
                 sf::Font &l_font, std::string l_list[], unsigned noOfElements, unsigned defaultIndex = 0);
    ~DropDownList();

    // Accessors
    bool getKeytime();
    unsigned short getActiveElementId() const;

    // Functions
    void updateKeytime(const float &dt);
    void update(const sf::Vector2i &mousePosWindow, const float &dt);
    void render(sf::RenderTarget &target);
};

class TextureSelector
{
private:
    float keytime;
    float keytimeMax;
    float gridSize;
    int textureSize;
    bool active;
    bool hidden;
    gui::Button *hideBtn;
    sf::RectangleShape bounds;
    sf::Sprite sheet;
    sf::RectangleShape selector;
    sf::Vector2i mousePosGrid;
    sf::IntRect textureRect;
    sf::Font font;

public:
    // Constructor / Destructor
    TextureSelector(float x, float y, float width, float height, float l_gridSize, int l_textureSize,
                    const sf::Texture *textureSheet, sf::Font l_font, std::string text);
    ~TextureSelector();

    // Accessors
    const bool &getActive() const;
    const sf::IntRect &getTextureRect() const;
    bool getKeytime();

    // Functions
    void updateKeytime(const float &dt);
    void update(const sf::Vector2i &mousePosWindow, const float &dt);
    void render(sf::RenderTarget &target);
};
}
