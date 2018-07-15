#pragma once

#include "Walker.hpp"

#include "Time.hpp"
#include "Vector2.hpp"

class Walker {
public:
	//field of view
	float fov = 90;
	
	//vector of sprites currently on screen
	std::vector<Sprite *> sprites;

	//location of each sprite
	std::vector<Vector3> location;

	Walker(std::vector<Sprite *> sprites, std::vector<Vector2> location);
	~Walker();

	void walk(Vector2 startPosition, Vector2 endPosition, Time startTime, Time endTime);
	void rotate(Vector2 startAngle, Vector2 endAngle, Time startTime, Time endTime);
private:
	Vector3 convertThreeD(Vector2);
}
