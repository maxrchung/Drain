#include "Swatch.hpp"
#include "Time.hpp"
#include "Timing.hpp"
#include <algorithm>
const Color Swatch::white = Color(255, 255, 255);
const Color Swatch::black = Color(0, 0, 0);
const Color Swatch::offwhite = Color(218, 236, 236);
const Color Swatch::water = Color(114, 187, 180);
const Color Swatch::blood = Color(170, 0, 0);
const Color Swatch::eerie = Color(27, 27, 27);
const std::vector<SwatchTiming> Swatch::bgTimings = {
	SwatchTiming(0, Time("00:27:093").ms, Swatch::offwhite, Swatch::offwhite),
	SwatchTiming(Time("00:27:093").ms, Time("00:35:018").ms, Swatch::offwhite, Swatch::water),
	SwatchTiming(Time("00:35:018").ms, Time("02:29:357").ms, Swatch::water, Swatch::water),
	SwatchTiming(Time("02:29:357").ms, Time("02:33:885").ms, Swatch::water, Swatch::eerie),
	SwatchTiming(Time("02:33:885").ms, Timing::songEnd, Swatch::eerie, Swatch::eerie),
};
const std::vector<SwatchTiming> Swatch::fgTimings = {
	SwatchTiming(0, Time("00:27:093").ms, Swatch::water, Swatch::water),
	SwatchTiming(Time("00:27:093").ms, Time("00:35:018").ms, Swatch::water, Swatch::offwhite),
	SwatchTiming(Time("00:35:018").ms, Time("02:29:357").ms, Swatch::offwhite, Swatch::offwhite),
	SwatchTiming(Time("02:29:357").ms, Time("02:33:885").ms, Swatch::offwhite, Swatch::blood),
	SwatchTiming(Time("02:33:885").ms, Timing::songEnd, Swatch::blood, Swatch::blood),
};
void Swatch::colorBgToBgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime) {
	colorSprites(sprites, startTime, endTime, bgTimings, bgTimings);
}
void Swatch::colorBgToFgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime) {
	colorSprites(sprites, startTime, endTime, bgTimings, fgTimings);
}
void Swatch::colorFgToBgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime) {
	colorSprites(sprites, startTime, endTime, fgTimings, bgTimings);
}
void Swatch::colorFgToFgSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime) {
	colorSprites(sprites, startTime, endTime, fgTimings, fgTimings);
}
void Swatch::colorSprites(const std::vector<Sprite*>& sprites, const int startTime, const int endTime, const std::vector<SwatchTiming>& startTimings, const std::vector<SwatchTiming>& endTimings) {
	// Find start timing
	const auto startIterator = std::find_if(startTimings.begin(), startTimings.end(), [startTime](const SwatchTiming& timing) {
		const auto contained = timing.contains(startTime);
		return contained;
	});
	const auto startIndex = startIterator - startTimings.begin();
	// Progress through timings and color depending on start/end times
	for (auto timing = startIndex; timing < startTimings.size(); ++timing) {
		const auto& startTiming = startTimings[timing];
		int localStartTime;
		if (startTime < startTiming.startTime) {
			localStartTime = startTiming.startTime;
		}
		else {
			localStartTime = startTime;
		}
		int localEndTime;
		bool endColoring;
		if (endTime > startTiming.endTime) {
			localEndTime = startTiming.endTime;
			endColoring = false;
		}
		else {
			localEndTime = endTime;
			endColoring = true;
		}
		const auto startColor = startTiming.getColor(localStartTime);
		const auto endColor = endTimings[timing].getColor(localEndTime);
		std::for_each(sprites.begin(), sprites.end(), [&](Sprite* const sprite) {
			sprite->Color(localStartTime, localEndTime, startColor, endColor);
		});
		if (endColoring) {
			break;
		}
	}
}
