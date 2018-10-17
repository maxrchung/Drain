#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Path.hpp"

#include "Walker.hpp"

#include <cmath>

Walker::Walker(const std::vector<SpriteCollection>& sprites)
	: sprites{ sprites } {}

Vector2 Walker::findEndPoint(const Vector2& startPosition) {
	Vector2 endPosition = Vector2::Zero;

	Vector2 slopeVector = startPosition;
	float slope = slopeVector.y / slopeVector.x;
	float offset = SPRITE_SIZE * maxScale * 5;

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

void Walker::moveCurrent(const Time& startTime, const Time& endTime) {
	const auto totalTime = endTime.ms - startTime.ms;

	for (auto & drop : sprites) {
		if (isInScreen(drop.position)) {
			const auto startPosition = drop.position;
			const auto endPosition = findEndPoint(startPosition);

			const auto ratioTraveled = (endPosition - startPosition).Magnitude() / (endPosition.Magnitude());

			const auto startScale = drop.scale[0];
			const auto endScale = startScale * (1 + ratioTraveled);

			auto moveEndTime = startTime.ms + generateRandomFloat(1000, totalTime);
			if (moveEndTime > endTime.ms) {
				moveEndTime = endTime.ms;
			}

			drop.MoveAndScale(startTime.ms, moveEndTime, startPosition, endPosition, startScale, endScale);
			Swatch::colorFgToFgSprites(drop.sprites, startTime.ms, moveEndTime);
		}
	}
}

void Walker::moveSprites(const float distance, const Time& startTime, const Time& endTime, const float density) {
	const auto totalTime = endTime.ms - startTime.ms;
	const auto speed = distance / totalTime;

	const auto size = Vector2(Vector2::ScreenSize.x / 2 * 0.4f, Vector2::ScreenSize.y / 2 * 0.4f);

	const auto count = static_cast<int>(speed * density);

	for (int i = 0; i < count; ++i) {
		auto moveStartTime = startTime.ms + i * generateRandomFloat(0, 100);
		auto moveEndTime = moveStartTime + generateRandomFloat(1000, totalTime);

		if (moveEndTime > endTime.ms)
			moveEndTime = endTime.ms - generateRandomFloat(0, 2000);

		if (moveStartTime > endTime.ms) {
			moveStartTime = endTime.ms - 1000;
			moveEndTime = endTime.ms;
			break;
		}

		float startScale = minScale;
		float endScale = maxScale * generateRandomFloat(1, 5);

		const auto startPosition = Vector2(generateRandomFloat(-size.x, size.x),
										   generateRandomFloat(-size.y, size.y));

		const auto endPosition = findEndPoint(startPosition);
		auto sprite = create(moveStartTime, startPosition, startScale);

		sprite.MoveAndScale(moveStartTime, moveEndTime, startPosition, endPosition, startScale, endScale);
		Swatch::colorFgToFgSprites(sprite.sprites, moveStartTime, moveEndTime);
	}
}

/*
* distance: forward distance walked, can be positive or negative?
* startTime/endTime: specificy how long walked
*/
void Walker::walk(const float distance, const Time& startTime, const Time& endTime, const float density) {
	//for every sprite
	Vector3 temp = Vector3::Zero;

	//move the boys from rainGenerator
	moveCurrent(startTime, endTime);

	//move those boys
	moveSprites(distance, startTime, endTime, density);
}