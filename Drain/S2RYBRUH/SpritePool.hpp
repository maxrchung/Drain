#pragma once

#include "Sprite.hpp"
#include <deque>
#include <string>

// Saves space so you don't have to keep remaking sprites
class SpritePool {
public:
	SpritePool(const std::string& imagePath, const Layer& layer = Layer::Foreground, const Origin& origin = Origin::Centre);
	// Gets the next available Sprite
	Sprite* Get();
	// Removes specified sprite from pool
	void Free(Sprite* const sprite);
	// Clear all sprites in pool
	void Clear();
	// Clear index for getting next sprite, i.e. after calling ClearIndex(), the next Get() called will return sprites[0]
	void ClearIndex();
private:
	const std::string& imagePath;
	const Layer& layer;
	const Origin& origin;
	std::deque<Sprite*> sprites;
	int index = 0;
};