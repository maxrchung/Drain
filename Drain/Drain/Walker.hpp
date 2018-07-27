#pragma once

#include "Sprite.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

#include <vector>

typedef struct raindrop {
	Sprite *sprite;
	Vector3 position;
	float size;
} raindrop;


class Walker {
public:
	//field of view
	float fov = 90;

	std::vector<raindrop> raindrops;

	Walker(std::vector<Sprite *> sprites);

	void walk(float distance, Time startTime, Time endTime);

private:
	float w_rand(float min, float max);

	//check if the given 3d coordinate is on screen
	bool checkInScreen(Vector3 coordinates, float size);

	//convert 2d to 3d
	Vector3 twoToThree(Sprite *sprite, float size);

	//convert 3d to 2d
	Vector3 threeToTwo(Vector3 coordinates, float size);

	//find the collision point of the line between a and b
	//to the border of the screen
	Vector2 findCollision(Vector2 a, Vector2 b);

	//find the point at which to start drawing point
	Vector2 findDistance(Vector3 a, Vector3 b, float size);

	//add more sprites for walking
	void addSprites(float distance, Time startTime, Time endTime);

	//the maximum distance that any sprite will be drawn
	//the minimum distance that a sprite will be drawn
	const float max_distance = 30;
	const float min_distance = 1;

	//size in pixels
	const uint8_t sprite_size = 100;

	//min and max scale of the raindrop
	//scales are for the actual sprite size
	//i think these are the values used in rainGenerator
	const float min_scale = 0.05;
	const float maxScale = 0.7;

	//sizes of the raindrop
	const float minSize = 1;
	const float maxSize = 100;
};
