#pragma once
#include "CharacterConfig.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include <memory>
class Character {
public:
	static std::unique_ptr<Character> get(const char character);
	virtual void draw(const Vector2& position, const CharacterConfig& config) const = 0;
	virtual float getWidth() const { return 1.0f; }
	// Size of sprite images in pixels
	static const int imageSize = 100;
};