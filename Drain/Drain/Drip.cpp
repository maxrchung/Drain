#include "Drip.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include <random>
#include <ctime>

Drip::Drip(const Time& startTime, const Time& endTime,
    const float xSize, const float xPos, const float speedFactor)
    : startTime{ startTime }, endTime{ endTime },
    xSize{ xSize }, xPos { xPos }, speedFactor { speedFactor }
{
    totalDur = endTime.ms - startTime.ms;
}

// returns and draws a single rectangle after offset ms at xPos growing down
Sprite * Drip::drawRect(int offset, float growDur, Easing easing)
{
    auto s = Storyboard::CreateSprite(getPath(Path::Column), Vector2(xPos, 240), Layer::Foreground, Origin::TopCentre);
    const float ySizeStart = 0;
    const float ySizeFullScreen = 480.0 / 100.0;    // div 100 because of 100x100 sprite size
    const Vector2 endSize = Vector2(xSize, ySizeFullScreen);
    if (growDur != 0) {
        if (startTime.ms + offset + growDur < endTime.ms)
            s->ScaleVector(startTime.ms + offset, startTime.ms + offset + growDur, Vector2(xSize, ySizeStart), endSize, easing);
        else
            s->ScaleVector(startTime.ms + offset, endTime.ms, Vector2(xSize, ySizeStart), endSize, easing);   // clip duration to endTime
    }
    else
        s->ScaleVector(startTime.ms + offset, startTime.ms + offset, endSize, endSize); // scale to proper size instantaneously
    Swatch::colorFgToFgSprites({ s }, startTime.ms + offset, endTime.ms); // color will determine Sprite lifetime
    return s;
}

// returns number of sprites drawn
int Drip::make() {
    drawRect(0, speedFactor, Easing::Linear);
    return 0;
}

void Drip::render() {
    std::cout << "Rendering Drip..." << std::endl;
    Drip(Time("04:04:168"), Time("04:44:074"), 1, 0, 1500).make();
    // drip to cover screen 04:04:168 - 04:44:074
    // 3D drip 05:39:000 - 06:06:000
}

