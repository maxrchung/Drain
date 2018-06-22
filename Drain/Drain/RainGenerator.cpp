#include "RainGenerator.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"

RainGenerator::RainGenerator(int count) {
	int x = -Vector2::ScreenSize.x/2;
	for (int i = 0; i < count; i++) {
		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(x+i*50, Vector2::ScreenSize.y/2));
		sprite->Move(0, 10000, sprite->position, Vector2(sprite->position.x, -Vector2::ScreenSize.y / 2));
	}
}