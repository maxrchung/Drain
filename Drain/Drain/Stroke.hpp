#pragma once
#include "CharacterConfig.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"
class Stroke {
public:
	explicit Stroke(const Vector2& start, const Vector2& end);
	virtual float calculateLength() const = 0;
	virtual void createSprites() = 0;
	virtual void draw(const Vector2& position, const CharacterConfig& config) = 0;
	const Vector2 start;
	const Vector2 end;
protected:
	std::vector<Sprite*> sprites;
};