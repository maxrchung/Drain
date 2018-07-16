#include "SpritePool.hpp"
#include "Storyboard.hpp"
#include <algorithm>
#include <iostream>

SpritePool::SpritePool(const std::string& imagePath, const Layer& layer, const Origin& origin)
	: imagePath{ imagePath }, layer{ layer }, origin{ origin } {

}

Sprite* SpritePool::Get() {
	if (index >= sprites.size()) {
		auto const sprite = Storyboard::CreateSprite(imagePath, Vector2::Zero, layer, origin);
		sprites.push_back(sprite);
	}
	return sprites[index++];
}

void SpritePool::Free(Sprite* const sprite) {
	const auto spriteIterator = std::find(sprites.begin(), sprites.end(), sprite);
	if (spriteIterator != sprites.end()) {
		sprites.erase(spriteIterator);
		--index;
	}
}

void SpritePool::Clear() {
	sprites.clear();
	ClearIndex();
}

void SpritePool::ClearIndex() {
	index = 0;
}