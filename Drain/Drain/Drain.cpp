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
		for(int i = 0; i < 20; ++i) {
			Bubble bub = Bubble();
			start_time += 5000;
			float rx = ((float)std::rand() / RAND_MAX) * Vector2::ScreenSize.x - (Vector2::ScreenSize.x / 2);
			float ry = ((float)std::rand() / RAND_MAX) * Vector2::ScreenSize.y - (Vector2::ScreenSize.y / 2);
			float sx = ((float)std::rand() / RAND_MAX) * 2;
			float sy = ((float)std::rand() / RAND_MAX) * 2;
			Vector2 start_pos = {0, -100};
			bub.MoveY(start_time, end_time, start_pos.y, Vector2::ScreenSize.y);
			float rtemp = rx;
			for(int j = 0; j < 100; j += 2) {
				rx = rtemp/2;
				bub.MoveX(start_time + j * 500, start_time + (j + 1) * 500, -rx, rx, Easing::SineInOut);
				bub.MoveX(start_time + (j + 1) * 500, start_time + (j + 2) * 500, rx, -rx, Easing::SineInOut);
			}

			bub.Scale(start_time, start_time, 0.2, 0.2);
			bub.Color(start_time, end_time);
		}
	}

	// BubbleGenerator shit
	if (1) {
		BubbleGenerator bubGen = BubbleGenerator::BubbleGenerator();
		BubbleGenerator bubGen2 = BubbleGenerator::BubbleGenerator(true);
	}

	BubbleGenerator::renderMouthBubbles();

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}
