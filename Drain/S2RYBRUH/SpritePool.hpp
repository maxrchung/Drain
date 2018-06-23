#pragma once

#include "Sprite.hpp"
#include <string>

// Used in StrokeAnimation for drawing lines/objects frame by frame
// Saves space so you don't have to keep remaking sprites
class SpritePool {
public:
	SpritePool(const std::string& imagePath, const Layer& layer = Layer::Foreground, const Origin& origin = Origin::Centre);
	// Gets the next available Sprite
	Sprite* Get();
	// Get specific index
	Sprite* Get(const int index);
	// Reset get index
	void ClearIndex();
	std::vector<Sprite*> sprites;
private:
	int index = 0;
	const std::string& imagePath;
	const Layer& layer;
	const Origin& origin;
};