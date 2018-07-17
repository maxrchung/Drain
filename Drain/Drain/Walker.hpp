#pragma once

#include "Sprite.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

#include <vector>

class Walker {
public:
	//field of view
	float fov = 90;
	
	//current angle
	Vector2 angle = Vector2::Zero;

	//current position
	Vector3 position;

	//vector of all sprites
	std::vector<Sprite *> sprites;

	//location of each sprite
	std::vector<Vector3> location;

	//size of each sprite
	std::vector<float> size;

	Walker(std::vector<Sprite *> sprites, std::vector<Vector2> location, std::vector<float> size);

	void walk(float distance, Time startTime, Time endTime);

private:
	bool checkInScreen(Vector3 coordinates, float size);
	Vector3 convertThreeD(Vector2 coordinates, float size);
	Vector3 convertTwoD(Vector3 coordinates);

	//the maximum distance that any sprite will be drawn
	float max_distance = 30;

	//the minimum distance that a sprite will be drawn
	float min_distance = 1;
};
