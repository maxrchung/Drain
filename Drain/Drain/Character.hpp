#pragma once
#include "CharacterConfig.hpp"
#include "Color.hpp"
#include "Stroke.hpp"
#include "Vector2.hpp"
#include <memory>
class Character {
public:
	explicit Character(const char character);
	float calculateWidth() const;
	virtual void draw(const Vector2& position, const CharacterConfig& config) const;
protected:
	// Size of sprite images in pixels
	static const int imageSize = 100;
	// Thickness of Character stroke
	static constexpr float thickness = 0.1f * imageSize;
	std::vector<std::unique_ptr<Stroke>> strokes;
};