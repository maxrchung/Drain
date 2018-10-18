#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Path.hpp"

#include "Walker.hpp"

#include <cmath>

Walker::Walker(const std::vector<SpriteCollection>& sprites)
	: sprites{ sprites } {}

Vector2 Walker::findEndPoint(const Vector2& startPosition, const float offset) {
	Vector2 endPosition = Vector2::Zero;

	Vector2 slopeVector = startPosition;
	float slope = slopeVector.y / slopeVector.x;

	Vector2 mid;
	if (slopeVector.y < 0) {
		mid.y = -Vector2::ScreenSize.y / 2 - offset;
	}
	else {
		mid.y = Vector2::ScreenSize.y / 2 + offset;
	}

	if (slopeVector.x < 0) {
		mid.x = -Vector2::ScreenSize.x / 2 - offset;
	}
	else {
		mid.x = Vector2::ScreenSize.x / 2 + offset;
	}

	switch ((!!slopeVector.y) | (!!slopeVector.x << 1)) {
		case 0:
			break;

		case 1:
			endPosition.x = mid.x;
			break;

		case 2:
			endPosition.y = mid.y;
			break;

		case 3:
			endPosition.y = slope * mid.x + startPosition.y;
			endPosition.x = (mid.y - startPosition.y) / slope;
			if (std::abs(endPosition.y) > Vector2::ScreenSize.y / 2)
				endPosition.y = mid.y;

			if (std::abs(endPosition.x) > Vector2::ScreenSize.x / 2)
				endPosition.x = mid.x;
			break;
	}

	return endPosition;
}

float Walker::generateRandomFloat(float min, float max) {
	float out = (float)rand() / RAND_MAX;
	out *= (max - min);
	out += min;

	return out;
}

/*
* checks that the object is within screen
*/
bool Walker::isInScreen(const Vector2& point) {
	bool out = 1;

	if (std::abs(point.x) > Vector2::ScreenSize.x / 2)
		out = 0;

	if (out && (std::abs(point.y) > Vector2::ScreenSize.y / 2))
		out = 0;

	return out;
}

/*
* distance: forward distance walked, can be positive or negative?
* startTime/endTime: specificy how long walked
*/
void Walker::walk(const Time& startTime, const Time& endTime, const float spawnsPerSecond) {
	//move the boys from rainGenerator
	moveCurrent(startTime, endTime);

	//move those boys
	moveSprites(startTime, endTime, spawnsPerSecond);
}