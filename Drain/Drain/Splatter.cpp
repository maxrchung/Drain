#include "Splatter.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include <random>
#include <ctime>

// standalone, defined by centerPos Vector2
Splatter::Splatter(const Time& startTime, const Time& endTime,
    const float size, const int numDrops, const Vector2 centerPos)
    : startTime{ startTime }, endTime{ endTime },
    sizeFactor{ size }, numDrops{ numDrops }, centerPos { centerPos }
{
    totalDur = endTime.ms - startTime.ms;
}

// position defined by existing AirBubble
Splatter::Splatter(const Time& startTime, const Time& endTime,
    const float size, const int numDrops, const Sketch * bubble)   // replace with AirBubble
    : Splatter(startTime, endTime, size, numDrops, Vector2(0,0))   // replace 0,0 with bubble->loc
{
}

// returns and draws a single circle at pos after offset ms
Sprite * Splatter::draw(Vector2 pos, int offset, float size,
    float fadeInDur, float fadeFrom, float growDur, float growFromSize, Easing easing)
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
    if (fadeInDur != 0){
        if (startTime.ms + offset + fadeInDur < endTime.ms)
            s->Fade(startTime.ms + offset, startTime.ms + offset + fadeInDur, fadeFrom, 1, easing);
        else
            s->Fade(startTime.ms + offset, endTime.ms, fadeFrom, 1, easing);
    }
    Swatch::colorFgToFgSprites({ s }, startTime.ms + offset, endTime.ms); // color will determine Sprite lifetime
    return s;
}

// returns number of sprites drawn, going for something like this: http://gifimage.net/splatter-gif-10/
int Splatter::make() {
    // main droplet will grow from 80% to 100% of its size over 1/2 of its lifespan
    auto centerPoint = draw(centerPos, 0, sizeFactor, 0, 0, totalDur * 0.5, 0.8, Easing::EasingOut);
    int ans = 1;
    std::default_random_engine generator(time(0));
    std::exponential_distribution<double> exp(3.5);    // mean of the exp distribution = 1 / 3.5
    std::normal_distribution<double> normal(4.5, 4.1); // mean, std dev
    std::normal_distribution<double> normal2(4.5, 4.2); // mean, std dev
    std::uniform_real_distribution<double> uniform(-1, 1); // uniform distribution between -1 and 1
    for (int i = 1; i < numDrops; i++) {
        // offset 'easing' is an exponential exp
        auto expRandomPoint = exp(generator);
        auto normalRP = normal(generator);
        auto normalRP2 = normal2(generator);
        auto neg3 = (uniform(generator) > 0) ? 1 : -1;
        while (expRandomPoint > 1.0) {  // in the off chance that RNG returns more than 1, roll again
            expRandomPoint = exp(generator);
        }
        auto offset = expRandomPoint * 2200; // satellite droplets will spawn in for 2 seconds
        offset -= 200;  // shift left 200ms
        if (offset < 0) {
            offset = 0; // so we can have some satellites spawn instantly
        }
        // distance from centerPos increases as offset increases
        // some randomness for the satellite droplet positions
        auto neg = uniform(generator);
        auto neg2 = uniform(generator);
        auto pos = centerPos + Vector2(neg * normalRP, neg2 * normalRP2) * expRandomPoint * neg3 / sizeFactor / sizeFactor;
        // size decreases as distance increases
        auto size = sizeFactor / centerPos.DistanceBetween(pos) * 2;
        if (size > 0.25 * sizeFactor) {
            size = 0.25 * sizeFactor;
        }
        if (size < 0.01 || pos.DistanceBetween(centerPos) < sizeFactor * 40) {
            continue;   // calculated satellite droplet is miniscule or is completely engulfed by the centerPoint
        }
        draw(pos, static_cast<int>(offset), size, offset, 0.4);
        ans++;
    }
    std::cout << ans << std::endl;
    return ans;
}

void Splatter::render() {
    std::cout << "Rendering Splatter..." << std::endl;
    // sprite size is 100px radius circle, sizeFactor scales this size, so 0.2 = 20px radius
    // numDrops is an upper bound
    Splatter(Time("04:00:000"), Time("04:05:000"), 0.3, 700, Vector2(50, 50)).make();
    Splatter(Time("04:02:000"), Time("04:05:000"), 0.2, 500, Vector2(-130, 0)).make();
}
