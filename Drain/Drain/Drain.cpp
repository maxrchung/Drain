#include "Bubble.hpp"
#include "BubbleGenerator.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "RainGenerator.hpp"
#include "Rain_walker.hpp"
#include "Splatter_walker.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Sketch.hpp"
#include "Text.hpp"
#include "Walker.hpp"
#include "Splatter.hpp"
#include "Drip.hpp"

#include <ctime>
#include <cmath>
#include <iostream>

int main() {
	srand(time(NULL));
	Swatch::init();

	// Background
	if (1) {
		// Gets rid of beatmap background
		Storyboard::CreateSprite("36592_serial_experiments_lain.jpg", Vector2::Zero, Layer::Background);
		// Solid color background
		auto const background = Storyboard::CreateSprite(getPath(Path::Pixel), Vector2::Zero, Layer::Background);
		background->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize, Easing::Linear, 0);
		Swatch::colorBgToBgSprites({ background }, 0, Timing::songEnd);
	}

	// Bubble generation
	// Moved right above background so that text and sketch can appear normally above them
	if (0) {
		BubbleGenerator bubGen = BubbleGenerator::BubbleGenerator();
		BubbleGenerator bubGen2 = BubbleGenerator::BubbleGenerator(true);
		auto splatBubbles = bubGen.GetSplatBubbles();
		BubbleGenerator::renderMouthBubbles();
	}

	if (1) {
		BubbleGenerator::BubbleGenerator();
		RainGenerator(Time("02:55:580"), Time("03:10:716"));
		//Text::renderBanner();
		Sketch::renderBackground();
		Splatter::renderBackground();
		Drip::renderBackground();
	}

	//Text::render();

	//Sketch::render();

	// Rain
	if (0) {
		RainGenerator firstRain = RainGenerator::RainGenerator(Time("00:05:580"), Time("00:51:716"));
		RainGenerator gen = RainGenerator(Time("01:03:319"), Time("01:30:489"), true, 1.03f);
		std::vector<Sprite *> raindrops = gen.FreezeRain();
		std::vector<SpriteCollection> coll_raindrops;
		for (auto drop : raindrops) {
			coll_raindrops.push_back(drop);
		}

#if 0
		//Walker &walk_boi = Rain_walker(coll_raindrops);
		//walk_boi.walk(100000, Time("01:30:489"), Time("01:57:659"), 100);
#else
		//Walker *walk_boi = new Rain_walker(coll_raindrops);
		//walk_boi->walk(100000, Time("01:30:489"), Time("01:57:659"), 100);
#endif


	}

	// Testing bubbles
	if (0) {
		int start_time = Time("01:00:000").ms;
		int end_time = Time("02:00:000").ms;
		for (int i = 0; i < 5; ++i) {
			Bubble bub = Bubble(1);
			start_time += 5000;
			float rx = ((float)std::rand() / RAND_MAX) * Vector2::ScreenSize.x - (Vector2::ScreenSize.x / 2);
			float ry = ((float)std::rand() / RAND_MAX) * Vector2::ScreenSize.y - (Vector2::ScreenSize.y / 2);
			float sx = (i + 1) * 0.3;
			Vector2 start_pos = { i * 20.0f, i * 20.0f };
			Vector2 end_pos = { rx, ry };

			bub.Scale(start_time, start_time, sx, sx);
			bub.Move(start_time, end_time, start_pos, end_pos);

			bub.Color(start_time, end_time);
		}
	}

	// First splatter section
	if (0) {
		// Test bubble transition
		const auto bubbleCount = 19;
		auto bubbles = std::vector<Bubble*>(bubbleCount);
		for (int i = 0; i < bubbleCount; ++i) {
			bubbles[i] = new Bubble();
			const auto scale = RandomRange::calculate(25, 125, 100.0f);
			const auto startTime = Time("02:33:885").ms - 1000;
			const auto endTime = Time("02:33:885").ms;
			const auto position = Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200));
			bubbles[i]->Scale(startTime, startTime, scale, scale);
			bubbles[i]->Move(startTime,
				endTime,
				position, position);
		}

		// First splatter section
		Splatter::renderFirstGradualPop(bubbles);
	}

	// Second splatter section and walker
	if (0) {
		// Test bubble transition
		const auto bubbleCount = 19;
		auto bubbles = std::vector<Bubble*>(bubbleCount);
		for (int i = 0; i < bubbleCount; ++i) {
			bubbles[i] = new Bubble();
			const auto scale = RandomRange::calculate(25, 125, 100.0f);
			const auto startTime = Time("03:18:036").ms - 1000;
			const auto endTime = Time("03:18:036").ms;
			const auto position = Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200));
			bubbles[i]->Scale(startTime, startTime, scale, scale);
			bubbles[i]->Move(startTime,
				endTime,
				position, position);
		}

		// Second splatter section
		auto splatters = Splatter::renderSecondAllPop(bubbles);

		//Splatter_walker walk_splats = Splatter_walker(splatters);
		int start_splat = Time("03:19:168").ms;
		int end_splat = Time("04:04:168").ms;

		//Walker *walk_splats = new Splatter_walker(splatters);
		//walk_splats->walk(10000, start_splat, end_splat, 100);
		
		// Test splatter walker
		for (auto& splatter : splatters) {
			splatter.Move(Time("03:19:168").ms,
				Time("03:19:168").ms + 1000,
				splatter.position,
				splatter.position + Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200)));
		}

		// Testing makeWalkerSplatter
		for (int i = 0; i < 4; ++i) {
			auto splatter = Splatter::makeWalkerSplatter(Time("04:00:000"), Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200)), RandomRange::calculate(5, 10, 10));
			splatter.Move(Time("04:00:000").ms,
				Time("04:00:000").ms + 1000,
				splatter.position,
				splatter.position + Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200)));
		}
		
	}

	// Drip
	if (0) {
		// First drip section
		Drip::renderFirstFill();

		// Second drip section
		auto drips = Drip::renderSecondDrips();

		// Test drip walker
		for (auto& drip : drips) {
			drip.Move(Time("05:39:546").ms,
				Time("05:39:546").ms + 1000,
				drip.position,
				drip.position + Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200)));
		}

		// Test makeWalkerDrip
		for (int i = 0; i < 4; ++i) {
			auto drip = Drip::makeWalkerDrip(Time("05:00:000"), Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200)), RandomRange::calculate(20, 50));
			drip.Move(Time("05:00:000").ms,
				Time("05:00:000").ms + 1000,
				drip.position,
				drip.position + Vector2(RandomRange::calculate(-200, 200), RandomRange::calculate(-200, 200)));
		}
	}

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}
