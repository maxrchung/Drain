#pragma once
#include <vector>
#include <cstring>
#include "Bezier.hpp"
#include "Path.hpp"
#include "Time.hpp"
#include "Easing.hpp"
#include "Sprite.hpp"

struct s {
	double pos;
	double secondDeriv;
};

class Sketch {
public:
	Sketch(const std::string& pointMapPath,
		   const Time& startTime,
		   const Time& endTime,
		   const float resolution = defaultResolution,
		   const bool dynamic = true,
		   const Path& brush = Path::Taper,
		   const int margin = 0,
		   const int thickness = 1,
		   const Easing& easing = Easing::Linear,
		   const bool drawIn = false,
		   const bool drawOut = false,
		   const bool fadeIn = false,
		   const bool fadeOut = false);
	static void render();
private:
	// Helper that calls make()
	static void make(const std::string& pointMapPath,
					 const Time& startTime,
					 const Time& endTime,
					 const float resolution = defaultResolution,
					 const bool dynamic = true,
					 const Path& brush = Path::Taper,
					 const int margin = 0,
					 const int thickness = 1,
					 const Easing& easing = Easing::Linear,
					 const bool drawIn = false,
					 const bool drawOut = false,
					 const bool fadeIn = false,
					 const bool fadeOut = false);
	static void loop(std::vector<Sketch>& v, int times);
	static constexpr float defaultResolution = 4.5f;
	static constexpr float shift = 4.0f;
	void draw(Bezier& b);    // make() breaks the .txt up into 4-dim beziers and calls draw
	void getTransform(float *xshift, float *yshift, float *xscale, float *yscale);
	bool inBounds(const Vector2& point); // Check if point is within bounds
	int constResolution(Bezier& b);
	int dynamicResolution(Bezier& b);
	int make();
	const std::string pointMapPath;
	const bool fadeIn;
	const bool fadeOut;
	const bool drawIn;
	const bool drawOut;
	const bool dynamic;
	const Easing easing;
	const float resolution;
	const int boundsBorder = 5;
	const int margin;
	const int thickness;
	const Path brush;
	const std::string brushPath;
	const Time endTime;
	const Time startTime;
	int count;  // number of ; in .txt (curves)
	int totalLines;
	int visDur;
	int loopEndTime;
	int times;  // times to loop visibility on and off
	int relStart; // delay between start of loop and start of this sketch
	int hiddenDur;  // time this sketch is hidden (used in loops)
	std::vector<Vector2> points;
	std::vector<Sprite*> sprites;
};