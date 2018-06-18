#include "SpriteCollection.hpp"



SpriteCollection::SpriteCollection(Sprite *sprite) {
	this->push_back(sprite, Vector2(0, 0));
	position = sprite->position;
}


SpriteCollection::~SpriteCollection() {
}


//coordinate is the relative position of the new sprite to the first sprite at (0, 0)
void SpriteCollection::push_back(Sprite *sprite, Vector2 coordinate) {
	sprites.push_back(sprite);
	location.push_back(coordinate);
	sprite->position = position + coordinate;
	std::cout << sprite->position << "\n";
	++length;
}


Sprite *SpriteCollection::pop(void) {
	Sprite *out = NULL;
	/*
	Sprite *out = sprites.end;
	sprites.pop_back();

	location.pop_back();
	--length;
	*/
	return out;
}

void SpriteCollection::Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing) {
	for (auto& sprite : sprites) {
		sprite->Move(startTime, endTime, startPos, endPos, easing);
	}
}


void SpriteCollection::MoveX(int startTime, int endTime, float startX, float endX, Easing easing) {
	for (auto& sprite : sprites) {
		sprite->MoveX(startTime, endTime, startX, endX, easing);
	}

}


void SpriteCollection::MoveY(int startTime, int endTime, float startY, float endY, Easing easing) {
	for (auto& sprite : sprites) {
		sprite->MoveY(startTime, endTime, startY, endY, easing);
	}
}


void SpriteCollection::Fade(int startTime, int endTime, float startOpacity, float endOpacity, Easing easing) {
	for (auto& sprite : sprites) {
		sprite->Fade(startTime, endTime, startOpacity, endOpacity, easing);
	}
}


void SpriteCollection::Rotate(int startTime, int endTime, float startRotate, float endRotate, Easing easing, int precision) {
	for(int i = 0; i < length; ++i){
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
		sprite->Move(startTime, endTime, sprite->position * startScale, sprite->position * endScale);
	}
}


void SpriteCollection::ScaleVector(int startTime, int endTime, float startX, float startY, float endX, float endY, Easing easing, int precision) {
	for (auto& sprite : sprites) {
		sprite->ScaleVector(startTime, endTime, startX, startY, endX, endY, easing, precision);
		sprite->MoveX(startTime, endTime, sprite->position.x * startX, sprite->position.x * endX, easing);
		sprite->MoveY(startTime, endTime, sprite->position.y * startY, sprite->position.y * endY, easing);
	}
}


void SpriteCollection::ScaleVector(int startTime, int endTime, Vector2 startScale, Vector2 endScale, Easing easing, int precision) {
	float startX = startScale.x;
	float startY = startScale.y;

	float endX = endScale.x;
	float endY = endScale.y;

	for (auto& sprite : sprites) {
		sprite->ScaleVector(startTime, endTime, startScale, endScale, easing, precision);
		sprite->MoveX(startTime, endTime, sprite->position.x * startX, sprite->position.x * endX, easing);
		sprite->MoveY(startTime, endTime, sprite->position.y * startY, sprite->position.y * endY, easing);
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


void SpriteCollection::Loop(int startTime, int loopCount, const std::vector<std::string>& loopCommands) {
	for (auto& sprite : sprites) {
		sprite->Loop(startTime, loopCount, loopCommands);
	}
}