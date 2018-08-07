#include "Splatter.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

// standalone, defined by pos Vector2
Splatter::Splatter(const Time& startTime, const Time& endTime,
    const float size, const int numDrops, const Easing& easing, const Vector2 pos)
    : startTime{ startTime }, endTime{ endTime },
    size{ size }, numDrops{ numDrops }, easing{ easing }, pos { pos }
{
}

// position defined by existing AirBubble
Splatter::Splatter(const Time& startTime, const Time& endTime,
    const float size, const int numDrops, const Easing& easing, const Sketch * bubble)   // replace with AirBubble
    : startTime{ startTime }, endTime{ endTime },
    size{ size }, numDrops{ numDrops }, easing{ easing }, bubble{ bubble }
{
}

// returns and draws a single circle at pos after offset ms
Sprite * Splatter::draw(Vector2 pos, int offset) {
    auto s = Storyboard::CreateSprite(getPath(Path::Circle), pos);
    s->Scale(startTime.ms + offset, endTime.ms, size, size);
    Swatch::colorFgToFgSprites({ s }, startTime.ms, startTime.ms);
    return s;
}

// returns number of sprites drawn, going for something like this: http://gifimage.net/splatter-gif-10/
int Splatter::make() {
    auto centerPoint = draw(pos, 0);
    int ans = 1;
    // todo: add bleeding from centerPoint
    for (int i = 1; i < numDrops; i++) {
        // todo: easing for offset
        // do my magic here

    }
    std::cout << ans << std::endl;
    return ans;
}

void Splatter::render() {
    std::cout << "Rendering Splatter..." << std::endl;
    Splatter(Time("00:00:900"), Time("00:04:200"), 0.5, 20, Easing::Linear, Vector2(50, 50)).make();
}
