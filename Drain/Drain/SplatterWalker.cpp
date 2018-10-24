#include "Splatter.hpp"
#include "SplatterWalker.hpp"
#include "Swatch.hpp"
#include "Vector2.hpp"


SplatterWalker::SplatterWalker(const std::vector<SpriteCollection> &sprites)
	: Walker(sprites) {
}

SpriteCollection SplatterWalker::create(const Time& startTime, const Vector2& centerPos) {
	return Splatter::makeWalkerSplatter(startTime, centerPos, 1.0f);
}

void SplatterWalker::moveCurrent(const Time& startTime, const Time& endTime) {
	const auto totalTime = endTime.ms - startTime.ms;

	for (auto& sprite : sprites) {
		if (isInScreen(sprite.position)) {
			const auto startPosition = sprite.position;
			const auto endPosition = findEndPoint(startPosition, offset);

			const auto ratioTraveled = (endPosition - startPosition).Magnitude() / (endPosition.Magnitude());

			const auto startScale = 1;
			const auto endScale = startScale * (1 + ratioTraveled);

			auto moveEndTime = startTime.ms + generateRandomFloat(1000, totalTime);
			if (moveEndTime > endTime.ms) {
				moveEndTime = endTime.ms;
			}

			specialMove(sprite, startTime.ms, moveEndTime, startPosition, endPosition, startScale, endScale);
			Swatch::colorFgToFgSprites(sprite.sprites, startTime.ms, moveEndTime);
		}
	}
}

void SplatterWalker::moveSprites(const Time& startTime, const Time& endTime, const float spawnsPerSecond) {
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

		const auto startPosition = Vector2(generateRandomFloat(-size.x, size.x),
										   generateRandomFloat(-size.y, size.y));

		const auto endPosition = findEndPoint(startPosition, offset);
		auto sprite = create(moveStartTime, startPosition);

		const auto startScale = generateRandomFloat(0.01f, 0.05f);
		const auto endScale = generateRandomFloat(1.0f, 1.5f);

		specialMove(sprite, moveStartTime, moveEndTime, startPosition, endPosition, startScale, endScale);
		Swatch::colorFgToFgSprites(sprite.sprites, moveStartTime, moveEndTime);
	}
}

void SplatterWalker::specialMove(SpriteCollection& collection, const int startTime, const int endTime, const Vector2& startPos, const Vector2& endPos, const float startScale, const float endScale, const Easing& easing, const int precision) {
	for (int i = 0; i < collection.size; ++i) {
		auto const sprite = collection.sprites[i];
		sprite->Scale(startTime, endTime, startScale * collection.scale[i], endScale * collection.scale[i], easing, precision);
		Vector2 start = collection.location[i] * startScale + startPos;
		Vector2 end = collection.location[i] * endScale + endPos;

		const auto parallaxTime = i == 0 ? 0 : RandomRange::calculate(1, 10000);
		sprite->Move(startTime, endTime + parallaxTime, start, end);
	}
}