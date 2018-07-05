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
	Lyric::draw("abcabc", Vector2(50.0f, 50.0f), Time("00:05:584").ms, Time("00:15:282").ms, 80.0f);

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb

	auto testSketch = Sketch("", 50, 1, Path::Pixel, 0, 20000);
	testSketch.draw();

	/*
	auto testBez = Bezier({ Vector2(-400,220),
								  Vector2(-210,-85.5),
								  Vector2(300,100) });
	int resolution = 50;
	float thickness = 1;
	int numPoints = testBez.length / resolution;	// truncate
	auto points = std::vector<Vector2>();
	for (int i = 0; i < numPoints; i++) {
		points.push_back(testBez.findPosition(static_cast<float>(i) / numPoints));
	}
	// draw each point
	for (auto &point : points) {
		Storyboard::CreateSprite("b", point)->Scale(0, Time("00:10:000").ms, thickness, thickness);
	}
	auto mpoints = std::vector<Vector2>();
	// find midpoint of points and draw line between them
	for (int i = 0; i < points.size() - 1; i++) {
		mpoints.push_back((points[i] + points[i + 1]) / 2);
		float dist = points[i].DistanceBetween(points[i + 1]);
		float angle = atan(-(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x)); // negate y because osu!
		auto line = Storyboard::CreateSprite("b", mpoints[i]);
		line->ScaleVector(0, Time("00:10:000").ms, Vector2(dist, thickness), Vector2(dist, thickness));
		line->Rotate(0, Time("00:10:000").ms, angle, angle);
	}
	*/

	/*
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
	*/
	

	//RainGenerator testing
	//RainGenerator::RainGenerator(5, 10, Time("00:14:00").ms, Time("00:54:00").ms, 1.2f);

	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);


	return 0;
}