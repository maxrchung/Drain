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

	void colorBgToBgSprites(const int startTime, const int endTime);
	void colorBgToFgSprites(const int startTime, const int endTime);
	void colorFgToBgSprites(const int startTime, const int endTime);
	void colorFgToFgSprites(const int startTime, const int endTime);

	SpriteCollection sprites;

private:


	int highlight_count;
	SpriteCollection create_sprites();

	float w_rand(float min, float max);

	int const sprite_size = 100;

	int max_highlight;
	int min_highlight;
};
