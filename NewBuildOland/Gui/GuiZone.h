#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

enum ZoneHAlign
{
    HCenter,
    HLeft,
    HRight
};

enum ZoneVAlign
{
    VCenter,
    VTop,
    VBottom
};

class GuiZone
{
    public:
        GuiZone(sf::FloatRect zone, float aspectRatio, ZoneHAlign hAlign, ZoneVAlign vAlign);
        //Dispatch an event (click for example) to children
        bool handleEvent(sf::Event e);
        //Draw the GUI element inside of the zone
        void draw(sf::RenderWindow& rw);

        sf::View getView(sf::Vector2f windowSize);

    private:
        sf::FloatRect rect;
        float ratio;
        ZoneHAlign hAlign;
        ZoneVAlign vAlign;

        void calculateView();
        //Used as a cache to not calculate the view each time
        sf::View calculatedView;
        sf::Vector2f viewWindowSize;

};
