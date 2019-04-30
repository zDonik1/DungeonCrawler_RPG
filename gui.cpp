#include "gui.h"
#include <iostream>

float gui::pTpX(float perc, const sf::VideoMode& vm)
{
    /*
     * Converts a percentage value to pixel relative to the current resolution in the x-axis
     *
     * @param       float perc      The percentage value
     * @param       sf::VideoMode &vm   The current video mode of the window (resolution).
     *
     * @return      float           The calculated pixel value
     *
     */

    return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

float gui::pTpY(float perc, const sf::VideoMode& vm)
{
    /*
     * Converts a percentage value to pixel relative to the current resolution in the y-axis
     *
     * @param       float perc          The percentage value
     * @param       sf::VideoMode &vm   The current video mode of the window (resolution).
     *
     * @return      float           The calculated pixel value
     *
     */

    return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
    /*
     * Converts the character size for text using the current resolution
     *
     * @param       sf::VideoMode &vm   The current video mode of the window (resolution)
     * @param       unsigned Modifier   Used to modify the character size
     *
     * @return      unsigned            The calculated character size value
     *
     */

    return (vm.width + vm.height) / modifier;
}

// Button class ========================

// Constructor / Destructor

gui::Button::Button(float x, float y, float width, float height, sf::Font *l_font, std::string l_text, unsigned characterSize,
                    sf::Color l_textIdleColor, sf::Color l_textHoverColor, sf::Color l_textActiveColor,
                    sf::Color l_idleColor, sf::Color l_hoverColor, sf::Color l_activeColor,
                    sf::Color l_outlineIdleColor, sf::Color l_outlineHoverColor, sf::Color l_outlineActiveColor,
                    unsigned short l_id)
{
    buttonState = ButtonState::BTN_IDLE;
    id = l_id;

    textIdleColor = l_textIdleColor;
    textHoverColor = l_textHoverColor;
    textActiveColor = l_textActiveColor;

    idleColor = l_idleColor;
    hoverColor = l_hoverColor;
    activeColor = l_activeColor;

    outlineIdleColor = l_outlineIdleColor;
    outlineHoverColor = l_outlineHoverColor;
    outlineActiveColor = l_outlineActiveColor;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idleColor);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outlineIdleColor);

    font = l_font;
    text.setFont(*font);
    text.setString(l_text);
    text.setFillColor(textIdleColor);
    text.setCharacterSize(characterSize);
    text.setPosition(
                shape.getPosition().x + shape.getGlobalBounds().width / 2.f - text.getGlobalBounds().width / 2.f,
                shape.getPosition().y + shape.getGlobalBounds().height / 2.f  - text.getGlobalBounds().height / 2.f - 5.f
                );
}

gui::Button::~Button()
{

}

// Accessors

bool gui::Button::isPressed() const
{
    if (buttonState == ButtonState::BTN_ACTIVE) {
        return true;
    }
    else {
        return false;
    }
}

std::string gui::Button::getText() const
{
    return text.getString();
}

unsigned short gui::Button::getId() const
{
    return id;
}

// Modifiers

void gui::Button::setText(std::string l_text)
{
    text.setString(l_text);
}

void gui::Button::setId(unsigned short l_id)
{
    id = l_id;
}

// Functions

void gui::Button::update(const sf::Vector2i &mousePosWindow)
{
    buttonState = ButtonState::BTN_IDLE;

    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
        buttonState = ButtonState::BTN_HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            buttonState = ButtonState::BTN_ACTIVE;
        }
    }

    if (buttonState == ButtonState::BTN_IDLE) {
        shape.setFillColor(idleColor);
        shape.setOutlineColor(outlineIdleColor);
        text.setFillColor(textIdleColor);
    }
    else if (buttonState == ButtonState::BTN_HOVER) {
        shape.setFillColor(hoverColor);
        shape.setOutlineColor(outlineHoverColor);
        text.setFillColor(textHoverColor);
    }
    else if (buttonState == ButtonState::BTN_ACTIVE) {
        shape.setFillColor(activeColor);
        shape.setOutlineColor(outlineActiveColor);
        text.setFillColor(textActiveColor);
    }
    else {
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineColor(sf::Color::Green);
        text.setFillColor(sf::Color::Blue);
    }
}

void gui::Button::render(sf::RenderTarget &target)
{
    target.draw(shape);
    target.draw(text);
}


// DropDownBox class ========================

// Constructor / Destructor

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font &l_font, std::string l_list[], unsigned noOfElements, unsigned defaultIndex)
    : keytime(0.f)
    , keytimeMax(1.f)
    , font(l_font)
    , showList(false)
{
    activeElement =  new gui::Button(
                x, y, width, height, &font, l_list[defaultIndex], 14,
                sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
                );

    for (unsigned short i = 0; i < noOfElements; ++i) {
        list.push_back(new gui::Button(
                           x, y + (i + 1) * height, width, height, &font, l_list[i], 14,
                           sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                           sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                           sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                           i
                           ));
    }
}

gui::DropDownList::~DropDownList()
{
    delete activeElement;

    for (size_t i = 0; i < list.size(); ++i) {
        delete list[i];
    }
}

// Accessors

bool gui::DropDownList::getKeytime()
{
    if (keytime >= keytimeMax) {
        keytime = 0.f;
        return true;
    }

    return false;
}

unsigned short gui::DropDownList::getActiveElementId() const
{
    return activeElement->getId();
}

// Functions

void gui::DropDownList::updateKeytime(const float &dt)
{
    if (keytime < keytimeMax) {
        keytime += 10.f * dt;
    }
}

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float &dt)
{
    updateKeytime(dt);

    activeElement->update(mousePosWindow);

    if (activeElement->isPressed() && getKeytime()) {
        if (showList) {
            showList = false;
        }
        else {
            showList = true;
        }
    }

    if (showList) {
        for (auto &itr : list) {
            itr->update(mousePosWindow);

            if (itr->isPressed() && getKeytime()) {
                showList = false;
                activeElement->setText(itr->getText());
                activeElement->setId(itr->getId());
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget &target)
{
    activeElement->render(target);

    if (showList) {
        for (auto &itr : list) {
            itr->render(target);
        }
    }
}


// TextureSelector class ========================

// Constructor / Destructor

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float l_gridSize, int l_textureSize,
                                      const sf::Texture *textureSheet, sf::Font l_font, std::string text)
    : keytime(0.f)
    , keytimeMax(5.f)
{
    gridSize = l_gridSize;
    textureSize = l_textureSize;
    active = false;
    hidden = false;
    float offset = gridSize;
    font = l_font;

    bounds.setSize(sf::Vector2f(width, height));
    bounds.setPosition(x + offset, y);
    bounds.setFillColor(sf::Color(50, 50, 50, 100));
    bounds.setOutlineThickness(1.f);
    bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    sheet.setTexture(*textureSheet);
    sheet.setScale(gridSize / l_textureSize, gridSize / l_textureSize);
    sheet.setPosition(x + offset, y);

    if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width) {
        sheet.setTextureRect(sf::IntRect(
                                 0,
                                 0,
                                 static_cast<int>(bounds.getGlobalBounds().width),
                                 static_cast<int>(sheet.getGlobalBounds().height)
                                 ));
    }
    if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height) {
        sheet.setTextureRect(sf::IntRect(
                                 0,
                                 0,
                                 static_cast<int>(sheet.getGlobalBounds().width),
                                 static_cast<int>(bounds.getGlobalBounds().height)
                                 ));
    }

    selector.setPosition(x + offset, y);
    selector.setSize(sf::Vector2f(gridSize, gridSize));
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(1.f);
    selector.setOutlineColor(sf::Color::Red);

    textureRect.width = static_cast<int>(textureSize);
    textureRect.height = static_cast<int>(textureSize);

    hideBtn = new gui::Button(
                x, y, 50, 50, &font, text , 16,
                sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
                );
}

gui::TextureSelector::~TextureSelector()
{
    delete hideBtn;
}

// Accessors

const bool &gui::TextureSelector::getActive() const
{
    return active;
}

const sf::IntRect &gui::TextureSelector::getTextureRect() const
{
    return textureRect;
}

bool gui::TextureSelector::getKeytime()
{
    if (keytime >= keytimeMax) {
        keytime = 0.f;
        return true;
    }

    return false;
}

// Functions

void gui::TextureSelector::updateKeytime(const float &dt)
{
    if (keytime < keytimeMax) {
        keytime += 10.f * dt;
    }
}

void gui::TextureSelector::update(const sf::Vector2i &mousePosWindow, const float &dt)
{
    updateKeytime(dt);
    hideBtn->update(mousePosWindow);

    if (hideBtn->isPressed() && getKeytime()) {
        if (hidden)
            hidden = false;
        else
            hidden = true;
    }

    if (!hidden) {
        if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
            active = true;
        }
        else {
            active = false;
        }

        if (active) {
            mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bounds.getPosition().x)) / static_cast<int>(gridSize);
            mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bounds.getPosition().y)) / static_cast<int>(gridSize);
            selector.setPosition(bounds.getPosition().x + mousePosGrid.x * gridSize, bounds.getPosition().y + mousePosGrid.y * gridSize);
        }

        textureRect.left = static_cast<int>((selector.getPosition().x - bounds.getPosition().x) * textureSize / gridSize);
        textureRect.top = static_cast<int>((selector.getPosition().y - bounds.getPosition().y) * textureSize / gridSize);
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target)
{
    if (!hidden) {
        target.draw(bounds);
        target.draw(sheet);

        if (active)
            target.draw(selector);
    }

    hideBtn->render(target);
}
