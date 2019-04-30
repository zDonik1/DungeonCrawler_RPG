#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

class GraphicsSettings
{
public:
    // Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    int frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    // Constructor
    GraphicsSettings();

    // Functions
    void saveToFile(const std::string &path);
    void loadFromFile(const std::string &path);
};
