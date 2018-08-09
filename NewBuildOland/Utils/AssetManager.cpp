#include "AssetManager.h"


sf::Font *AssetManager::getFont(std::string fontName) {

    //Get font if it already exists
    for(unsigned int i = 0; i < fontNames.size(); i++) {
        if(fontNames[i] == fontName) {
            return fonts[i];
        }
    }

    //Load font if it isn't already saved
    sf::Font *font = new sf::Font();

    if (font->loadFromFile(FONT_FOLDER + fontName + ".ttf")) {

        fontNames.push_back(fontName);
        fonts.push_back(font);

    } else {
        std::cout << "ERROR LOADING FROM '" + FONT_FOLDER + fontName + ".ttf'" << std::endl;
    }

    return font;

}
