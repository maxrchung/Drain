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
const std::vector<Color> Swatch::colors = {
	offwhite,
	water,
	blood,
	eerie
};
const RandomRange Swatch::randomColor = RandomRange(0, colors.size() - 1);
std::vector<SwatchTiming> Swatch::bgTimings = {
	SwatchTiming(0, Time("00:27:093").ms, offwhite, offwhite),
	SwatchTiming(Time("00:27:093").ms, Time("00:35:018").ms, offwhite, water),
	SwatchTiming(Time("00:35:018").ms, Time("02:29:357").ms, water, water),
	SwatchTiming(Time("02:29:357").ms, Time("02:33:885").ms, water, eerie),
	SwatchTiming(Time("02:33:885").ms, Time("04:44:074").ms, eerie, eerie),
	SwatchTiming(Time("04:44:074").ms, Time("05:03:319").ms, blood, blood),
};
std::vector<SwatchTiming> Swatch::fgTimings = {
	SwatchTiming(0, Time("00:27:093").ms, water, water),
	SwatchTiming(Time("00:27:093").ms, Time("00:35:018").ms, water, offwhite),
	SwatchTiming(Time("00:35:018").ms, Time("02:29:357").ms, offwhite, offwhite),
	SwatchTiming(Time("02:29:357").ms, Time("02:33:885").ms, offwhite, blood),
	SwatchTiming(Time("02:33:885").ms, Time("04:44:074").ms, blood, blood),
	SwatchTiming(Time("04:44:074").ms, Time("05:03:319").ms, eerie, eerie),
};
void Swatch::init() {
	int endTime;
	auto currentBgColor = blood;
	auto currentFgColor = eerie;
	for (auto time = static_cast<float>(Time("05:03:319").ms); time < Time("05:20:867").ms; time += Timing::whole) {
		const auto startTime = static_cast<int>(time);
		endTime = startTime + Timing::whole;
		currentBgColor = getRandomColor({ currentBgColor });
		bgTimings.push_back(SwatchTiming(startTime, endTime, currentBgColor, currentBgColor));
		currentFgColor = getRandomColor({ currentBgColor, currentFgColor });
		fgTimings.push_back(SwatchTiming(startTime, endTime, currentFgColor, currentFgColor));
	}
	const auto nextBgColor = getRandomColor({ currentBgColor });
	const auto nextFgColor = getRandomColor({ nextBgColor, currentFgColor });
	bgTimings.push_back(SwatchTiming(endTime, Time("05:39:546").ms, currentBgColor, nextBgColor));
	fgTimings.push_back(SwatchTiming(endTime, Time("05:39:546").ms, currentFgColor, nextFgColor));
	currentBgColor = nextBgColor;
	currentFgColor = nextFgColor;
	for (auto time = static_cast<float>(Time("05:39:546").ms); time < Time("05:57:659").ms; time += Timing::quarter) {
		const auto startTime = static_cast<int>(time);
		endTime = startTime + Timing::quarter;
		currentBgColor = getRandomColor({ currentBgColor });
		bgTimings.push_back(SwatchTiming(startTime, endTime, currentBgColor, currentBgColor));
		currentFgColor = getRandomColor({ currentBgColor, currentFgColor });
		fgTimings.push_back(SwatchTiming(startTime, endTime, currentFgColor, currentFgColor));
	}
	// Floating point error :(
	const auto error = 5;
	for (auto time = endTime; time < Time("06:22:565").ms - error; time += Timing::whole * 4) {
		auto startTime = static_cast<int>(time);
		endTime = startTime + Timing::half;
		currentBgColor = getRandomColor({ currentBgColor });
		bgTimings.push_back(SwatchTiming(startTime, endTime, currentBgColor, currentBgColor));
		currentFgColor = getRandomColor({ currentBgColor, currentFgColor });
		fgTimings.push_back(SwatchTiming(startTime, endTime, currentFgColor, currentFgColor));
		startTime = endTime;
		endTime = time + Timing::whole * 4;
		currentBgColor = getRandomColor({ currentBgColor });
		bgTimings.push_back(SwatchTiming(startTime, endTime, currentBgColor, currentBgColor));
		currentFgColor = getRandomColor({ currentBgColor, currentFgColor });
		fgTimings.push_back(SwatchTiming(startTime, endTime, currentFgColor, currentFgColor));
	}
	bgTimings.push_back(SwatchTiming(endTime, Time("06:31:055").ms, currentBgColor, white));
	fgTimings.push_back(SwatchTiming(endTime, Time("06:31:055").ms, currentFgColor, black));
	bgTimings.push_back(SwatchTiming(Time("06:31:055").ms, Timing::songEnd, white, white));
	fgTimings.push_back(SwatchTiming(Time("06:31:055").ms, Timing::songEnd, black, black));
}
Color Swatch::getRandomColor(const std::vector<Color>& exceptions) {
	Color color;
	while (true) {
		color = colors[randomColor.calculate()];
		if (std::find(exceptions.begin(), exceptions.end(), color) == exceptions.end()) {
			return color;
		}
	}
}
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
	for (auto index = startIndex; index < startTimings.size(); ++index) {
		const auto& timing = startTimings[index];
		int localStartTime;
		if (startTime < timing.startTime) {
			localStartTime = timing.startTime;
		}
		else {
			localStartTime = startTime;
		}
		int localEndTime;
		bool endColoring;
		if (endTime >= timing.endTime) {
			localEndTime = timing.endTime;
			endColoring = false;
		}
		else {
			localEndTime = endTime;
			endColoring = true;
		}
		const auto startColor = timing.getColor(localStartTime);
		const auto endColor = endTimings[index].getColor(localEndTime);
		std::for_each(sprites.begin(), sprites.end(), [&](Sprite* const sprite) {
			sprite->Color(localStartTime, localEndTime, startColor, endColor);
		});
		if (endColoring) {
			break;
		}
	}
}
