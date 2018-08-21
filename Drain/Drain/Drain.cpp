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

	// RainGenerator shit
	//RainGenerator::RainGenerator(Time("00:05:58"), Time("00:51:71"));
	
	//Walker shit I guess
	if(0) { //lmao
		RainGenerator gen = RainGenerator(Time("01:03:32"), Time("01:31:00"), true, 1.03f);
		std::vector<Sprite *> raindrops = gen.FreezeRain();
		Walker walk_boi = Walker::Walker(raindrops);
		walk_boi.walk(50, Time("01:32:00").ms, Time("01:42:00").ms);
	}

	// BubbleGenerator shit
	//BubbleGenerator::BubbleGenerator();

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}
