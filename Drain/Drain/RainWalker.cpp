#include "RainWalker.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

RainWalker::RainWalker(const std::vector<SpriteCollection> &sprites)
	: Walker{sprites} {
}

SpriteCollection RainWalker::create(const Time &startTime, const Vector2& centerPos) {
	std::string spriteImage = getPath(Path::Circle);
	return SpriteCollection(Storyboard::CreateSprite(spriteImage, { 0, 0 }));
}

void RainWalker::moveCurrent(const Time& startTime, const Time& endTime) {
	const auto totalTime = endTime.ms - startTime.ms;

	for (auto& drop : sprites) {
		if (isInScreen(drop.position)) {
			const auto startPosition = drop.position;
			const auto endPosition = findEndPoint(startPosition, offset);

			const auto ratioTraveled = (endPosition - startPosition).Magnitude() / (endPosition.Magnitude());

			const auto startScale = 1;
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

void RainWalker::moveSprites(const Time& startTime, const Time& endTime, const float spawnsPerSecond) {
	const auto totalTime = endTime.ms - startTime.ms;
	const auto count = static_cast<int>(totalTime / 1000.0f * spawnsPerSecond);
	const auto size = Vector2(Vector2::ScreenSize.x / 2 * 0.4f, Vector2::ScreenSize.y / 2 * 0.4f);

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

		const auto endPosition = findEndPoint(startPosition, offset);
		auto sprite = create(moveStartTime, startPosition);

		sprite.MoveAndScale(moveStartTime, moveEndTime, startPosition, endPosition, startScale, endScale);
		Swatch::colorFgToFgSprites(sprite.sprites, moveStartTime, moveEndTime);
	}
}