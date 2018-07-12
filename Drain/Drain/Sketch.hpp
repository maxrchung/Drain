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
           const int thickness = 1,
           const int resolution = 50,
           const int margin = 5,
		   const Easing& easing = Easing::Linear,
		   const Path& brush = Path::Pixel);
	const int parse();

private:
	const std::string pointMapPath;
    const int thickness;
	const int resolution;
    const int margin;
	const Path brush;
	std::string brushPath;
	const Time startTime;
	const Time endTime;
	const Easing easing;
	std::vector<Vector2> points;
    void draw(Bezier b);
    void getTransform(float *xshift, float *yshift, float *xscale, float *yscale);
};