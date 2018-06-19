#include "Lyric.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "SpriteCollection.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "RainGenerator.hpp"
#include <iostream>

int main() {
	// Gets rid of beatmap background
	Storyboard::CreateSprite("36592_serial_experiments_lain.jpg", Vector2::Zero, Layer::Background);
	// Solid color background
	auto const background = Storyboard::CreateSprite(getPath(Path::Pixel), Vector2::Zero, Layer::Background);
	background->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize, Easing::Linear, 0);
	background->Color(0, Time("06:37:848").ms, Swatch::offwhite, Swatch::offwhite, Easing::Linear, 0);
	
	//Lyric testing
	//Lyric::draw("abca", Vector2(-50.0f, -50.0f), Time("00:05:584").ms, Time("00:07:282").ms, Swatch::offwhite, Swatch::water, 50.0f);
	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	
	RainGenerator(10);

	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);


	return 0;
}