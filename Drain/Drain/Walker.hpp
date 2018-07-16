#pragma once

#include "Walker.hpp"

#include "Time.hpp"
#include "Vector2.hpp"

class Walker {
public:
	//field of view
	float fov = 90;
	
	//current angle
	Vector2 angle;

	//current position
	Vector3 position;

	//vector of all sprites
	std::vector<Sprite *> sprites;

	//location of each sprite
	std::vector<Vector3> location;

	Walker(std::vector<Sprite *> sprites, std::vector<Vector2> location);
	~Walker();

	void walk(float distance, Time startTime, Time endTime);
	//void rotate(Vector2 startAngle, Vector2 endAngle, Time startTime, Time endTime);

private:
	bool checkAzimuth(Vector3 coordinates, float size);
	bool checkAltitude(Vector3 coordinates, float size);
	bool checkInScreen(Vector3 coordinates, float size);
	Vector3 convertThreeD(Vector2 coordinates, float size);
	Vector2 convertTwoD(Vector3 coordinates, float *size);
}
