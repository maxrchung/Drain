#include "Character.hpp"
#include "CircularStroke.hpp"
#include "LineStroke.hpp"
#include "PointStroke.hpp"
#include <exception>
Character::Character(const char character)
	: strokes{ createStrokes(character) } {
}
float Character::calculateWidth(const float scale) const {
	if (strokes.size() <= 1) {
		return 0;
	}
	auto left = std::numeric_limits<float>::max();
	auto right = std::numeric_limits<float>::min();
	for (const auto& stroke : strokes) {
		auto startX = stroke->startPosition.x * scale;
		if (startX < left) {
			left = startX;
		}
		if (startX > right) {
			right = startX;
		}
		auto endX = stroke->endPosition.x * scale;
		if (endX < left) {
			left = endX;
		}
		if (endX > right) {
			right = endX;
		}
	}
	// Account for line thickness
	const auto width = right - left + Stroke::thickness * scale;
	return width;
}
float Character::calculateLength() const {
	auto length = 0.0f;
	for (const auto& stroke : strokes) {
		// Always account for thickness so PointStroke has actual thickness
		length += stroke->calculateLength();
	}
	return length;
}
void Character::createSprites(const Vector2& position, const float scale) const {
	// Create sprites backwards so strokes do not overlap
	for (auto stroke = strokes.rbegin(); stroke != strokes.rend(); ++stroke) {
		stroke->get()->createSprites(position, scale);
	}
}
std::vector<std::unique_ptr<Stroke>> Character::createStrokes(const char character) {
	std::vector<std::unique_ptr<Stroke>> strokes;
	switch (character) {
		case 'a':
			strokes.push_back(std::make_unique<CircularStroke>(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			//strokes.push_back(std::make_unique<CircularStroke>(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			//strokes.push_back(std::make_unique<CircularStroke>(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			//strokes.push_back(std::make_unique<CircularStroke>(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			//strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.5f)));
			break;
		default:
			throw new std::exception("Unsupported lyric character: " + character);
	}
	return strokes;
}
void Character::draw(const Vector2& position,
					   const int startTime,
					   const int endTime,
					   const int drawSpeed,
					   const Color& foreground,
					   const Color& background,
					   const float scale) const {
	createSprites(position, scale);
	const auto totalLength = calculateLength();
	// For more accurate time measurements, setting this to float
	for (int i = 0; i < strokes.size(); ++i) {
		const auto strokeLength = strokes[i]->calculateLength();
		const auto lengthFraction = strokeLength / totalLength;
		const auto timeFraction = lengthFraction * drawSpeed;
		// Definitely possible to get float rounding errors here, but few enough strokes should not make this too bad
		const auto startDraw = static_cast<int>(startTime + i * timeFraction);
		const auto endDraw = static_cast<int>(startTime + (i + 1) * timeFraction);
		// Drain from reverse
		const auto startDrain = static_cast<int>(endTime + (strokes.size() - 1 - i) * timeFraction);
		const auto endDrain = static_cast<int>(endTime + (strokes.size() - i) * timeFraction);
		strokes[i]->draw(position, startDraw, endDraw, startDrain, endDrain, endTime, drawSpeed, foreground, background, scale);
	}
}