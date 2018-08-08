#include "Splatter.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

// standalone, defined by pos Vector2
Splatter::Splatter(const Time& startTime, const Time& endTime,
    const float size, const int numDrops, const Vector2 pos)
    : startTime{ startTime }, endTime{ endTime },
    sizeFactor{ size }, numDrops{ numDrops }, pos { pos }
{
    visDur = endTime.ms - startTime.ms;
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
    if (growDur != 0)
        s->Scale(startTime.ms + offset, startTime.ms + offset + growDur, size * growFromSize, size, easing);
    else
        s->Scale(startTime.ms + offset, startTime.ms + offset, size, size); // scale to proper size instantaneously
    if (fadeInDur != 0)
        s->Fade(startTime.ms + offset, startTime.ms + offset + fadeInDur, fadeFrom, 1, easing);
    Swatch::colorFgToFgSprites({ s }, startTime.ms, endTime.ms); // color will determine Sprite lifetime
    return s;
}

// returns number of sprites drawn, going for something like this: http://gifimage.net/splatter-gif-10/
int Splatter::make() {
    // main droplet will grow from 80% to 100% of its size over 3/4 of its lifespan
    auto centerPoint = draw(pos, 0, sizeFactor, 0, 0, (endTime.ms - startTime.ms) * 0.75, 0.8, Easing::EasingOut);
    int ans = 1;
    // todo: add satellite drops to emulate bleeding from centerPoint
    for (int i = 1; i < numDrops; i++) {
        // todo: easing for offset
        // do my magic here

    }
    std::cout << ans << std::endl;
    return ans;
}

void Splatter::render() {
    std::cout << "Rendering Splatter..." << std::endl;
    Splatter(Time("00:00:900"), Time("00:04:200"), 0.5, 20, Vector2(50, 50)).make();
}
