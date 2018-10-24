#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Walker.hpp"

#include <vector>

class SplatterWalker : public Walker {
public:
	SplatterWalker(const std::vector<SpriteCollection> &sprites);

protected:
	SpriteCollection create(const Time& startTime, const Vector2& centerPos);
	void moveCurrent(const Time& startTime, const Time& endTime);
	void moveSprites(const Time& startTime, const Time& endTime, const float spawnsPerSecond);
private:
	void specialMove(SpriteCollection& sprite, const int startTime, const int endTime, const Vector2& startPos, const Vector2& endPos, const float startScale, const float endScale, const Easing& easing = Easing::Linear, const int precision = 3);
	static constexpr float offset = 200.0f;
};
