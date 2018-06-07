#pragma once
#include "Stroke.hpp"
class CircularStroke : public Stroke {
public:
	explicit CircularStroke(const Vector2& start, const Vector2& end, const Vector2& center);
	float calculateLength() const;
	void createSprites();
	void draw(const Vector2& position, const CharacterConfig& config);
private:
	const Vector2 center;
};