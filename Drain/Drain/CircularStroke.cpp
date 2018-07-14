#include "CircularStroke.hpp"
#include "CCWEndEighthStroke.hpp"
#include "CCWQuarterStroke.hpp"
#include "CCWStartEighthStroke.hpp"
#include "CWEndEighthStroke.hpp"
#include "CWQuarterStroke.hpp"
#include "CWStartEighthStroke.hpp"

#include <cmath>

CircularStroke::CircularStroke(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center)
	: startPosition{ startPosition }, endPosition{ endPosition }, center{ center } {
}
std::unique_ptr<CircularStroke> CircularStroke::create(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center) {
	const auto startOffset = isStartOffset(startPosition, center);
	const auto endOffset = isEndOffset(endPosition, center);
	const auto clockwise = isClockwise(startPosition, endPosition, center);
	if (!startOffset && !endOffset && clockwise) {
		return std::make_unique<CWQuarterStroke>(startPosition, endPosition, center);
	}
	else if (!startOffset && !endOffset && !clockwise) {
		return std::make_unique<CCWQuarterStroke>(startPosition, endPosition, center);
	}
	else if (startOffset && !endOffset && clockwise) {
		return std::make_unique<CWStartEighthStroke>(startPosition, endPosition, center);
	}
	else if (startOffset && !endOffset && !clockwise) {
		return std::make_unique<CCWStartEighthStroke>(startPosition, endPosition, center);
	}
	else if (!startOffset && endOffset && clockwise) {
		return std::make_unique<CWEndEighthStroke>(startPosition, endPosition, center);
	}
	else if (!startOffset && endOffset && !clockwise) {
		return std::make_unique<CCWEndEighthStroke>(startPosition, endPosition, center);
	}
}
float CircularStroke::calculateLength() const {
	const auto startFromCenter = startPosition - center;
	const auto endFromCenter = endPosition - center;
	const auto angleBetween = startFromCenter.AngleBetween(endFromCenter);
	// Add thickness so PointStroke has length
	const auto length = fabsf(angleBetween) * (endPosition - center).Magnitude() + thickness;
	return length;
}
Vector2 CircularStroke::getEndPosition() const {
	return endPosition;
}
Vector2 CircularStroke::getStartPosition() const {
	return startPosition;
}
bool CircularStroke::isClockwise(const Vector2& startPosition, const Vector2& endPosition, const Vector2& center) {
	const auto angleBetween = (startPosition - center).AngleBetween(endPosition - center);
	const auto clockwise = angleBetween > 0;
	return clockwise;
}
bool CircularStroke::isStartOffset(const Vector2& startPosition, const Vector2& center) {
	if (startPosition.x != center.x && startPosition.y != center.y) {
		return true;
	}
	else {
		return false;
	}
}
bool CircularStroke::isEndOffset(const Vector2& endPosition, const Vector2& center) {
	if (endPosition.x != center.x && endPosition.y != center.y) {
		return true;
	}
	else {
		return false;
	}
}
