#include "Drip.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include <random>
#include <ctime>

Drip::Drip(const Time& startTime, const Time& endTime,
    const float size, const Vector2 centerPos)
    : startTime{ startTime }, endTime{ endTime },
    sizeFactor{ size }, centerPos{ centerPos }
{
    totalDur = endTime.ms - startTime.ms;
}

// returns and draws a single circle at pos after offset ms
Sprite * Drip::draw(Vector2 pos, int offset, float size,
    float fadeInDur, float fadeFrom, float fadeTo, float growDur, float growFromSize, Easing easing)
{
    auto s = Storyboard::CreateSprite(getPath(Path::Circle), pos);
    if (growDur != 0) {
        if (startTime.ms + offset + growDur < endTime.ms)
            s->Scale(startTime.ms + offset, startTime.ms + offset + growDur, size * growFromSize, size, easing);
        else
            s->Scale(startTime.ms + offset, endTime.ms, size * growFromSize, size, easing);
    }
    else
        s->Scale(startTime.ms + offset, startTime.ms + offset, size, size); // scale to proper size instantaneously
    if (fadeInDur != 0) {
        if (startTime.ms + offset + fadeInDur < endTime.ms)
            s->Fade(startTime.ms + offset, startTime.ms + offset + fadeInDur, fadeFrom, fadeTo, easing);
        else
            s->Fade(startTime.ms + offset, endTime.ms, fadeFrom, fadeTo, easing);
    }
    Swatch::colorFgToFgSprites({ s }, startTime.ms + offset, endTime.ms); // color will determine Sprite lifetime
    return s;
}

// returns number of sprites drawn
int Drip::make() {

    return 0;
}

void Drip::render() {
    std::cout << "Rendering Drip..." << std::endl;
    // drip to cover screen 04:04:168 - 04:44:074
    // 3D drip 05:39:000 - 06:06:000
}

