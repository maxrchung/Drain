#pragma once
#include "Bubble.hpp"
#include "Time.hpp"
#include "Timing.hpp"
#include "Vector2.hpp"
#include <random>
#include <vector>
#include <cmath>

class Splatter {
public:
	// standalone, defined by pos Vector2
	Splatter(const Time& startTime,
			 const Time& endTime,
			 const float size,
			 const int numDrops,
			 const int type,
             const int satelliteSpawnTime,
			 const Vector2 centerPos);
	// position defined by existing AirBubble
	Splatter(const Time& startTime,
			 const Time& endTime,
			 const float size,
			 const int numDrops,
			 const int type,
             const int satelliteSpawnTime,
			 Bubble* const bubble);   // Sketch is a placeholder, replace with AirBubble
	static void render();
	static void renderFirstGradualPop(std::vector<Bubble*>& bubbles);
	static void renderSecondAllPop(std::vector<Bubble*>& bubbles);
	std::vector<Sprite*> sprites;
private:
    static constexpr float SPRITE_SIZE = 100.0; // in pixels
    static constexpr float DEG_TO_RAD = 3.14159 / 180.0;    // multiply by this to convert from deg to rad
    static constexpr float MIN_SATELLITE_SIZE = 0.01;
    static constexpr float MAX_SATELLITE_SIZE_FACTOR = 0.25;    // sizeFactor * this value is the max satellite size
	const Time startTime;
	const Time endTime;
	int totalDur;
	const Vector2 centerPos;
	const float sizeFactor;
	const int numDrops;
	const int type;
    const int satelliteSpawnTime;   // in ms
	Sprite* draw(Vector2 pos,
				 int offset,
				 float size,
				 float fadeInDur = 0,    // duration of fade in ms
				 float fadeFrom = 0,     // origin opacity from 0 to 1
				 float fadeTo = 1,     // destination opacity from 0 to 1
				 float growDur = 0,      // duration of expansion in ms
				 float growFrom = 0,     // origin size from 0 to 1
				 Easing easing = Easing::Linear);
	static void make(const Time& startTime,
					 const Time& endTime,
					 Bubble* const bubble);
	int make();

	static constexpr float bubbleFadeTime = Timing::half;
	static std::default_random_engine generator;
	static std::exponential_distribution<double> exp;    // mean of the exp distribution = 1 / 3.5
	static std::gamma_distribution<double> gamma;
	static std::normal_distribution<double> normal; // mean, std dev
	static std::normal_distribution<double> normal2; // mean, std dev
	static std::uniform_real_distribution<double> uniform; // uniform distribution between -1 and 1
    static std::uniform_real_distribution<double> uniformAngle; // uniform distribution between 0 and 359 (degrees)
};

