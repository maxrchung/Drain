#pragma once

#include <vector>

#include "Easing.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"


class SpriteCollection {
public:
	SpriteCollection(Sprite *sprite);
	~SpriteCollection();

	//number of sprites in collection
	unsigned int length;

	//sprites
	std::vector<Sprite *> sprites;

	//location of each sprite relative to the first sprite
	//location[0] should always be (0, 0)
	std::vector<Vector2> location;

	//coordinate of the collection as a whole
	//the first sprite should match exactly with this one
	Vector2 position;

	//add sprite to the end
	void push_back(Sprite *sprite, Vector2 coordinate);

	//remove sprite from the end
	Sprite *pop(void);

	void Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing = Easing::Linear);
	void MoveX(int startTime, int endTime, float startX, float endX, Easing easing = Easing::Linear);
	void MoveY(int startTime, int endTime, float startY, float endY, Easing easing = Easing::Linear);
	void Fade(int startTime, int endTime, float startOpacity, float endOpacity, Easing easing = Easing::Linear);
	void Rotate(int startTime, int endTime, float startRotate, float endRotate, Easing easing = Easing::Linear, int precision = 3);
	void Scale(int startTime, int endTime, float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3);
	void ScaleVector(int startTime, int endTime, float startX, float startY, float endX, float endY, Easing easing = Easing::Linear, int precision = 3);
	void ScaleVector(int startTime, int endTime, Vector2 startScale, Vector2 endScale, Easing easing = Easing::Linear, int precision = 3);
	void Color(int startTime, int endTime, int startR, int startG, int startB, int endR, int endG, int endB, Easing easing = Easing::Linear, int precision = 3);
	void Color(int startTime, int endTime, ::Color startColor, ::Color endColor, Easing easing = Easing::Linear, int precision = 3);
	void Loop(int startTime, int loopCount, const std::vector<std::string>& loopCommands);
};
