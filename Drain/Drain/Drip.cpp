#include "Drip.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include <random>
#include <ctime>
#include <numeric>

#define SPRITE_SIZE 100.0

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
    const float ySizeFullScreen = Vector2::ScreenSize.y / SPRITE_SIZE;
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

// checks if there are still gaps on screen
bool Drip::ScreenIsNotFilled(){
    // todo
    return false;
}

// returns number of sprites drawn
int Drip::make(bool fillScreen) {
    std::default_random_engine generator(time(0));
    std::uniform_real_distribution<float> uniformPosition(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2);
    std::uniform_real_distribution<float> uniformSize(1, xSize);
    int numColumns = std::ceil(Vector2::ScreenSize.x / SPRITE_SIZE);
    // drawRect(0, speedFactor, Easing::Linear);
    auto columnXPositions = std::vector<int>();
    auto columnXSizes = std::vector<int>();
    if (fillScreen){
        while (ScreenIsNotFilled()) {
            columnXPositions.push_back((int)uniformPosition(generator));
            columnXSizes.push_back((int)uniformSize(generator));
        }
    }
    return 0;
}

void Drip::render() {
    std::cout << "Rendering Drip..." << std::endl;
    // drip to cover screen 04:04:168 - 04:44:074
    Drip(Time("04:04:168"), Time("04:44:074"), 1, 0, 1500).make(true);
    // 3D drip slower 05:39:000 - 06:06:000
    Drip(Time("05:39:000"), Time("06:06:000"), 1, 0, 4000).make(false);
}

