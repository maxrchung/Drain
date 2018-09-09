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
		
	/*
	Text::render();
	Sketch::render();
	Splatter::render();
	Drip::render();
	*/
	// RainGenerator shit
	RainGenerator firstRain = RainGenerator::RainGenerator(Time("00:05:580"), Time("00:51:716"));
	Swatch::colorFgToBgSprites(firstRain.sprites, Time("00:05:580").ms, Time("00:51:716").ms);
	
	//Walker shit I guess
	if(1) {
		RainGenerator gen = RainGenerator(Time("01:03:319"), Time("01:30:489"), true, 1.03f);
		Swatch::colorFgToBgSprites(gen.sprites, Time("01:03:319").ms, Time("01:30:489").ms);
		std::vector<Sprite *> raindrops = gen.FreezeRain();
		std::vector<SpriteCollection> coll_raindrops;
		for(auto drop: raindrops) {
			coll_raindrops.push_back(drop);
		}
		Walker walk_boi = Walker::Walker(coll_raindrops);
		walk_boi.walk(1000, Time("01:30:489"), Time("01:57:659"));
	}

	// BubbleGenerator shit
#if 1
	BubbleGenerator bubGen = BubbleGenerator::BubbleGenerator();
	Swatch::colorFgToBgSprites(bubGen.sprites, Time("01:58:790").ms, Time("02:33:890").ms);
	std::vector<Sprite *> bubbles = bubGen.GetSplatBubbles();

	// mouth bubble tests
	Vector2 pos = { 50, 50 };
	BubbleGenerator::BubbleGenerator(true, pos, Time("02:10:790"));
	BubbleGenerator::BubbleGenerator(true, pos, Time("01:10:790"));
#endif

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}
