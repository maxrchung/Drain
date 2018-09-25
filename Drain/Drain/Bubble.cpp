#include "Bubble.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

#include <vector>

Bubble::Bubble()
	: sprites{create_sprites()}, highlight_oblong{std::vector<Vector2>()} {
}


void Bubble::Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing) {
	if(!scale)
		fixScale(startTime, startTime);

	this->sprites.Move(startTime, endTime, startPos, endPos, easing);
	return;
}


void Bubble::MoveX(int startTime, int endTime, float startX, float endX, Easing easing) {
	if(!scale)
		fixScale(startTime, startTime);

	this->sprites.MoveX(startTime, endTime, startX, endX, easing);
	return;
}


void Bubble::MoveY(int startTime, int endTime, float startY, float endY, Easing easing) {
	if(!scale)
		fixScale(startTime, startTime);

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
	for(int i = 1; i < highlight_count + 1; ++i) {
		Swatch::colorBgToBgSprites({sprites.sprites[i]}, startTime, endTime);
	}
}


void Bubble::Fade(const int startTime, const int endTime) {
	Swatch::colorFgToBgSprites({sprites.sprites[0]}, startTime, endTime);
	for(int i = 1; i < highlight_count + 1; ++i) {
		Swatch::colorBgToBgSprites({sprites.sprites[i]}, startTime, endTime);
	}
}


void Bubble::fixScale(int startTime, int endTime) {
	for(int i = 0; i < this->sprites.scale.size(); ++i) {
		this->sprites.sprites[i]->Scale(startTime, endTime, this->sprites.scale[i], this->sprites.scale[i]);
	}
	this->scale = 1;
}


SpriteCollection Bubble::create_sprites() {
	this->highlight_count = w_rand(this->min_highlight, this->max_highlight);

	std::vector<Sprite *> sprite_vector;
	std::vector<Vector2> location;
	std::vector<float> scale;

	//main bubble
	Sprite *bubble = Storyboard::CreateSprite(getPath(Path::Circle));
	sprite_vector.push_back(bubble);

	Vector2 oblong_scale = Vector2(w_rand(min_oblong_range, max_oblong_range), w_rand(min_oblong_range, max_oblong_range));
	this->highlight_oblong.push_back(oblong_scale);

	//this->highlight_oblong.push_back(Vector2(w_rand(min_oblong_range, max_oblong_range), w_rand(min_oblong_range, max_oblong_range)));
	//this->oblong = {w_rand(min_oblong_range, max_oblong_range), w_rand(min_oblong_range, max_oblong_range)};

	location.push_back({0, 0});
	scale.push_back(1);

	for(int i = 0; i < highlight_count; ++i) {
		Vector2 offset = Vector2::Zero;
		float range = 0.75;
		offset.x = (this->sprite_size / 2) * w_rand(-range, range);
		offset.y = (this->sprite_size / 2) * w_rand(-range, range);

		oblong_scale  = Vector2(w_rand(min_oblong_range, max_oblong_range), w_rand(min_oblong_range, max_oblong_range));
		//Vector2 highlight_thing = Vector2(w_rand(min_oblong_range, max_oblong_range), w_rand(min_oblong_range, max_oblong_range));
		//highlight_oblong[i] = highlight_thing;
		this->highlight_oblong.push_back(oblong_scale);
		Sprite *sprite = Storyboard::CreateSprite(getPath(Path::Circle), offset);
		float s = w_rand(0.02, 0.1);
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
