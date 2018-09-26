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
        const float xSize,
        const float xPos,   // center of the drip
        const float speedFactor);
    static void render();
private:
    const Time startTime;
    const Time endTime;
    int totalDur;
    const float xSize;
    const float xPos;
    const float speedFactor;
    const Sketch * bubble;   // replace with AirBubble
    Sprite * drawRect(int offset,
        float growDur,      // duration of drip in ms
        Easing easing = Easing::Linear);
    int make(bool fillScreen);
    bool ScreenIsNotFilled();

};