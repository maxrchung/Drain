#include "Lyric.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Sketch.hpp"
#include "Walker.hpp"
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

	//Lyric::render();

	// idea: have the image gradually lower in resolution and fade away
	auto sketches = std::vector<Sketch>();
	sketches.push_back(Sketch("1.txt", Time("00:05:000"), Time("00:05:300"), 1, 3, true, Path::Taper));    // best quality
	/*
	sketches.push_back(Sketch("1.txt", Time("00:05:600"), Time("00:05:900"), 1, 4, false, Path::Taper));    // same cost as above, looks like below
	sketches.push_back(Sketch("1.txt", Time("00:05:300"), Time("00:05:600"), 1, 4, true, Path::Taper));     // best bang for buck
	sketches.push_back(Sketch("1.txt", Time("00:05:900"), Time("00:06:200"), 1, 5, false, Path::Taper));    // cheapest but worst looking
	for (auto& sketch : sketches) {
		if (sketch.make())
			return 1;   // error if make doesn't return 0
	}
	*/
	// RainGenerator testing
	// RainGenerator::RainGenerator();

	//Walker shit I guess
	if (1) { //lmao
		RainGenerator gen = RainGenerator(Time("00:53:00"));
		std::vector<Sprite *> raindrops = gen.FreezeRain();
		for (auto & raindrop : raindrops) {
			std::cout << raindrop->position.x << " " << raindrop->position.y << "\n";
		}
		Walker walk_boi = Walker::Walker(raindrops);
		walk_boi.walk(50, Time("00:54:00").ms, Time("01:04:00").ms);
	}

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}
