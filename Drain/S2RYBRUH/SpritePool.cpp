#include "SpritePool.hpp"
#include "Storyboard.hpp"
#include <iostream>

SpritePool::SpritePool(const std::string& imagePath, const Layer& layer, const Origin& origin)
	: imagePath{ imagePath }, layer{ layer }, origin{ origin } {

}

Sprite* SpritePool::Get() {
	return Get(index++);
}

Sprite* SpritePool::Get(const int index) {
	while (index >= sprites.size()) {
		auto const sprite = Storyboard::CreateSprite(imagePath, Vector2::Zero, layer, origin);
		sprites.push_back(sprite);
	}

	return sprites[index];
}

void SpritePool::ClearIndex() {
	index = 0;
}