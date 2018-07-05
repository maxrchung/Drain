#include <algorithm>
#include <memory>

#include "SpriteCollection.hpp"



SpriteCollection::SpriteCollection(std::vector<Sprite *> sprites)
	: sprites(sprites) {
	size = sprites.size();
	stack.reserve(size);
}

SpriteCollection::~SpriteCollection() {
}

bool compareValue(int *a, int *b) {
	return (*a) > (*b);
}

//writes movements
//only works for linear movement
void SpriteCollection::commitMove(void) {
	//for all the sprites in the collection
	for (int i = 0; i < this->size; ++i) {
		//get the number of commands for each sprite in the collection
		int size = this->stack[i].startTimeVector.size();
		std::vector<int *> startSort(size);
		std::vector<int *> endSort(size);

		//for all commands, have a pointer to the start and end times
		for(int j = 0; j < size; ++j){
			startSort[j] = &(this->stack[j].startTimeVector[j]);
			endSort[j] = &(this->stack[j].endTimeVector[j]);
		}

		std::sort(startSort.begin(), startSort.end(), compareValue);
		std::sort(endSort.begin(), endSort.end(), compareValue);
	}
}

void SpriteCollection::Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing) {
	for (int i = 0; i < size; ++i) {
		pushMove(i, startTime, endTime, startPos, endPos);
	}
}


void SpriteCollection::MoveX(int startTime, int endTime, float startX, float endX, Easing easing) {
	for (int i = 0; i < size; ++i) {
		Vector2 startPos(startX + location[i].x, location[i].y);
		Vector2 endPos(endX + location[i].x, location[i].y);

		pushMove(i, startTime, endTime, startPos, endPos);
	}
}


void SpriteCollection::MoveY(int startTime, int endTime, float startY, float endY, Easing easing) {
	for (int i = 0; i < size; ++i) {
		Vector2 startPos(location[i].x, startY + location[i].y);
		Vector2 endPos(location[i].x, endY + location[i].y);

		pushMove(i, startTime, endTime, startPos, endPos);
	}
}


void SpriteCollection::Fade(int startTime, int endTime, float startOpacity, float endOpacity, Easing easing) {
	for (auto& sprite : sprites) {
		sprite->Fade(startTime, endTime, startOpacity, endOpacity, easing);
	}
}


void SpriteCollection::Rotate(int startTime, int endTime, float startRotate, float endRotate, Easing easing, int precision) {
	for(int i = 0; i < size; ++i){
		Vector2 initial = position + location[i];

		initial = initial.Rotate(startRotate);

		float startX = initial.x;
		float startY = initial.y;

		Vector2 end = initial.Rotate(endRotate);

		float endX = end.x;
		float endY = end.y;

		sprites[i]->Rotate(startTime, endTime, startRotate, endRotate, easing, precision);

		sprites[i]->MoveX(startTime, endTime, startX, endX, Easing::SineOut);
		sprites[i]->MoveY(startTime, endTime, startY, endY, Easing::SineIn);
	}
}


void SpriteCollection::Scale(int startTime, int endTime, float startScale, float endScale, Easing easing, int precision) {
	for (auto& sprite : sprites) {
		sprite->Scale(startTime, endTime, startScale, endScale, easing, precision);
	}

	for (int i = 0; i < size; ++i) {
		this->pushMove(i, startTime, endTime, location[i] * startScale, location[i] * endScale);
	}
}


void SpriteCollection::ScaleVector(int startTime, int endTime, float startX, float startY, float endX, float endY, Easing easing, int precision) {
	float startX = startScale.x;
	float endX = endScale.x;
	float startY = startScale.y;
	float endY = endScale.y;
	
	for (auto& sprite : sprites) {
		sprite->ScaleVector(startTime, endTime, startX, startY, endX, endY, easing, precision);
	}
	for (int i = 0; i < size; ++i) {
		Vector2 startPos(location[i].x * startX, location[i].y * startY);
		Vector2 endPos(location[i].x * endX, location[i].y * endY);

		this->pushMove(i, startTime, endTime, startPos, endPos);
	}
}


void SpriteCollection::ScaleVector(int startTime, int endTime, Vector2 startScale, Vector2 endScale, Easing easing, int precision) {
	float startX = startScale.x;
	float endX = endScale.x;
	float startY = startScale.y;
	float endY = endScale.y;
	
	for (auto& sprite : sprites) {
		sprite->ScaleVector(startTime, endTime, startX, startY, endX, endY, easing, precision);
	}
	for (int i = 0; i < size; ++i) {

		Vector2 startPos = startScale * location[i];
		Vector2 endPos = endScale * location[i];

		this->pushMove(i, startTime, endTime, startPos, endPos);
	}
}


void SpriteCollection::Color(int startTime, int endTime, int startR, int startG, int startB, int endR, int endG, int endB, Easing easing, int precision) {
	for (auto& sprite : sprites) {
		sprite->Color(startTime, endTime, startR, startG, startB, endR, endG, endB, easing, precision);
	}
}


void SpriteCollection::Color(int startTime, int endTime, ::Color startColor, ::Color endColor, Easing easing, int precision) {
	for (auto& sprite : sprites) {
		sprite->Color(startTime, endTime, startColor, endColor, easing, precision);
	}
}

void SpriteCollection::pushMove(int number, int startTime, int endTime, Vector2 startPos, Vector2 endPos) {
	this->stack[number].startTimeVector.push_back(startTime);
	this->stack[number].endTimeVector.push_back(endTime);
	this->stack[number].startPositionVector.push_back(startPos);
	this->stack[number].endPositionVector.push_back(endPos);
}
