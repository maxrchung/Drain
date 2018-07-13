#pragma once
#include "Color.hpp"
#include "Sprite.hpp"
#include "SwatchTiming.hpp"
#include <vector>
// Place colors that you plan on using into here
// In my original outline, I only planned for 4 main colors: white, blue, red, black, but this is always subject to change
class Swatch {
public:
	static void colorBgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime);
	static void colorFgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime);
	// Pure white
	static const Color white;
	// Pure black
	static const Color black;
	// Hysteresis album cover white
	static const Color offwhite;
	// Hysteresis album color blue/green;
	static const Color water;
private:
	static void colorSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime, const std::vector<SwatchTiming>& timings);
	static const std::vector<SwatchTiming> bgTimings;
	static const std::vector<SwatchTiming> fgTimings;
};