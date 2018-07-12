#include "Character.hpp"
#include "BlankStroke.hpp"
#include "CircularStroke.hpp"
#include "LineStroke.hpp"
#include "Math.hpp"
#include "PointStroke.hpp"
#include <exception>
Character::Character(const char character)
	: strokes{ createStrokes(character) } {
}
float Character::calculateCenter(const float scale) const {
	if (strokes.empty()) {
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
	if (strokes.empty()) {
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
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.5f)));
			break;
		case 'b':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 1.25f), Vector2(-0.5f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, -0.5f), Vector2(-0.5f, 0.0f)));
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
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, 1.25f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 1.25f), Vector2(0.5f, -0.5f)));
			break;
		case 'e':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.0f), Vector2(0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(Math::sqrt2 * 0.25f, -Math::sqrt2 * 0.25f), Vector2::Zero));
			break;
		case 'f':
			strokes.push_back(CircularStroke::create(Vector2(0.25f + Math::sqrt2 * 0.125f, 1.0f + Math::sqrt2 * 0.125f), Vector2(0.25f, 1.25f), Vector2(0.25f, 1.0f)));
			strokes.push_back(CircularStroke::create(Vector2(0.25f, 1.25f), Vector2(0.0f, 1.0f), Vector2(0.25f, 1.0f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, 1.0f), Vector2(0.0f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.25f - Math::sqrt2 * 0.125f, 0.5f), Vector2(0.5f, 0.5f)));
			break;
		case 'g':
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.75f)));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, -0.75f), Vector2(0.0f, -1.25f), Vector2(0.0f, -0.75f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -1.25f), Vector2(-Math::sqrt2 * 0.25f, -0.75f - Math::sqrt2 * 0.25f), Vector2(0.0f, -0.75f)));
			break;
		case 'h':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 1.25f), Vector2(-0.5f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, -0.5f), Vector2(-0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, -0.5f)));
			break;
		case 'i':
			strokes.push_back(std::make_unique<PointStroke>(Vector2(0.0f, 1.0f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, 0.5f), Vector2(0.0f, -0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.25f), Vector2(0.25f, -0.5f), Vector2(0.25f, -0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(0.25f, -0.5f), Vector2(0.25f + Math::sqrt2 * 0.125f, -0.25 - Math::sqrt2 * 0.125f), Vector2(0.25f, -0.25f)));
			break;
		case 'j':
			strokes.push_back(std::make_unique<PointStroke>(Vector2(0.5f, 1.0f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.75f)));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, -0.75f), Vector2(0.0f, -1.25f), Vector2(0.0f, -0.75f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -1.25f), Vector2(-Math::sqrt2 * 0.25f, -0.75f - Math::sqrt2 * 0.25f), Vector2(0.0f, -0.75f)));
			break;
		case 'k':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 1.25f), Vector2(-0.5f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.25f, 0.5f), Vector2(-0.5f, 0.0f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.0f), Vector2(0.25f, -0.5f)));
			break;
		case 'l':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, 1.25f), Vector2(0.0f, -0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.25f), Vector2(0.25f, -0.5f), Vector2(0.25f, -0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(0.25f, -0.5f), Vector2(0.25f + Math::sqrt2 * 0.125f, -0.25 - Math::sqrt2 * 0.125f), Vector2(0.25f, -0.25f)));
			break;
		case 'm':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.75f, 0.5f), Vector2(-0.75f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.75f, -0.5f), Vector2(-0.75f, 0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.75f, 0.125f), Vector2(-0.375f, 0.5f), Vector2(-0.375f, 0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.375f, 0.5f), Vector2(0.0f, 0.125f), Vector2(-0.375f, 0.125f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, 0.125f), Vector2(0.0f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, -0.5f), Vector2(0.0f, 0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.125f), Vector2(0.375f, 0.5f), Vector2(0.375f, 0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(0.375f, 0.5f), Vector2(0.75f, 0.125f), Vector2(0.375f, 0.125f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.75f, 0.125f), Vector2(0.75f, -0.5f)));
			break;
		case 'n':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(-0.5f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, -0.5f), Vector2(-0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, -0.5f)));
			break;
		case 'o':
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			break;
		case 'p':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(-0.5f, -1.25f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, -1.25f), Vector2(-0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			break;
		case 'q':
			strokes.push_back(CircularStroke::create(Vector2(0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(-0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -1.25f)));
			break;
		case 'r':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(-0.5f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, -0.5f), Vector2(-0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, 0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, 0.5f), Vector2(Math::sqrt2 * 0.25f, Math::sqrt2 * 0.25f), Vector2::Zero));
			break;
		case 's': {
			const auto offset = 0.025f;
			strokes.push_back(CircularStroke::create(Vector2(0.5f - offset, 0.25f), Vector2(0.25f - offset, 0.5f), Vector2(0.25f - offset, 0.25f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.25f - offset, 0.5f), Vector2(-0.25f + offset, 0.5f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.25f + offset, 0.5f), Vector2(-0.5f + offset, 0.25f), Vector2(-0.25f + offset, 0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f + offset, 0.25f), Vector2(-0.25f + offset, 0.0f), Vector2(-0.25f + offset, 0.25f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.25f + offset, 0.0f), Vector2(0.25f - offset, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(0.25f - offset, 0.0f), Vector2(0.5f - offset, -0.25f), Vector2(0.25f - offset, -0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(0.5f - offset, -0.25f), Vector2(0.25f - offset, -0.5f), Vector2(0.25f - offset, -0.25f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.25f - offset, -0.5f), Vector2(-0.25f + offset, -0.5f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.25f + offset, -0.5f), Vector2(-0.5f + offset, -0.25f), Vector2(-0.25f + offset, -0.25f)));
			break;
		}
		case 't':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(0.5f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, 1.25f), Vector2(0.0f, -0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.25f), Vector2(0.25f, -0.5f), Vector2(0.25f, -0.25f)));
			strokes.push_back(CircularStroke::create(Vector2(0.25f, -0.5f), Vector2(0.25f + Math::sqrt2 * 0.125f, -0.25 - Math::sqrt2 * 0.125f), Vector2(0.25f, -0.25f)));
			break;
		case 'u':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(-0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.5f)));
			break;
		case 'v':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(0.0f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.5f)));
			break;
		case 'w':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.75f, 0.5f), Vector2(-0.75f, -0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.75f, -0.125f), Vector2(-0.375f, -0.5f), Vector2(-0.375f, -0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.375f, -0.5f), Vector2(0.0f, -0.125f), Vector2(-0.375f, -0.125f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, -0.125f), Vector2(0.0f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.0f, 0.5f), Vector2(0.0f, -0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.125f), Vector2(0.375f, -0.5f), Vector2(0.375f, -0.125f)));
			strokes.push_back(CircularStroke::create(Vector2(0.375f, -0.5f), Vector2(0.75f, -0.125f), Vector2(0.375f, -0.125f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.75f, -0.125f), Vector2(0.75f, 0.5f)));
			break;
		case 'x':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(0.5f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(-0.5f, -0.5f)));
			break;
		case 'y':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(-0.5f, 0.0f)));
			strokes.push_back(CircularStroke::create(Vector2(-0.5f, 0.0f), Vector2(0.0f, -0.5f), Vector2::Zero));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), Vector2::Zero));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.0f), Vector2(0.5f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.75f)));
			strokes.push_back(CircularStroke::create(Vector2(0.5f, -0.75f), Vector2(0.0f, -1.25f), Vector2(0.0f, -0.75f)));
			strokes.push_back(CircularStroke::create(Vector2(0.0f, -1.25f), Vector2(-Math::sqrt2 * 0.25f, -0.75f - Math::sqrt2 * 0.25f), Vector2(0.0f, -0.75f)));
			break;
		case 'z':
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, 0.5f), Vector2(0.5f, 0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(0.5f, 0.5f), Vector2(-0.5f, -0.5f)));
			strokes.push_back(std::make_unique<LineStroke>(Vector2(-0.5f, -0.5f), Vector2(0.5f, -0.5f)));
			break;
		case ' ':
			strokes.push_back(std::make_unique<BlankStroke>());
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