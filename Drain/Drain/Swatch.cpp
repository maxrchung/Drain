#include "Swatch.hpp"
#include <algorithm>
const std::vector<SwatchTiming> Swatch::bgTimings = {
	SwatchTiming(0,10000,Color(125), Color(125))
};
const std::vector<SwatchTiming> Swatch::fgTimings = {

};
const Color Swatch::white = Color(255, 255, 255);
const Color Swatch::black = Color(0, 0, 0);
const Color Swatch::offwhite = Color(218, 236, 236);
const Color Swatch::water = Color(114, 187, 180);
void Swatch::colorBgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime) {
	colorSprites(sprites, startTime, endTime, bgTimings);
}
void Swatch::colorFgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime) {
	colorSprites(sprites, startTime, endTime, fgTimings);
}
void Swatch::colorSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime, const std::vector<SwatchTiming>& timings) {
	// Find start timing
	const auto startTiming = std::find_if(timings.begin(), timings.end(), [startTime](const SwatchTiming& timing) {
		const auto contained = timing.contains(startTime);
		return contained;
	});
	// Progress through timings and color depending on start/end times
	for (auto timing = startTiming; timing != timings.end(); timing++) {
		int localStartTime;
		if (startTime <= timing->startTime) {
			localStartTime = timing->startTime;
		}
		else {
			localStartTime = startTime;
		}
		int localEndTime;
		bool endColoring;
		if (endTime <= timing->endTime) {
			localEndTime = timing->endTime;
			endColoring = false;
		}
		else {
			localEndTime = endTime;
			endColoring = true;
		}
		const auto startColor = timing->getColor(localStartTime);
		const auto endColor = timing->getColor(localEndTime);
		std::for_each(sprites.begin(), sprites.end(), [&](Sprite* const sprite) {
			sprite->Color(startTime, endTime, startColor, endColor);
		});
		if (endColoring) {
			break;
		}
	}
}
