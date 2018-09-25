#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
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
	std::vector<SpriteCollection> sprites;

	Walker(std::vector<SpriteCollection> sprites);

	void walk(float distance, Time startTime, Time endTime);

private:
	float w_rand(float min, float max);

	//check if the given 3d coordinate is on screen
	bool inScreen(Vector2 a);

	//convert 2d to 3d
	Vector3 twoToThree(Sprite *sprite, float size);

	//convert 3d to 2d
	Vector3 threeToTwo(Vector3 coordinates, float size);

	//given a line between the Vector2s b and a, find the point at
	//which is crosses the screen
	Vector2 findProjection(Vector2 a, Vector2 b);

	//find the point at which to start drawing point
	Vector2 findAppearPoint(Vector3 a, Vector3 b, float size);

	//move sprites from RainGenerator
	void moveCurrent(float distance, Time startTime, Time endTime);

	//move the sprites
	void moveSprites(float distance, Time startTime, Time endTime);
	
	//the maximum distance that any sprite will be drawn
	//the minimum distance that a sprite will be drawn
	const float max_distance = 100;
	const float min_distance = 1;

	//size in pixels
	const uint8_t sprite_size = 100;

	//min and max scale of the raindrop
	//scales are for the actual sprite size
	//i think these are the values used in rainGenerator
	const float min_scale = 0.01;
	const float max_scale = 0.1;

	const float sizeScale = 1;

	//sizes of the raindrop
	const float minSize = 10;
	const float maxSize = 100;
};
