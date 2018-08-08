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
        const Vector2 pos);
    // position defined by existing AirBubble
    Splatter(const Time& startTime,
        const Time& endTime,
        const float size,
        const int numDrops,
        const Sketch * bubble);   // Sketch is a placeholder, replace with AirBubble
    static void render();
private:
    const Time startTime;
    const Time endTime;
    int visDur;
    const Vector2 pos;
    const float sizeFactor;
    const int numDrops;
    const Sketch * bubble;   // replace with AirBubble
    Sprite * draw(Vector2 pos,
        int offset,
        float size,
        float fadeInDur = 0,    // duration of fade in ms
        float fadeFrom = 0,     // origin opacity from 0 to 1
        float growDur = 0,      // duration of expansion in ms
        float growFrom = 0,     // origin size from 0 to 1
        Easing easing = Easing::Linear);
    int make();
};

