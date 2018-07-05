#pragma once

#include <vector>

#include "Easing.hpp"
#include "Sprite.hpp"
#include "Vector2.hpp"

typedef struct {
	std::vector<int> startTimeVector;
	std::vector<int> endTimeVector;
	std::vector<Vector2> startPositionVector;
	std::vector<Vector2> endPositionVector;
} moveStruct;

class SpriteCollection {
public:
	SpriteCollection(std::vector<Sprite *> sprites);
	~SpriteCollection();

	//number of sprites in collection
	unsigned int size = 0;

	//sprites
	std::vector<Sprite *> sprites;

	//location of each sprite relative to the first sprite
	//location[0] should always be (0, 0)
	std::vector<Vector2> location;

	//coordinate of the collection as a whole
	//the first sprite should match exactly with this one
	Vector2 position;

	void commitMove(void);

	//any sprite->moves will require a commit
	//e.g. the SpriteCollection::Scale will still call the Sprite::Scale without commit
	//but the move portion of the collection's scale must be commited, otherwise only the scale will happen
	void Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing = Easing::Linear);
	void MoveX(int startTime, int endTime, float startX, float endX, Easing easing = Easing::Linear);
	void MoveY(int startTime, int endTime, float startY, float endY, Easing easing = Easing::Linear);
	void Rotate(int startTime, int endTime, float startRotate, float endRotate, Easing easing = Easing::Linear, int precision = 3);
	void Scale(int startTime, int endTime, float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3);
	void ScaleVector(int startTime, int endTime, float startX, float startY, float endX, float endY, Easing easing = Easing::Linear, int precision = 3);
	void ScaleVector(int startTime, int endTime, Vector2 startScale, Vector2 endScale, Easing easing = Easing::Linear, int precision = 3);

	//theses functions do not require a commit, and will write to file by just being called
	void Fade(int startTime, int endTime, float startOpacity, float endOpacity, Easing easing = Easing::Linear);
	void Color(int startTime, int endTime, int startR, int startG, int startB, int endR, int endG, int endB, Easing easing = Easing::Linear, int precision = 3);
	void Color(int startTime, int endTime, ::Color startColor, ::Color endColor, Easing easing = Easing::Linear, int precision = 3);

private:

	std::vector<moveStruct> stack;

	void pushMove(int number, int startTime, int endTime, Vector2 startPos, Vector2 endPos);
};