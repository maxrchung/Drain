#include "Lyric.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Sketch.hpp"
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

	Lyric::render();

	auto testSketch = Sketch("1.txt", 100, 10000, 1, 4);
    if (testSketch.make())
        return 1;   // error if make doesn't return 0

	// RainGenerator testing
	// RainGenerator::RainGenerator();

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}