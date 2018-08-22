#include "BubbleGenerator.hpp"

BubbleGenerator::BubbleGenerator() {
	// TODO: add cool wiggly bubble move effect lmao
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
		std::vector<float> moveTimes = GetBubbleTiming();
		Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(startPos.x, startPos.y));
		MoveBubble(sprite, moveTimes);
	}
}

// Returns position of where bubble should be spawned
Vector2 BubbleGenerator::GetBubbleStartPos() {
	Vector2 startPos;
	startPos.x = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2); // Random x-coordinate in osu! screen
	startPos.y = screenBottom;

	return startPos;
}

// Randomizes and returns bubble startTime and endTime
std::vector<float> BubbleGenerator::GetBubbleTiming() {
	float adjustedTotalTime = moveTotalTime; // Note to self: This value will be randomized later on
	float timeVariance = adjustedTotalTime * 8; // Constant here is copied over from RainGenerator, adjust if necessary
	float moveTimeDelta = RandomRange::calculate(-timeVariance, timeVariance);
	float adjustedStartTime = moveStartTime + moveTimeDelta;
	float adjustedEndTime = adjustedStartTime + adjustedTotalTime;

	return {adjustedStartTime, adjustedEndTime };
}

// Handles all bubble movement from bottom of screen to top
void BubbleGenerator::MoveBubble(Sprite* sprite, std::vector<float> moveTimes) {
	float startMove = moveTimes[0];
	float endMove = moveTimes[1];
	sprite->Move(startMove, endMove, sprite->position, Vector2(sprite->position.x, screenTop));
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