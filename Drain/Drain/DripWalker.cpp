#include "Drip.hpp"
#include "DripWalker.hpp"
#include "Math.hpp"
#include "Swatch.hpp"
#include "Vector2.hpp"


DripWalker::DripWalker(const std::vector<SpriteCollection> &sprites)
	: Walker(sprites) {}

SpriteCollection DripWalker::create(const Time& startTime, const Vector2& centerPos) {
	return Drip::makeWalkerDrip(startTime, centerPos, generateRandomFloat(1.0f, 1.0f));
}

Vector2 DripWalker::findDripEndPoint(const Vector2& startPosition, const float offset) {
	Vector2 endPosition = Vector2::Zero;

	Vector2 slopeVector = startPosition;
	float slope = slopeVector.y / slopeVector.x;

	Vector2 mid;
	if (slopeVector.x < 0) {
		mid.x = -Vector2::ScreenSize.x / 2 - offset;
	}
	else {
		mid.x = Vector2::ScreenSize.x / 2 + offset;
	}

	endPosition.y = slope * mid.x;
	endPosition.x = mid.x;
	return endPosition;
}

void DripWalker::moveCurrent(const Time& startTime, const Time& endTime) {
	const auto totalTime = endTime.ms - startTime.ms;

	for (auto& sprite : sprites) {
		if (isInScreen(sprite.position)) {
			const auto startPosition = sprite.position;
			const auto endPosition = findDripEndPoint(startPosition, OFFSET);

			const auto ratioTraveled = (endPosition - startPosition).Magnitude() / (endPosition.Magnitude());
			//const auto endScale = startScale * (1 + ratioTraveled);
			const auto scaleTo = 3;

			auto moveEndTime = startTime.ms + generateRandomFloat(1000, totalTime);
			if (moveEndTime > endTime.ms) {
				moveEndTime = endTime.ms;
			}

			specialScale(sprite, startTime.ms, moveEndTime, startPosition, endPosition, scaleTo);
			Swatch::colorFgToFgSprites(sprite.sprites, startTime.ms, moveEndTime);
		}
	}
}

void DripWalker::moveSprites(const Time& startTime, const Time& endTime, const float spawnsPerSecond) {
	const auto totalTime = endTime.ms - startTime.ms;
	const auto count = static_cast<int>(totalTime / 1000.0f * spawnsPerSecond);
	const auto size = Vector2(Vector2::ScreenSize.x / 2 * 0.4f, Vector2::ScreenSize.y / 2 * 0.4f);
	const auto spawnTime = totalTime * 0.75f / count;

	for (int i = 0; i < count; ++i) {
		auto moveStartTime = startTime.ms + i * spawnTime;
		auto moveEndTime = moveStartTime + generateRandomFloat(10000, totalTime);

		if (moveEndTime > endTime.ms)
			moveEndTime = endTime.ms - generateRandomFloat(0, 2000);

		if (moveStartTime > endTime.ms) {
			moveStartTime = endTime.ms - 1000;
			moveEndTime = endTime.ms;
			break;
		}

		const auto negative = (rand() % 2 ? -1 : 1);
		const auto startPosition = 
			Vector2(negative * generateRandomFloat(size.x * 0.1f, size.x), 0)
			.Rotate(generateRandomFloat(-Math::pi / 4.0f, Math::pi / 4.0f));

		const auto endPosition = findDripEndPoint(startPosition, OFFSET);
		auto sprite = create(moveStartTime, startPosition);

		const auto startScale = 1;
		const auto ratioTraveled = (endPosition - startPosition).Magnitude() / (endPosition.Magnitude());
		const auto scaleTo = generateRandomFloat(40.0f, 60.0f);

		specialScale(sprite, moveStartTime, moveEndTime, startPosition, endPosition, scaleTo, Easing::EasingOut);
		Swatch::colorFgToFgSprites(sprite.sprites, moveStartTime, moveEndTime);
	}
}

void DripWalker::specialScale(SpriteCollection& collection, const int startTime, const int endTime, const Vector2& startPos, const Vector2& endPos, const float scaleTo, const Easing& easing, const int precision) {
	const auto circle = collection.sprites[0];
	const auto circleStartScale = circle->scale;
	const auto circleEndScale = circleStartScale * scaleTo;
	circle->Scale(startTime, endTime, circleStartScale, circleEndScale, easing, precision);

	Vector2 circleStartPos = collection.location[0] + startPos;
	Vector2 circleEndPos = collection.location[0] + endPos;
	circle->Move(startTime, endTime, circleStartPos, circleEndPos, easing);

	auto const column = collection.sprites[1];
	const auto columnStartScale = column->scaleVector;
	const auto top = column->position.y;
	const auto columnStartPos = collection.location[1] + startPos;
	const auto columnEndPos = collection.location[1] + endPos;

	auto bottom = circleEndPos.y;
	auto scaleEndTime = endTime;
	auto factor = 1.0f;
	if (bottom > top) {
		factor = (top - circleStartPos.y) / (circleEndPos.y - circleStartPos.y);
		scaleEndTime = startTime + factor * (endTime - startTime);
		bottom = top;
	}
	const auto columnEndScaleX = columnStartScale.x + factor * (columnStartScale.x * scaleTo - columnStartScale.x);
	const auto columnEndScale = Vector2(columnEndScaleX, (top - bottom) / COLUMN_PIXEL_SIZE) ;

	column->ScaleVector(startTime, scaleEndTime, columnStartScale, columnEndScale, easing, precision);

	column->MoveX(startTime, endTime, columnStartPos.x, columnEndPos.x, easing);
}
