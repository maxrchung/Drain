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
           const int resolution = 5,    // lower=more detail
           const int margin = 5,
           const Path& brush = Path::Pixel,
		   const Easing& easing = Easing::Linear);
	const int make();

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
    int constResolution(Bezier b);
    void getTransform(float *xshift, float *yshift, float *xscale, float *yscale);
    int totalLines;
    int count;
    void dynamicResolution(Bezier b, const double dynamicResFactor = 50.0);
};