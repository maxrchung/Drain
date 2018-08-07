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
           const int thickness,
           const float resolution,
           const bool dynamic,
           const Path& brush,
           const int margin = 5,
           const Easing& easing = Easing::Linear,
           const bool drawIn = false,
           const bool drawOut = false);
    static void render();
    int times;  // times to loop visibility on and off
    int relStart; // delay between start of loop and start of this sketch
    int hiddenDur;  // time this sketch is hidden (used in loops)
private:
    const int make();
	const std::string pointMapPath;
    const int thickness;
	const float resolution;
    const bool dynamic;
    const int margin;
	const Path brush;
	std::string brushPath;
	const Time startTime;
	const Time endTime;
    int visDur;
	const Easing easing;
    const bool drawIn;
    const bool drawOut;
	std::vector<Vector2> points;
    void draw(Bezier b);    // make() breaks the .txt up into 4-dim beziers and calls draw
    int constResolution(Bezier b);
    void getTransform(float *xshift, float *yshift, float *xscale, float *yscale);
    int totalLines; // should be the same as sprites.size()
    std::vector<Sprite*> sprites;
    int count;  // number of ; in .txt (curves)
    int dynamicResolution(Bezier b);
    static void loop(int times, std::vector<Sketch> v);
};