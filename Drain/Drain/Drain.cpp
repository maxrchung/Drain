#include "Bubble.hpp"
#include "BubbleGenerator.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "RainGenerator.hpp"
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

	// Gets rid of beatmap background
	Storyboard::CreateSprite("36592_serial_experiments_lain.jpg", Vector2::Zero, Layer::Background);
	// Solid color background
	auto const background = Storyboard::CreateSprite(getPath(Path::Pixel), Vector2::Zero, Layer::Background);
	background->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize, Easing::Linear, 0);
	Swatch::colorBgToBgSprites({ background }, 0, Timing::songEnd);
		
	//Text::render();
	//Sketch::render(); 
	//Splatter::render();
	//Drip::render();
	
	// RainGenerator shit
	//RainGenerator firstRain = RainGenerator::RainGenerator(Time("00:05:580"), Time("00:51:716"));
	
	//Walker shit I guess
	if(0) {
		RainGenerator gen = RainGenerator(Time("01:03:319"), Time("01:30:489"), true, 1.03f);
		std::vector<Sprite *> raindrops = gen.FreezeRain();
		std::vector<SpriteCollection> coll_raindrops;
		for(auto drop: raindrops) {
			coll_raindrops.push_back(drop);
		}
		Walker walk_boi = Walker::Walker(coll_raindrops);
		walk_boi.walk(1000, Time("01:30:489"), Time("01:57:659"));
	}

	//testing bubbles
	if(0) {
		int start_time = Time("01:00:000").ms;
		int end_time = Time("02:00:000").ms;
		for(int i = 0; i < 5; ++i) {
			Bubble bub = Bubble(1);
			start_time += 5000;
			float rx = ((float)std::rand() / RAND_MAX) * Vector2::ScreenSize.x - (Vector2::ScreenSize.x / 2);
			float ry = ((float)std::rand() / RAND_MAX) * Vector2::ScreenSize.y - (Vector2::ScreenSize.y / 2);
			float sx = (i + 1) * 0.3;
			Vector2 start_pos = {i * 20.0f, i * 20.0f};
			Vector2 end_pos = {rx, ry};

			bub.Scale(start_time, start_time, sx, sx);
			bub.Move(start_time, end_time, start_pos, end_pos);

			bub.Color(start_time, end_time);
		}
	}

	// BubbleGenerator shit
	if (1) {
		BubbleGenerator bubGen = BubbleGenerator::BubbleGenerator();
		BubbleGenerator bubGen2 = BubbleGenerator::BubbleGenerator(true);
		BubbleGenerator::renderMouthBubbles();
	}

	if (1) {
		const auto bubbleCount = 10;
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
		Splatter::renderFirstGradualPop(bubbles);
	}

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}
