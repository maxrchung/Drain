#pragma once
#include "Color.hpp"
#include "Stroke.hpp"
#include "Vector2.hpp"
#include <memory>
class Character {
public:
	explicit Character(const char character);
	float calculateWidth(const float scale) const;
	virtual void drain(const Vector2& position,
					   const int endTime,
					   const int drawSpeed,
					   const Color& foreground,
					   const Color& background,
					   const float scale) const;
	virtual void draw(const Vector2& position,
					  const int startTime,
					  const int endTime,
					  const int drawSpeed,
					  const Color& foreground,
					  const Color& background,
					  const float scale) const;
	void render(const Vector2& position,
				const int startTime,
				const int endTime,
				const int drawSpeed,
				const Color& foreground,
				const Color& background,
				const float scale) const;
protected:
	static std::vector<std::unique_ptr<Stroke>> createStrokes(const char character);
	void createSprites(const Vector2& position, const float scale) const;
	std::vector<std::unique_ptr<Stroke>> strokes;
private:
	float calculateLength() const;
};