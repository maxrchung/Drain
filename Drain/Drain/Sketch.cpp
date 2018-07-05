#include "Sketch.hpp"
#include "Storyboard.hpp"

/*
This class reads from a text file, parses it, and creates a vector of
Bezier curves to sketch an image
*/

Sketch::Sketch(const std::string& pointMapPath, const Time& startTime, const Time& endTime,
    const Easing& easing, const Path& brush, const int resolution, const int thickness)
	: pointMapPath{ pointMapPath }, startTime{ startTime }, endTime{ endTime },
    easing{ easing }, brush{ brush }, resolution{ resolution }, thickness{ thickness }
{
	brushPath = getPath(brush);
}

void Sketch::draw() {
	auto testBez = Bezier({ Vector2(-400,220),
		Vector2(-210,-85.5),
		Vector2(300,100) });
	int numPoints = testBez.length / resolution;	// truncate
	auto points = std::vector<Vector2>();
	for (int i = 0; i < numPoints; i++) {
		points.push_back(testBez.findPosition(static_cast<float>(i) / numPoints));
	}
	// draw each point
	for (auto &point : points) {
		Storyboard::CreateSprite(brushPath, point)->Scale(startTime.ms, endTime.ms, thickness, thickness);
	}
	auto mpoints = std::vector<Vector2>();
	// find midpoint of points and draw line between them
	for (int i = 0; i < points.size() - 1; i++) {
		mpoints.push_back((points[i] + points[i + 1]) / 2);
		float dist = points[i].DistanceBetween(points[i + 1]);
		float angle = atan(-(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x)); // negate y because osu!
		auto line = Storyboard::CreateSprite(brushPath, mpoints[i]);
		line->ScaleVector(startTime.ms, endTime.ms, Vector2(dist, thickness), Vector2(dist, thickness));
		line->Rotate(startTime.ms, endTime.ms, angle, angle);
	}
}