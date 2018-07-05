#include "Character.hpp"
#include "CircularStroke.hpp"
#include "LineStroke.hpp"
#include "Math.hpp"
#include "PointStroke.hpp"
#include <exception>
Character::Character(const char character)
	: strokes{ createStrokes(character) } {
}
float Character::calculateCenter(const float scale) const {
	if (strokes.size() <= 1) {
		return 0;
	}
	auto left = std::numeric_limits<float>::max();
	for (const auto& stroke : strokes) {
		auto startX = stroke->getStartPosition().x * scale;
		if (startX < left) {
			left = startX;
		}
		auto endX = stroke->getEndPosition().x * scale;
		if (endX < left) {
			left = endX;
		}
	}
	const auto centerWidth = fabsf(left);
	return centerWidth;
}
float Character::calculateWidth(const float scale) const {
	if (strokes.size() <= 1) {
		return 0;
	}
	auto left = std::numeric_limits<float>::max();
	auto right = std::numeric_limits<float>::min();
	for (const auto& stroke : strokes) {
		auto startX = stroke->getStartPosition().x * scale;
		if (startX < left) {
			left = startX;
		}
		if (startX > right) {
			right = startX;
		}
		auto endX = stroke->getEndPosition().x * scale;
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
void Character::createPoints(const Vector2& position, const float scale) const {
	for (auto stroke = strokes.rbegin(); stroke != strokes.rend(); ++stroke) {
		stroke->get()->createPoints(position, scale);
	}
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
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.5f)));
			break;
		case 'b':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 1.0f), Vector2(-0.5f, -0.5f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			break;
		case 'c':
			strokes.push_back(CircularStroke::create(Vector2(Math::sqrt2 * 0.25f, Math::sqrt2 * 0.25f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(Math::sqrt2 * 0.25f, -Math::sqrt2 * 0.25f), Vector2::Zero));
			break;
		case 'd':
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 1.0f), Vector2(0.5f, -0.5f)));
			break;
		case 'e':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.0f), Vector2(0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(Math::sqrt2 * 0.25f, -Math::sqrt2 * 0.25f), Vector2::Zero));
			break;
		case 'f':
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.75f), Vector2(0.25f, 1.0f), Vector2(0.25f, 0.75f)));
			strokes.push_back(CircularStroke::create(Vector2(0.25f, 1.0f), Vector2(0.0f, 0.75f), Vector2(0.25f, 0.75f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, 0.75f), Vector2(0.0f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.25f), Vector2(0.5f, 0.25f)));
			break;
		case 'g':
			break;
		case 'h':
			break;
		case 'i':
			break;
		case 'j':
			break;
		case 'k':
			break;
		case 'l':
			break;
		case 'm':
			break;
		case 'n':
			break;
		case 'o':
			break;
		case 'p':
			break;
		case 'q':
			break;
		case 'r':
			break;
		case 's':
			break;
		case 't':
			break;
		case 'u':
			break;
		case 'v':
			break;
		case 'w':
			break;
		case 'x':
			break;
		case 'y':
			break;
		case 'z':
			break;
		case ' ':
			break;
		default:
			throw new std::exception("Unsupported lyric character: " + character);
	}
	return strokes;
}
void Character::draw(const Vector2& position,
					 const int startTime,
					 const int endTime,
					 const float scale) const {
	createSprites(position, scale);
	createPoints(position, scale);
	const auto totalTime = endTime - startTime - drawBuffer;
	const auto totalLength = calculateLength();
	auto partialLength = 0.0f;
	// For more accurate time measurements, setting this to float
	for (const auto& stroke : strokes) {
		const auto strokeLength = stroke->calculateLength();
		const auto lengthFraction = strokeLength / totalLength;
		const auto drawFraction = lengthFraction * totalTime;
		// Definitely possible to get float rounding errors here, but few enough strokes should not make this too bad
		const auto startDraw = static_cast<int>(startTime + partialLength);
		const auto endDraw = static_cast<int>(startTime + partialLength + drawFraction);
		stroke->draw(position, startDraw, endDraw, endTime, endTime + drainTime, scale);
		partialLength += drawFraction;
	}
}