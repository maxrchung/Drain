#pragma once
#include <vector>
#include "Vector2.hpp"
#include "Time.hpp"
#include "Sketch.hpp"

class Drip
{
public:
    // standalone, defined by pos Vector2
    Drip(const Time& startTime,
        const Time& endTime,
        const float size,
        const Vector2 centerPos);
    static void render();
private:
    const Time startTime;
    const Time endTime;
    int totalDur;
    const Vector2 centerPos;
    const float sizeFactor;
    const Sketch * bubble;   // replace with AirBubble
    Sprite * draw(Vector2 pos,
        int offset,
        float size,
        float fadeInDur = 0,    // duration of fade in ms
        float fadeFrom = 0,     // origin opacity from 0 to 1
        float fadeTo = 1,     // destination opacity from 0 to 1
        float growDur = 0,      // duration of expansion in ms
        float growFrom = 0,     // origin size from 0 to 1
        Easing easing = Easing::Linear);
    int make();
};