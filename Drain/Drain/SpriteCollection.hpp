#pragma once

#include <vector>

#include "Easing.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"


class SpriteCollection {
public:
	SpriteCollection(std::vector<Sprite *> sprites, std::vector<Vector2> location);
	SpriteCollection(Sprite *sprites);
	~SpriteCollection();

	//number of sprites in collection
	unsigned int size;

	//sprites
	std::vector<Sprite *> sprites;

	//location of each sprite relative to position
	std::vector<Vector2> location;

	//coordinate of the first sprite
	//will act as the position of the collection
	Vector2& position;
	float& scale;

	void Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing = Easing::Linear);
	void MoveX(int startTime, int endTime, float startX, float endX, Easing easing = Easing::Linear);
	void MoveY(int startTime, int endTime, float startY, float endY, Easing easing = Easing::Linear);
	void Rotate(int startTime, int endTime, float startRotate, float endRotate, Easing easing = Easing::Linear, int precision = 3);
	void Scale(int startTime, int endTime, float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3);
	void ScaleVector(int startTime, int endTime, float startX, float startY, float endX, float endY, Easing easing = Easing::Linear, int precision = 3);
	void ScaleVector(int startTime, int endTime, Vector2 startScale, Vector2 endScale, Easing easing = Easing::Linear, int precision = 3);

	void MoveAndScale(int startTime, int endTime, Vector2 startPos, Vector2 endPos, float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3);

	//theses functions do not require a commit, and will write to file by just being called
	void Fade(int startTime, int endTime, float startOpacity, float endOpacity, Easing easing = Easing::Linear);
	void Color(int startTime, int endTime, int startR, int startG, int startB, int endR, int endG, int endB, Easing easing = Easing::Linear, int precision = 3);
	void Color(int startTime, int endTime, ::Color startColor, ::Color endColor, Easing easing = Easing::Linear, int precision = 3);
};
