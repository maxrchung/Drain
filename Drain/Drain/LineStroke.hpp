#pragma once
#include "Stroke.hpp"
class LineStroke : public Stroke {
public:
	explicit LineStroke(const Vector2& start, const Vector2& end);
	void draw(const Vector2& position, const CharacterConfig& config);
	float calculateLength() const;
	float createSprites();
};