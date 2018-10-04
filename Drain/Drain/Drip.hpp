#pragma once
#include "Sketch.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include <vector>

class Drip {
public:
    // standalone, defined by pos Vector2
    Drip(const Time& startTime,
        const Time& endTime,
        const float xSize,
        const float xPos,   // center of the drip
        const float speedFactor);
    static void render();
	static void renderFirstFill();
	static void renderSecondDrips();

private:
	Sprite* drawRect(int offset,
					  float growDur,      // duration of drip in ms
					  Easing easing = Easing::Linear);
	int make(bool fillScreen);
	bool screenIsNotFilled();

    const Time startTime;
    const Time endTime;
    const float xSize;
    const float xPos;
    const float speedFactor;
	const int totalDur;
};