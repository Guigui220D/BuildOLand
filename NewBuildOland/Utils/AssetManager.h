#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class AssetManager {
public:
    sf::Font* getFont(std::string fontName);

private:
    const std::string FONT_FOLDER = "Res/Font/";
    std::vector<sf::Font*> fonts;
    std::vector<std::string> fontNames;
};



