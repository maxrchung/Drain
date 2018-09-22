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

	void Color(const int startTime, const int endTime);
	void Fade(const int startTime, const int endTime);

	void fixScale(int startTime, int endTime);
	SpriteCollection sprites;

private:
	float scale = 0;

	Vector2 oblong;
	int highlight_count;
	std::vector<Vector2> highlight_oblong;

	SpriteCollection create_sprites();

	float w_rand(float min, float max);

	static const int sprite_size = 100;

	static const int min_highlight = 5;
	static const int max_highlight = 9;

	static constexpr float min_oblong_range = 0.01f;
	static constexpr float max_oblong_range = 0.05f;
};
