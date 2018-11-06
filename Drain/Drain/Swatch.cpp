#include "Swatch.hpp"
#include "Timing.hpp"
#include <algorithm>
const Color Swatch::white = Color(255, 255, 255);
const Color Swatch::black = Color(0, 0, 0);
const Color Swatch::offwhite = Color(156, 184, 192);
const Color Swatch::water = Color(70, 101, 110);
const Color Swatch::blood = Color(170, 0, 0);
const Color Swatch::eerie = Color(27, 27, 27);
const std::vector<Color> Swatch::colors = {
	offwhite,
	water,
	blood,
	eerie
};
const RandomRange Swatch::randomColor = RandomRange(0, colors.size() - 1);
const std::vector<Time> Swatch::fastTimes = {
	Time("05:39:546").ms,
	Time("05:39:829").ms,
	Time("05:40:112").ms,
	Time("05:40:395").ms,
	Time("05:40:678").ms,
	Time("05:41:244").ms,
	Time("05:41:810").ms,
	Time("05:42:093").ms,
	Time("05:42:376").ms,
	Time("05:42:659").ms,
	Time("05:42:942").ms,
	Time("05:43:508").ms,
	Time("05:43:650").ms,
	Time("05:43:791").ms,
	Time("05:43:933").ms,
	Time("05:44:074").ms,
	Time("05:44:357").ms,
	Time("05:44:640").ms,
	Time("05:44:923").ms,
	Time("05:45:206").ms,
	Time("05:45:772").ms,
	Time("05:46:338").ms,
	Time("05:46:480").ms,
	Time("05:46:621").ms,
	Time("05:46:763").ms,
	Time("05:46:904").ms,
	Time("05:47:187").ms,
	Time("05:47:470").ms,
	Time("05:47:895").ms,
	Time("05:48:036").ms,
	Time("05:48:602").ms,
	Time("05:48:885").ms,
	Time("05:49:168").ms,
	Time("05:49:452").ms,
	Time("05:49:735").ms,
	Time("05:50:301").ms,
	Time("05:50:867").ms,
	Time("05:51:150").ms,
	Time("05:51:433").ms,
	Time("05:51:716").ms,
	Time("05:51:999").ms,
	Time("05:52:565").ms,
	Time("05:52:706").ms,
	Time("05:52:848").ms,
	Time("05:52:989").ms,
	Time("05:53:131").ms,
	Time("05:53:414").ms,
	Time("05:53:697").ms,
	Time("05:53:980").ms,
	Time("05:54:263").ms,
	Time("05:54:829").ms,
	Time("05:55:395").ms,
	Time("05:55:536").ms,
	Time("05:55:678").ms,
	Time("05:55:819").ms,
	Time("05:55:961").ms,
	Time("05:56:244").ms,
	Time("05:56:527").ms,
	Time("05:56:952").ms,
	Time("05:57:093").ms,
};
std::vector<SwatchTiming> Swatch::bgTimings = {
	SwatchTiming(0, Time("00:27:093").ms, offwhite, offwhite),
	SwatchTiming(Time("00:27:093").ms, Time("00:35:018").ms, offwhite, water),
	SwatchTiming(Time("00:35:018").ms, Time("00:54:263").ms, water, water),
	SwatchTiming(Time("00:54:263").ms, Time("01:03:319").ms, water, eerie),

	SwatchTiming(Time("01:03:319").ms, Time("01:03:602").ms, water, water),
	SwatchTiming(Time("01:03:602").ms, Time("01:05:584").ms, eerie, eerie),

	SwatchTiming(Time("01:05:584").ms, Time("01:05:867").ms, water, water),
	SwatchTiming(Time("01:05:867").ms, Time("01:07:848").ms, eerie, eerie),

	SwatchTiming(Time("01:07:848").ms, Time("01:08:131").ms, water, water),
	SwatchTiming(Time("01:08:131").ms, Time("01:10:112").ms, eerie, eerie),

	SwatchTiming(Time("01:10:112").ms, Time("01:10:301").ms, water, water),
	SwatchTiming(Time("01:10:301").ms, Time("01:10:489").ms, eerie, eerie),
	SwatchTiming(Time("01:10:489").ms, Time("01:10:678").ms, water, water),
	SwatchTiming(Time("01:10:678").ms, Time("01:10:867").ms, eerie, eerie),
	SwatchTiming(Time("01:10:867").ms, Time("01:11:055").ms, water, water),
	SwatchTiming(Time("01:11:055").ms, Time("01:11:244").ms, eerie, eerie),
	SwatchTiming(Time("01:11:244").ms, Time("01:11:433").ms, water, water),
	SwatchTiming(Time("01:11:433").ms, Time("01:11:621").ms, eerie, eerie),
	SwatchTiming(Time("01:11:621").ms, Time("01:11:810").ms, water, water),
	SwatchTiming(Time("01:11:810").ms, Time("01:11:999").ms, eerie, eerie),
	SwatchTiming(Time("01:11:999").ms, Time("01:12:187").ms, water, water),
	SwatchTiming(Time("01:12:187").ms, Time("01:12:376").ms, eerie, eerie),

	SwatchTiming(Time("01:12:376").ms, Time("01:12:659").ms, water, water),
	SwatchTiming(Time("01:12:659").ms, Time("01:14:640").ms, eerie, eerie),

	SwatchTiming(Time("01:14:640").ms, Time("01:14:923").ms, water, water),
	SwatchTiming(Time("01:14:923").ms, Time("01:16:904").ms, eerie, eerie),

	SwatchTiming(Time("01:16:904").ms, Time("01:17:187").ms, water, water),
	SwatchTiming(Time("01:17:187").ms, Time("01:19:168").ms, eerie, eerie),

	SwatchTiming(Time("01:19:168").ms, Time("01:19:357").ms, water, water),
	SwatchTiming(Time("01:19:357").ms, Time("01:19:546").ms, eerie, eerie),
	SwatchTiming(Time("01:19:546").ms, Time("01:19:735").ms, water, water),
	SwatchTiming(Time("01:19:735").ms, Time("01:19:923").ms, eerie, eerie),
	SwatchTiming(Time("01:19:923").ms, Time("01:20:112").ms, water, water),
	SwatchTiming(Time("01:20:112").ms, Time("01:20:301").ms, eerie, eerie),
	SwatchTiming(Time("01:20:301").ms, Time("01:20:489").ms, water, water),
	SwatchTiming(Time("01:20:489").ms, Time("01:20:678").ms, eerie, eerie),
	SwatchTiming(Time("01:20:678").ms, Time("01:20:867").ms, water, water),
	SwatchTiming(Time("01:20:867").ms, Time("01:21:055").ms, eerie, eerie),
	SwatchTiming(Time("01:21:055").ms, Time("01:21:244").ms, water, water),
	SwatchTiming(Time("01:21:244").ms, Time("01:21:433").ms, eerie, eerie),

	SwatchTiming(Time("01:21:433").ms, Time("01:21:716").ms, water, water),
	SwatchTiming(Time("01:21:716").ms, Time("01:23:697").ms, eerie, eerie),

	SwatchTiming(Time("01:23:697").ms, Time("01:23:980").ms, water, water),
	SwatchTiming(Time("01:23:980").ms, Time("01:25:961").ms, eerie, eerie),

	SwatchTiming(Time("01:25:961").ms, Time("01:26:244").ms, water, water),
	SwatchTiming(Time("01:26:244").ms, Time("01:28:225").ms, eerie, eerie),

	SwatchTiming(Time("01:28:225").ms, Time("01:28:414").ms, water, water),
	SwatchTiming(Time("01:28:414").ms, Time("01:28:602").ms, eerie, eerie),
	SwatchTiming(Time("01:28:602").ms, Time("01:28:791").ms, water, water),
	SwatchTiming(Time("01:28:791").ms, Time("01:28:980").ms, eerie, eerie),
	SwatchTiming(Time("01:28:980").ms, Time("01:29:168").ms, water, water),
	SwatchTiming(Time("01:29:168").ms, Time("01:29:357").ms, eerie, eerie),
	SwatchTiming(Time("01:29:357").ms, Time("01:29:546").ms, water, water),
	SwatchTiming(Time("01:29:546").ms, Time("01:29:735").ms, eerie, eerie),
	SwatchTiming(Time("01:29:735").ms, Time("01:29:923").ms, water, water),
	SwatchTiming(Time("01:29:923").ms, Time("01:30:112").ms, eerie, eerie),
	SwatchTiming(Time("01:30:112").ms, Time("01:30:301").ms, water, water),
	SwatchTiming(Time("01:30:301").ms, Time("01:30:489").ms, eerie, eerie),

	SwatchTiming(Time("01:30:489").ms, Time("02:29:357").ms, water, water),

	SwatchTiming(Time("02:29:357").ms, Time("02:33:885").ms, water, eerie),
	SwatchTiming(Time("02:33:885").ms, Time("03:18:036").ms, eerie, eerie),
	SwatchTiming(Time("03:18:036").ms, Time("03:19:168").ms, eerie, offwhite),
	SwatchTiming(Time("03:19:168").ms, Time("04:44:074").ms, offwhite, offwhite),
	SwatchTiming(Time("04:44:074").ms, Time("05:03:319").ms, blood, blood),
};
std::vector<SwatchTiming> Swatch::fgTimings = {
	SwatchTiming(0, Time("00:27:093").ms, water, water),
	SwatchTiming(Time("00:27:093").ms, Time("00:35:018").ms, water, offwhite),
	SwatchTiming(Time("00:35:018").ms, Time("00:54:263").ms, offwhite, offwhite),
	SwatchTiming(Time("00:54:263").ms, Time("01:03:319").ms, offwhite, offwhite),

	SwatchTiming(Time("01:03:319").ms, Time("01:03:602").ms, offwhite, offwhite),
	SwatchTiming(Time("01:03:602").ms, Time("01:05:584").ms, offwhite, offwhite),

	SwatchTiming(Time("01:05:584").ms, Time("01:05:867").ms, offwhite, offwhite),
	SwatchTiming(Time("01:05:867").ms, Time("01:07:848").ms, offwhite, offwhite),

	SwatchTiming(Time("01:07:848").ms, Time("01:08:131").ms, offwhite, offwhite),
	SwatchTiming(Time("01:08:131").ms, Time("01:10:112").ms, offwhite, offwhite),

	SwatchTiming(Time("01:10:112").ms, Time("01:10:301").ms, offwhite, offwhite),
	SwatchTiming(Time("01:10:301").ms, Time("01:10:489").ms, offwhite, offwhite),
	SwatchTiming(Time("01:10:489").ms, Time("01:10:678").ms, offwhite, offwhite),
	SwatchTiming(Time("01:10:678").ms, Time("01:10:867").ms, offwhite, offwhite),
	SwatchTiming(Time("01:10:867").ms, Time("01:11:055").ms, offwhite, offwhite),
	SwatchTiming(Time("01:11:055").ms, Time("01:11:244").ms, offwhite, offwhite),
	SwatchTiming(Time("01:11:244").ms, Time("01:11:433").ms, offwhite, offwhite),
	SwatchTiming(Time("01:11:433").ms, Time("01:11:621").ms, offwhite, offwhite),
	SwatchTiming(Time("01:11:621").ms, Time("01:11:810").ms, offwhite, offwhite),
	SwatchTiming(Time("01:11:810").ms, Time("01:11:999").ms, offwhite, offwhite),
	SwatchTiming(Time("01:11:999").ms, Time("01:12:187").ms, offwhite, offwhite),
	SwatchTiming(Time("01:12:187").ms, Time("01:12:376").ms, offwhite, offwhite),

	SwatchTiming(Time("01:12:376").ms, Time("01:12:659").ms, offwhite, offwhite),
	SwatchTiming(Time("01:12:659").ms, Time("01:14:640").ms, offwhite, offwhite),

	SwatchTiming(Time("01:14:640").ms, Time("01:14:923").ms, offwhite, offwhite),
	SwatchTiming(Time("01:14:923").ms, Time("01:16:904").ms, offwhite, offwhite),

	SwatchTiming(Time("01:16:904").ms, Time("01:17:187").ms, offwhite, offwhite),
	SwatchTiming(Time("01:17:187").ms, Time("01:19:168").ms, offwhite, offwhite),

	SwatchTiming(Time("01:19:168").ms, Time("01:19:357").ms, offwhite, offwhite),
	SwatchTiming(Time("01:19:357").ms, Time("01:19:546").ms, offwhite, offwhite),
	SwatchTiming(Time("01:19:546").ms, Time("01:19:735").ms, offwhite, offwhite),
	SwatchTiming(Time("01:19:735").ms, Time("01:19:923").ms, offwhite, offwhite),
	SwatchTiming(Time("01:19:923").ms, Time("01:20:112").ms, offwhite, offwhite),
	SwatchTiming(Time("01:20:112").ms, Time("01:20:301").ms, offwhite, offwhite),
	SwatchTiming(Time("01:20:301").ms, Time("01:20:489").ms, offwhite, offwhite),
	SwatchTiming(Time("01:20:489").ms, Time("01:20:678").ms, offwhite, offwhite),
	SwatchTiming(Time("01:20:678").ms, Time("01:20:867").ms, offwhite, offwhite),
	SwatchTiming(Time("01:20:867").ms, Time("01:21:055").ms, offwhite, offwhite),
	SwatchTiming(Time("01:21:055").ms, Time("01:21:244").ms, offwhite, offwhite),
	SwatchTiming(Time("01:21:244").ms, Time("01:21:433").ms, offwhite, offwhite),

	SwatchTiming(Time("01:21:433").ms, Time("01:21:716").ms, offwhite, offwhite),
	SwatchTiming(Time("01:21:716").ms, Time("01:23:697").ms, offwhite, offwhite),

	SwatchTiming(Time("01:23:697").ms, Time("01:23:980").ms, offwhite, offwhite),
	SwatchTiming(Time("01:23:980").ms, Time("01:25:961").ms, offwhite, offwhite),

	SwatchTiming(Time("01:25:961").ms, Time("01:26:244").ms, offwhite, offwhite),
	SwatchTiming(Time("01:26:244").ms, Time("01:28:225").ms, offwhite, offwhite),

	SwatchTiming(Time("01:28:225").ms, Time("01:28:414").ms, offwhite, offwhite),
	SwatchTiming(Time("01:28:414").ms, Time("01:28:602").ms, offwhite, offwhite),
	SwatchTiming(Time("01:28:602").ms, Time("01:28:791").ms, offwhite, offwhite),
	SwatchTiming(Time("01:28:791").ms, Time("01:28:980").ms, offwhite, offwhite),
	SwatchTiming(Time("01:28:980").ms, Time("01:29:168").ms, offwhite, offwhite),
	SwatchTiming(Time("01:29:168").ms, Time("01:29:357").ms, offwhite, offwhite),
	SwatchTiming(Time("01:29:357").ms, Time("01:29:546").ms, offwhite, offwhite),
	SwatchTiming(Time("01:29:546").ms, Time("01:29:735").ms, offwhite, offwhite),
	SwatchTiming(Time("01:29:735").ms, Time("01:29:923").ms, offwhite, offwhite),
	SwatchTiming(Time("01:29:923").ms, Time("01:30:112").ms, offwhite, offwhite),
	SwatchTiming(Time("01:30:112").ms, Time("01:30:301").ms, offwhite, offwhite),
	SwatchTiming(Time("01:30:301").ms, Time("01:30:489").ms, offwhite, offwhite),

	SwatchTiming(Time("01:30:489").ms, Time("02:29:357").ms, offwhite, offwhite),

	SwatchTiming(Time("02:29:357").ms, Time("02:33:885").ms, offwhite, blood),
	SwatchTiming(Time("02:33:885").ms, Time("03:18:036").ms, blood, blood),
	SwatchTiming(Time("03:18:036").ms, Time("03:19:168").ms, blood, blood),
	SwatchTiming(Time("03:19:168").ms, Time("04:44:074").ms, blood, blood),
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
	for (auto i = 0; i < fastTimes.size(); ++i) {
		const auto startTime = fastTimes[i].ms;
		if (i == fastTimes.size() - 1) {
			endTime = Time("05:57:659").ms;
		}
		else {
			endTime = fastTimes[i + 1].ms;
		}
		currentBgColor = getRandomColor({ currentBgColor });
		bgTimings.push_back(SwatchTiming(startTime, endTime, currentBgColor, currentBgColor));
		currentFgColor = getRandomColor({ currentBgColor, currentFgColor });
		fgTimings.push_back(SwatchTiming(startTime, endTime, currentFgColor, currentFgColor));
	}
	for (auto time = Time("05:57:659").ms; time < Time("06:20:301").ms; time += Timing::whole * 4) {
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
	int startIndex;
	// Handle special case if startTime comes before first startTime
	if (startTime < startTimings[0].startTime) {
		startIndex = 0;
	}
	else {
		// Find start timing
		const auto startIterator = std::find_if(startTimings.begin(), startTimings.end(), [startTime](const SwatchTiming& timing) {
			const auto contained = timing.contains(startTime);
			return contained;
		});
		startIndex = startIterator - startTimings.begin();
	}
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
		if (endTime > timing.endTime) {
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
		if(startColor.r > 255 || startColor.g > 255 || startColor.b > 255) {
			printf("%d\n", endTime);
			std::cout << startColor.r << " " << startColor.g << " " << startColor.b << "\n";
		}
		if(endColor.r > 255 || endColor.g > 255 || endColor.b > 255) {
			printf("%d\n", endTime);
			std::cout << endColor.r << " " << startColor.g << " " << startColor.b << "\n";
		}
		if (endColoring) {
			break;
		}
	}
}
