#include "Bubble.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

#include <cmath>
#include <vector>


Bubble::Bubble(bool outline)
	: sprites{create_sprites(outline)} {
}


void Bubble::Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing) {
	this->sprites.Move(startTime, endTime, startPos, endPos, easing);
	return;
}


void Bubble::MoveX(int startTime, int endTime, float startX, float endX, Easing easing) {
	this->sprites.MoveX(startTime, endTime, startX, endX, easing);
	return;
}


void Bubble::MoveY(int startTime, int endTime, float startY, float endY, Easing easing) {
	this->sprites.MoveY(startTime, endTime, startY, endY, easing);
	return;
}


void Bubble::Scale(int startTime, int endTime, float startScale, float endScale, Easing easing, int precision) {
	this->sprites.Scale(startTime, endTime, startScale, endScale, easing, precision);
	return;
}


void Bubble::MoveAndScale(int startTime, int endTime, Vector2 startPos,Vector2 endPos,float startScale, float endScale, Easing easing, int precision) {
	this->sprites.MoveAndScale(startTime, endTime, startPos, endPos, startScale, endScale, easing, precision);
	return;
}


void Bubble::Color(const int startTime, const int endTime) {
	Swatch::colorFgToFgSprites({sprites.sprites[0]}, startTime, endTime);
	Swatch::colorBgToBgSprites({sprites.sprites[1]}, startTime, endTime);
	for(int i = 1; i < highlight_count + 1; ++i) {
		Swatch::colorBgToBgSprites({sprites.sprites[i]}, startTime, endTime);
	}

	return;
}


void Bubble::Fade(const int startTime, const int endTime) {
	Swatch::colorFgToBgSprites({sprites.sprites[0]}, startTime, endTime);
	Swatch::colorBgToBgSprites({sprites.sprites[1]}, startTime, endTime);
	for(int i = 1; i < highlight_count + 1; ++i) {
		Swatch::colorBgToBgSprites({sprites.sprites[i]}, startTime, endTime);
	}

	return;
}


SpriteCollection Bubble::create_sprites(bool outline) {
	if(outline) {
		this->highlight_count = 0;
	} else {
		this->highlight_count = w_rand(this->min_highlight, this->max_highlight);
	}

	std::vector<Sprite *> sprite_vector;
	std::vector<Vector2> location;
	std::vector<float> scale;

	//main bubble
	Sprite *bubble = Storyboard::CreateSprite(getPath(Path::Circle));
	sprite_vector.push_back(bubble);

	location.push_back({0, 0});
	scale.push_back(1);

	//inner highlight thing
	Sprite *inner = Storyboard::CreateSprite(getPath(Path::Circle));
	sprite_vector.push_back(inner);
	float min_o = -3;
	float max_o = 3;
	//Vector2 offset{w_rand(min_o, max_o),\
		       w_rand(min_o, max_o)};

	Vector2 offset{min_o, max_o};

	location.push_back(offset);
	scale.push_back(0.85);

	for(int i = 0; i < highlight_count; ++i) {

		float r = w_rand(37, 40);
		float theta = w_rand(0, 360);

		float offset_x = r * cos(theta);
		float offset_y = r * sin(theta);

		Vector2 offset{offset_x, offset_y};

		Sprite *sprite = Storyboard::CreateSprite(getPath(Path::Circle), offset * scale[0]);
		float s = w_rand(0.05, 0.15);
		scale.push_back(s);
		sprite_vector.push_back(sprite);

		location.push_back(offset);
	}
	
	return SpriteCollection(sprite_vector, location, scale);
}


float Bubble::w_rand(float min, float max) {
	float out = (float)rand() / RAND_MAX;
	out *= (max - min);
	out += min;

	return out;	       
}
