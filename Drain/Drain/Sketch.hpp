#pragma once
#include <vector>
#include <cstring>
#include "Bezier.hpp"
#include "Path.hpp"
#include "Time.hpp"
#include "Easing.hpp"

class Sketch {
public:
	Sketch(std::string pointMapPath = "xy.txt",
		   int resolution = 50,
		   int thickness = 1,
		   Path brush = Path::Pixel,
		   Time startTime = Time("00:00:00").ms,
		   Time endTime = Time("00:00:00").ms,
		   Easing easing = Easing::Linear);
	void draw();

private:
	const std::string pointMapPath;
	const int resolution;
	const int thickness;
	const Path brush;
	std::string brushPath;
	const Time startTime;
	const Time endTime;
	const Easing easing;
	std::vector<Vector2> points;
};