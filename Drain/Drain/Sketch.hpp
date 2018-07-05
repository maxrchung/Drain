#pragma once
#include <vector>
#include <cstring>
#include "Bezier.hpp"
#include "Path.hpp"
#include "Time.hpp"
#include "Easing.hpp"

class Sketch {
public:
	Sketch(const std::string& pointMapPath,
		   const Time& startTime,
		   const Time& endTime,
		   const Easing& easing = Easing::Linear,
		   const Path& brush = Path::Pixel,
           const int resolution = 50,
		   const int thickness = 1);
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