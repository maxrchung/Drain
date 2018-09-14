#pragma once

#include "Easing.hpp"
#include "SpriteCollection.hpp"
#include "Vector2.hpp"

class Bubble {
public:
	Bubble();
	void Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing = Easing::Linear);
	void MoveX(int startTime, int endTime, float startX, float endX, Easing easing = Easing::Linear);
	void MoveY(int startTime, int endTime, float startY, float endY, Easing easing = Easing::Linear);
	void Scale(int startTime, int endTime, float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3);

	void MoveAndScale(int startTime, int endTime, Vector2 startPos, Vector2 endPos, float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3);
private:

	SpriteCollection sprites;

	SpriteCollection create_sprites();

	float w_rand(float min, float max);

	int const sprite_size = 100;

	int const max_highlight = 5;
	int const min_highlight = 2;
};
