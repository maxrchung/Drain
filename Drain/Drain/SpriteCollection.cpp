#include <algorithm>
#include <memory>

#include "SpriteCollection.hpp"

SpriteCollection::SpriteCollection(std::vector<Sprite *> sprites, std::vector<Vector2> location, std::vector<float> scale)
	: sprites(sprites), position{sprites[0]->position}, location{location}, scale{scale} , overallScale{1}{
		size = sprites.size();
}

SpriteCollection::SpriteCollection(Sprite *sprite)
	: position{ sprite->position }, scale{ sprite->scale }, overallScale{1} {
		size = 1;
		this->sprites.push_back(sprite);
		location.push_back(Vector2(0, 0));
}


SpriteCollection::~SpriteCollection() {
}


void SpriteCollection::Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing) {
	for(int i = 0; i < size; ++i) {
		Vector2 offset = location[i] * overallScale;
		Vector2 start = startPos + offset;
		Vector2 end = endPos + offset;
		sprites[i]->Move(startTime, endTime, start, end, easing);
	}
}


void SpriteCollection::MoveX(int startTime, int endTime, float startX, float endX, Easing easing) {
	for(int i = 0; i < size; ++i) {
		sprites[i]->MoveX(startTime, endTime, startX + location[i].x * overallScale, endX + location[i].x * overallScale, easing);
	}
}


void SpriteCollection::MoveY(int startTime, int endTime, float startY, float endY, Easing easing) {
	for(int i = 0; i < size; ++i) {
		sprites[i]->MoveY(startTime, endTime, startY + location[i].y * overallScale, endY + location[i].y * overallScale, easing);
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
	for (int i = 0; i < size; ++i) {
		sprites[i]->Scale(startTime, endTime, startScale * this->scale[i], endScale * this->scale[i], easing, precision);
		sprites[i]->Move(startTime, endTime, this->location[i] * startScale + position, this->location[i] * endScale + position);
	}

	this->overallScale = endScale;
}


void SpriteCollection::ScaleVector(int startTime, int endTime, float startX, float startY, float endX, float endY, Easing easing, int precision) {

	for (int i = 0; i < size; ++i) {
		sprites[i]->ScaleVector(startTime, endTime, startX * this->scale[i], startY * this->scale[i], endX * this->scale[i], endY * this->scale[i], easing, precision);

		Vector2 startPos(location[i].x * startX + position.x, location[i].y * startY + position.y);
		Vector2 endPos(location[i].x * endX + position.x, location[i].y * endY + position.y);

		sprites[i]->Move(startTime, endTime, startPos, endPos);
	}
}


void SpriteCollection::ScaleVector(int startTime, int endTime, Vector2 startScale, Vector2 endScale, Easing easing, int precision) {
	float startX = startScale.x;
	float endX = endScale.x;
	float startY = startScale.y;
	float endY = endScale.y;

	for (int i = 0; i < size; ++i) {
		sprites[i]->ScaleVector(startTime, endTime, startX * this->scale[i], startY * this->scale[i], endX * this->scale[i], endY * this->scale[i], easing, precision);
		Vector2 startPos = startScale * location[i] + position;
		Vector2 endPos = endScale * location[i] + position;

		sprites[i]->Move(startTime, endTime, startPos, endPos);
	}
}

//if there is a move and a scale, and if the move and scale both start and end at the same time
void SpriteCollection::MoveAndScale(int startTime, int endTime, Vector2 startPos, Vector2 endPos, float startScale, float endScale, Easing easing, int precision) {
	for(int i = 0; i < size; ++i) {
		sprites[i]->Scale(startTime, endTime, startScale * this->scale[i], endScale * this->scale[i], easing, precision);
		Vector2 start = this->location[i] * startScale + startPos;
		Vector2 end = this->location[i] * endScale + endPos;

		sprites[i]->Move(startTime, endTime, start, end);
	}

	this->overallScale = endScale;
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
