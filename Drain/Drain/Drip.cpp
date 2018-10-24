#include "Drip.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include <algorithm>

const RandomRange Drip::PARTIAL_DRAW_RANDOM = RandomRange(25, 100, 100);
const RandomRange Drip::RANDOM_VARIATION = RandomRange(10, 20);
const std::vector<int> Drip::BACKGROUND_SPAWN_TIMES = std::vector<int>{
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("02:55:000").ms,
	Time("03:02:000").ms
};
const std::vector<int> Drip::FIRST_SPAWN_TIMES = std::vector<int>{
	Time("04:04:168").ms,
	Time("04:04:452").ms,
	Time("04:06:433").ms,
	Time("04:06:716").ms,
	Time("04:08:697").ms,
	Time("04:08:980").ms,
	Time("04:12:942").ms,
	Time("04:13:225").ms,
	Time("04:13:791").ms,
	Time("04:14:074").ms,
	Time("04:17:470").ms,
	Time("04:17:753").ms,
	Time("04:18:319").ms,
	Time("04:18:602").ms,
	Time("04:22:282").ms,
	Time("04:22:565").ms,
	Time("04:24:546").ms,
	Time("04:24:829").ms,
	Time("04:26:810").ms,
	Time("04:27:093").ms,
	Time("04:31:055").ms,
	Time("04:31:338").ms,
	Time("04:31:904").ms,
	Time("04:32:187").ms,
	Time("04:42:942").ms, // Screen covered
};
const std::vector<int> Drip::SECOND_SPAWN_TIMES = std::vector<int>{
	Time("05:20:301").ms,
	Time("05:20:867").ms,
	Time("05:20:433").ms,
	Time("05:23:131").ms,
	Time("05:23:697").ms,
	Time("05:24:546").ms,
	Time("05:25:395").ms,
	Time("05:25:961").ms,
	Time("05:32:753").ms,
	Time("05:33:885").ms,
	Time("05:35:018").ms,
	Time("05:36:716").ms,
	Time("05:37:282").ms,
	Time("05:38:414").ms,
	Time("05:39:546").ms // Freeze
};

SpriteCollection Drip::buildSpriteCollection(Sprite* const circle, Sprite* const column) {
	auto locations = std::vector<Vector2>();
	auto scales = std::vector<float>();
	const auto centerPos = circle->position;
	const auto centerScale = circle->scale;
	locations.push_back(Vector2::Zero);
	scales.push_back(centerScale);
	locations.push_back(column->position - centerPos);
	scales.push_back(column->scale);

	const auto collection = SpriteCollection({ circle, column }, locations, scales);
	return collection;
}

SpriteCollection Drip::draw(const int startTime, const int endTime, const float left, const float right, const bool drawPartial) {
	const auto centerX = (left + right) / 2;
	const auto columnWidth = right - left;

	// Select an Out easing that is before Elastic
	const auto easing = static_cast<Easing>(1 + 3 * (rand() % 6));

	const auto circleDiameter = columnWidth * CIRCLE_FACTOR;
	const auto circleRadius = circleDiameter / 2;
	const auto top = Vector2::ScreenSize.y / 2.0f + circleRadius;
	float bottom;
	if (drawPartial) {
		// When drawing partial drip, choose a random end point dependent on PARTIAL_DRAW_RANDOM
		bottom = Vector2::ScreenSize.y / 2.0f - (Vector2::ScreenSize.y + circleRadius) * PARTIAL_DRAW_RANDOM.calculate();
	}
	else {
		bottom = -Vector2::ScreenSize.y / 2.0f - circleRadius;
	}
	const auto circle = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(centerX, top), Layer::Foreground);
	const auto column = Storyboard::CreateSprite(getPath(Path::Column), Vector2(centerX, top), Layer::Foreground, Origin::TopCentre);

	const auto circleScale = CIRCLE_FACTOR * columnWidth / COLUMN_PIXEL_SIZE;
	circle->Scale(startTime, startTime, circleScale, circleScale, easing);
	// Cannot do circle->MoveY() because this conflicts with circle->Move() calls made later during walker
	circle->Move(startTime, endTime, Vector2(centerX, top), Vector2(centerX, bottom), easing);

	const auto columnStartScale = Vector2(columnWidth / (COLUMN_PIXEL_SIZE * COLUMN_WIDTH_BUFFER), 0);
	const auto columnEndScale = Vector2(columnStartScale.x, (top - bottom) / COLUMN_PIXEL_SIZE);
	column->ScaleVector(startTime, endTime, columnStartScale, columnEndScale, easing);

	Swatch::colorFgToFgSprites({ circle, column }, startTime, endTime);
	
	const auto collection = buildSpriteCollection(circle, column);
	return collection;
}

std::vector<float> Drip::generatePositions(const int count) {
	// Create list of variations by some arbitrary values
	auto variation = 0;
	auto variations = std::vector<int>(count);
	variations[0] = variation;
	for (int i = 1; i < count; ++i) {
		variation += RANDOM_VARIATION.calculate();
		variations[i] = variation;
	}

	// Normalize variations so they are between 0 and 1
	const auto max = variations.back();
	auto normalizedVariations = std::vector<float>(variations.size());
	for (int i = 0; i < variations.size(); ++i) {
		normalizedVariations[i] = static_cast<float>(variations[i]) / max;
	}

	// Scale variations so they fit within ScreenSize.x
	auto scaledVariations = std::vector<float>(normalizedVariations.size());
	const auto left = -Vector2::ScreenSize.x / 2.0f;
	for (int i = 0; i < variations.size(); ++i) {
		scaledVariations[i] = left + normalizedVariations[i] * Vector2::ScreenSize.x;
	}

	return scaledVariations;
}

void Drip::renderBackground() {
	const auto variations = generatePositions(BACKGROUND_SPAWN_TIMES.size() * 4.0f);

	auto indexes = std::vector<int>(variations.size() - 1);
	for (int i = 0; i < variations.size() - 1; ++i) {
		indexes[i] = i;
	}
	std::random_shuffle(indexes.begin(), indexes.end());

	const auto endTime = BACKGROUND_SPAWN_TIMES.back();
	for (int i = 0; i < BACKGROUND_SPAWN_TIMES.size() - 1; ++i) {
		const auto startTime = BACKGROUND_SPAWN_TIMES[i];
		const auto index = indexes.back();
		indexes.pop_back();
		const auto left = variations[index];
		const auto right = variations[index + 1];
		const auto middle = (right + left) / 2.0f;
		if (middle < -170.0f || middle > 170.0f) {
			draw(startTime, endTime, left, right, true);
		}
		else {
			--i;
		}
	}
}

void Drip::renderFirstFill() {
	const auto variations = generatePositions(FIRST_SPAWN_TIMES.size());

	// Shuffle indexes so we randomly choose next drop
	auto indexes = std::vector<int>(variations.size() - 1);
	for (int i = 0; i < variations.size() - 1; ++i) {
		indexes[i] = i;
	}
	std::random_shuffle(indexes.begin(), indexes.end());

	const auto endTime = FIRST_SPAWN_TIMES.back();
	for(int i = 0; i < FIRST_SPAWN_TIMES.size() - 1; ++i) {
		const auto startTime = FIRST_SPAWN_TIMES[i];
		const auto index = indexes.back();
		indexes.pop_back();
		const auto left = variations[index];
		const auto right = variations[index + 1];
		draw(startTime, endTime, left , right);
	}
}

SpriteCollection Drip::makeWalkerDrip(const Time& spawnTime, const Vector2& center, const float columnWidth) {
	const auto circleDiameter = columnWidth * CIRCLE_FACTOR;
	const auto circleRadius = circleDiameter / 2;
	const auto top = Vector2::ScreenSize.y / 2.0f + circleRadius;
	const auto bottom = center.y;
	const auto circle = Storyboard::CreateSprite(getPath(Path::Circle), center, Layer::Foreground);
	const auto column = Storyboard::CreateSprite(getPath(Path::Column), Vector2(center.x, top), Layer::Foreground, Origin::TopCentre);

	const auto circleScale = circleDiameter / COLUMN_PIXEL_SIZE;
	circle->Scale(spawnTime.ms, spawnTime.ms, circleScale, circleScale);
	circle->Move(spawnTime.ms, spawnTime.ms, Vector2(center.x, top), center);

	const auto columnStartScale = Vector2(columnWidth / (COLUMN_PIXEL_SIZE * COLUMN_WIDTH_BUFFER), 0);
	const auto columnEndScale = Vector2(columnStartScale.x, (top - bottom) / COLUMN_PIXEL_SIZE);
	column->ScaleVector(spawnTime.ms, spawnTime.ms, columnStartScale, columnEndScale);

	const auto collection = buildSpriteCollection(circle, column);
	return collection;
}

std::vector<SpriteCollection> Drip::renderSecondDrips() {
	// Generate extra variations so only a portion is covered
	const auto variations = generatePositions(SECOND_SPAWN_TIMES.size() * 4);

	auto indexes = std::vector<int>(variations.size() - 1);
	for (int i = 0; i < variations.size() - 1; ++i) {
		indexes[i] = i;
	}
	std::random_shuffle(indexes.begin(), indexes.end());

	auto collections = std::vector<SpriteCollection>();
	const auto endTime = SECOND_SPAWN_TIMES.back();
	for (int i = 0; i < SECOND_SPAWN_TIMES.size() - 1; ++i) {
		const auto startTime = SECOND_SPAWN_TIMES[i];
		const auto index = indexes.back();
		indexes.pop_back();
		const auto left = variations[index];
		const auto right = variations[index + 1];
		const auto collection = draw(startTime, endTime, left, right, true);
		collections.push_back(collection);
	}

	return collections;
}