#include "BubbleGenerator.hpp"

BubbleGenerator::BubbleGenerator() {
	while (moveEndTime < endTime.ms) {
		BubbleController();
	}
}

void BubbleGenerator::BubbleController() {
	DrawBubble();
	VelocityController();
}

// Spawns bubble onto screen which will be moved to create visual effect 
void BubbleGenerator::DrawBubble() {
	for (int i = 0; i < bubbleCount; ++i) {
		Vector2 startPos = GetBubbleStartPos();
		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(startPos.x, startPos.y));
		MoveBubble(sprite);
	}
}

// Returns position of where bubble should be spawned
Vector2 BubbleGenerator::GetBubbleStartPos() {
	Vector2 startPos;
	startPos.x = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2); // Random x-coordinate in osu! screen
	startPos.y = screenBottom;

	return startPos;
}

// Move bubble from spawn point (bottom) to end point (top)
void BubbleGenerator::MoveBubble(Sprite* sprite) {
	sprite->Move(moveStartTime, moveEndTime, sprite->position, Vector2(sprite->position.x, screenTop));
}

// Adjust bubble velocity and density according to acceleration constant after each iteration of DrawBubble
void BubbleGenerator::VelocityController() {
	if (moveTotalTime >= minMoveTime) { // Ensures bubble doesn't move faster than minDropTime
		moveTotalTime *= (2.0f - acceleration);
	}

	// Increments time after "row" of bubbles finish moving
	moveStartTime += moveTotalTime;
	moveEndTime += moveTotalTime;
}