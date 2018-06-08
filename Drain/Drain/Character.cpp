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
		auto startX = stroke->start.x * scale;
		if (startX < left) {
			left = startX;
		}
		if (startX > right) {
			right = startX;
		}
		auto endX = stroke->end.x * scale;
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
float Character::calculateLength() {
	auto length = 0.0f;
	for (const auto& stroke : strokes) {
		length += stroke->calculateLength();
	}
	return length;
}
std::vector<std::unique_ptr<Stroke>> Character::createStrokes(const char character) const {
	std::vector<std::unique_ptr<Stroke>> strokes;
	switch (character) {
		case 'a':
			strokes.push_back(std::make_unique<CircularStroke>(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<CircularStroke>(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(std::make_unique<CircularStroke>(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<CircularStroke>(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(-0.5f, -0.5f)));
			break;
		default:
			throw new std::exception("Unsupported lyric character: " + character);
	}
	return strokes;
}
void Character::draw(const Vector2& position,
					 const int start,
					 const int end,
					 const int drawSpeed,
					 const Color& foreground,
					 const Color& background,
					 const float scale) const {
	// Create sprites backwards so they stack in order
	for (int i = strokes.size() - 1; i >= 0; --i) {
		strokes[i]->createSprites(position, scale);
	}
	const auto totalTime = end - start;
	const auto totalLength = calculateLength();
	// For more accurate time measurements, setting this to float
	auto time = static_cast<float>(start);
	for (auto& stroke : strokes) {
		const auto partialLength = stroke->calculateLength();
		const auto lengthFraction = partialLength / totalLength;
		const auto timeFraction = lengthFraction / totalTime;
		// Definitely possible to get float rounding errors here, but few enough strokes should not make this too bad
		const auto strokeStart = static_cast<int>(time);
		time += timeFraction;
		const auto strokeEnd = static_cast<int>(time);
		stroke->draw(position, strokeStart, strokeEnd, drawSpeed, foreground, background, scale);
	}
}