#pragma once
#include <vector>
#include "Vector2.hpp"
#include "Time.hpp"
#include "Sketch.hpp"

class Splatter
{
public:
    // standalone, defined by pos Vector2
    Splatter(const Time& startTime,
        const Time& endTime,
        const float size,
        const int numDrops,
        const Easing& easing,
        const Vector2 pos);
    // position defined by existing AirBubble
    Splatter(const Time& startTime,
             const Time& endTime,
             const float size,
             const int numDrops,
             const Easing& easing,
             const Sketch * bubble);   // Sketch is a placeholder, replace with AirBubble
    static void render();
private:
    const Time startTime;
    const Time endTime;
    const Vector2 pos;
    const float size;
    const int numDrops;
    const Easing easing;
    const Sketch * bubble;   // replace with AirBubble
    void draw();
};

