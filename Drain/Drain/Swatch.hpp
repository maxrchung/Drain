#pragma once
#include "Color.hpp"
#include "RandomRange.hpp"
#include "Sprite.hpp"
#include "SwatchTiming.hpp"
#include <vector>
// Place colors that you plan on using into here
// In my original outline, I only planned for 4 main colors: white, blue, red, black, but this is always subject to change
class Swatch {
public:
	// Sets up random colors
	static void init();
	static void colorBgToBgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime);
	static void colorBgToFgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime);
	static void colorFgToBgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime);
	static void colorFgToFgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime);
private:
	// Pure white
	static const Color white;
	// Pure black
	static const Color black;
	// Eerie black 
	// you cant make this shit up https://en.wikipedia.org/wiki/Shades_of_black#Eerie_black
	static const Color eerie;
	// Blood red
	static const Color blood;
	// Hysteresis album cover white
	static const Color offwhite;
	// Hysteresis album color blue/green;
	static const Color water;
	static const std::vector<Color> colors;
	static const RandomRange randomColor;
	static void colorSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime, const std::vector<SwatchTiming>& startTimings, const std::vector<SwatchTiming>& endTimings);
	static Color getRandomColor(const std::vector<Color>& exceptions);
	static std::vector<SwatchTiming> bgTimings;
	static std::vector<SwatchTiming> fgTimings;
};