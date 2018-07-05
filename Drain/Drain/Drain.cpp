#include "Lyric.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "SpriteCollection.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Bezier.hpp"
#include <iostream>

int main() {
	// Gets rid of beatmap background
	Storyboard::CreateSprite("36592_serial_experiments_lain.jpg", Vector2::Zero, Layer::Background);
	// Solid color background
	auto const background = Storyboard::CreateSprite(getPath(Path::Pixel), Vector2::Zero, Layer::Background);
	background->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize, Easing::Linear, 0);
	background->Color(0, Time("06:37:848").ms, Swatch::offwhite, Swatch::offwhite, Easing::Linear, 0);

	//Lyric testing
	Lyric::draw("abcabc", Vector2(50.0f, 50.0f), Time("00:05:584").ms, Time("00:15:282").ms, Swatch::offwhite, Swatch::water, 80.0f);
	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb

	auto testBez = Bezier({ Vector2(-106.46175,-100.45),
								  Vector2(-105.25824,-85.5),
								  Vector2(-105.64377,-42.5) });
	const auto result = std::vector<Vector2>({ testBez.findPosition(0.0),
											   testBez.findPosition(0.5),
											   testBez.findPosition(1.0) });
	auto const first = Storyboard::CreateSprite("a", result[0]);
	auto const mid = Storyboard::CreateSprite(getPath(Path::Circle), result[1]);
	auto const last = Storyboard::CreateSprite(getPath(Path::Circle), result[2]);
	first->Scale(0, Time("00:10:000").ms, 0.1, 0.1);
	mid->Scale(0, Time("00:10:000").ms, 0.1, 0.1);
	last->Scale(0, Time("00:10:000").ms, 0.1, 0.1);
	auto const move = Storyboard::CreateSprite("a", result[0]);
	move->Scale(0, Time("00:10:000").ms, 0.1, 0.1);
	move->Move(0, Time("00:05:000").ms, move->position, result[1]);
	move->Move(Time("00:05:000").ms, Time("00:10:000").ms, move->position, result[2]);


	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);


	return 0;
}