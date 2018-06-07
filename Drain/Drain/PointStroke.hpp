#pragma once
#include "Stroke.hpp"
class PointStroke : public Stroke {
public:
	explicit PointStroke(const Vector2& start);
	float calculateLength() const;
	void createSprites();
	void draw(const Vector2& position, const CharacterConfig& config);
};