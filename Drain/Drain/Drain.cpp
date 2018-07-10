#include "Lyric.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "RainGenerator.hpp"
#include "SpriteCollection.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Bezier.hpp"
#include "Sketch.hpp"
#include <iostream>
#include <ctime>
#include <cmath>

int main() {
	srand(time(NULL));
	// Gets rid of beatmap background
	Storyboard::CreateSprite("36592_serial_experiments_lain.jpg", Vector2::Zero, Layer::Background);
	// Solid color background
	auto const background = Storyboard::CreateSprite(getPath(Path::Pixel), Vector2::Zero, Layer::Background);
	background->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize, Easing::Linear, 0);
	background->Color(0, Time("06:37:848").ms, Swatch::offwhite, Swatch::offwhite, Easing::Linear, 0);

	//Lyric testing
	Lyric::draw("a bcdefghijklm", Vector2(0.0f, 100.0f), Time("00:05:584").ms, Time("00:10:282").ms, 50.0f);
	Lyric::draw("nopqrstuvwxyz", Vector2(0.0f, -100.0f), Time("00:05:584").ms, Time("00:10:282").ms, 50.0f);

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb

	//auto testSketch = Sketch("", 0, 10000);
	//testSketch.draw();

	//RainGenerator testing
	//RainGenerator::RainGenerator(5, 10, Time("00:14:00").ms, Time("00:54:00").ms, 1.2f);

	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);


	return 0;
}