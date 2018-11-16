#include <vector>
#include <memory>

#include "Gui.h"

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
        GuiZone(sf::FloatRect zone, float aspectRatio, ZoneHAlign hAlign = ZoneHAlign::HCenter, ZoneVAlign vAlign = ZoneVAlign::VCenter);
        //Dispatch an event (click for example) to children
        bool handleEvent(sf::Event e);
        void draw(sf::RenderWindow& rw);
        void update(float dt);

        inline void setVAlign(ZoneVAlign valign) { vAlign = valign; }
        inline void setHAlign(ZoneHAlign halign) { hAlign = halign; }
        inline void setAspectRatio(float aspectRatio) { ratio = aspectRatio; }
        inline void setRect(sf::FloatRect zone) { rect = zone; }

        inline ZoneVAlign getVAlign() const { return vAlign; }
        inline ZoneHAlign getHAlign() const { return hAlign; }
        inline float getRatio() const { return ratio; }
        inline sf::FloatRect getRect() const { return rect; }

        //Changes the view (not the viewport) dimensions accordingly to the aspect ratio
        void setZoneHeight(float height);
        void setZoneWidth(float width);

        sf::View getView(sf::Vector2u windowSize);

        std::vector<std::unique_ptr<Gui>> guiElements;

    private:
        sf::FloatRect rect;
        float ratio;
        ZoneHAlign hAlign;
        ZoneVAlign vAlign;
        float viewHeight;
        float viewWidth;

        void calculateView();
        //Used as a cache to not calculate the view each time
        sf::View calculatedView;
        sf::Vector2u viewWindowSize;

};
