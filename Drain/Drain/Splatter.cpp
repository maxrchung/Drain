#include "Splatter.hpp"
#include "Storyboard.hpp"

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

void Splatter::draw() {

}

void Splatter::render() {
    Splatter(Time("00:00:900"), Time("00:04:200"), 10.5, 20, Easing::Linear, Vector2(50, 50)).draw();
}
