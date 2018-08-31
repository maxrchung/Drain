#include "BubbleGenerator.hpp"

BubbleGenerator::BubbleGenerator() {
	// TODO: fix side movement lmao also add easing to it lmao
	// mouth bubbles
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
		ScaleBubbleSize(sprite, moveTimes);

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
	float adjustedTotalTime = RandomBubbleSpeed(); // Note to self: This value will be randomized later on
	float timeVariance = adjustedTotalTime * 8; // Constant here is copied over from RainGenerator, adjust if necessary
	float adjustedStartTime = 0;
	float adjustedEndTime = 0;

	do { // Ensures drops don't fall outside of time section & freezeTime
		float moveTimeDelta = timeVariance * RandomRange::calculate(-10000, 10000, 10000);
		adjustedStartTime = moveStartTime + moveTimeDelta;
		adjustedEndTime = adjustedStartTime + adjustedTotalTime;
	} while (adjustedStartTime < startTime.ms || adjustedEndTime > splatterTime.ms);

	return {adjustedStartTime, adjustedEndTime};
}

// Handles all bubble movement from bottom of screen to top including side movement
void BubbleGenerator::MoveBubble(Sprite* sprite, std::vector<float> moveTimes) {
	float startMove = moveTimes[0];
	float endMove = moveTimes[1];
	sprite->Move(startMove, endMove, sprite->position, Vector2(sprite->position.x, screenTop)); // Handles only vertical movement

	float sideMoveLength = Vector2::ScreenSize.y / sideMoveTimes;
	float oneDirMoveLength = sideMoveLength / 2;
	float xSideDelta = 30;

	float sideMoveTotalTime = (endMove - startMove) / sideMoveTimes;
	float oneDirTime = sideMoveTotalTime / 2; // Time for bubble to move in one direction, either left or right
	float oneDirMoveTimes = sideMoveTimes * 2;

	float startSideMove = startMove + 1; // +1 to avoid conflict with sprite->Move
	float endSideMove = startSideMove + oneDirTime;

	int leftOrRight = RandomRange::calculate(0, 1); // 0 = left 1 = right
	if (leftOrRight == 0) { // didnt know how to randomize btwn -1 and 1 so ye
		leftOrRight = -1;
	}

	if (leftOrRight == -1) { // So bubbles won't always start moving to the same side
		sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x - xSideDelta, Easing::SineOut);
	}
	else if (leftOrRight == 1) {
		sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + xSideDelta, Easing::SineOut);
	}

	startSideMove += oneDirTime;
	endSideMove += oneDirTime;

	for (int i = 0; i < oneDirMoveTimes - 1; i++) {
		if ((i % 2) == 0) { // Change direction every other iteration
			leftOrRight *= -1;
		}

		if ((i % 2) == 0) { // Bubble moving inwards
			sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + (xSideDelta * leftOrRight), Easing::SineIn);
		}
		else if ((i % 2) == 1) { // Bubble moving outwards
			sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + (xSideDelta * leftOrRight), Easing::SineOut);
		}

		startSideMove += oneDirTime;
		endSideMove += oneDirTime;
	}
}

// Returns the actual total time(ms) it takes for a bubble to float to the top of the screen; Smaller bubble sizes (slower speed) are made more probable for visual effect
float BubbleGenerator::RandomBubbleSpeed() {
	float adjustedTotalTime;
	static const float sections = 5; // How many different "sections" of velocity are to be sorted by probability
	static const float veloDelta = 10;
	float sectionLength = moveTotalTime / sections;
	float randNum = RandomRange::calculate(0, 1000, 100);

	if (randNum >= 0 && randNum <= 6.5) { // Gets speed of bubbles based on number randNum which ranges from 1-10
		adjustedTotalTime = RandomRange::calculate(sectionLength * 4, moveTotalTime);
	}
	else if (randNum > 6.5 && randNum <= 8.1) {
		adjustedTotalTime = RandomRange::calculate(sectionLength * 3, sectionLength * 4);
	}
	else if (randNum > 8.1 && randNum <= 9.4) {
		adjustedTotalTime = RandomRange::calculate(sectionLength * 2, sectionLength * 3);
	}
	else if (randNum > 9.4 && randNum <= 9.95) {
		adjustedTotalTime = RandomRange::calculate(sectionLength, sectionLength * 2);
	}
	else if (randNum > 9.95 && randNum <= 10) {
		adjustedTotalTime = RandomRange::calculate(minMoveTime, sectionLength);
	}

	return adjustedTotalTime;
}

// Scales bubbles to appropriate size based on speed
void BubbleGenerator::ScaleBubbleSize(Sprite* sprite, std::vector<float> moveTimes) {
	float adjustedSize;

	float adjustedTotalTime = moveTimes[1] - moveTimes[0];
	float veloRatio = adjustedTotalTime / moveTotalTime;
	float bubbleScale = maxSize - veloRatio;

	if (bubbleScale < 0) { // Ensures adjustedSize isn't a negative number; negative sizes would be fked
		float remainder = -bubbleScale;
		float minSizeScaler = maxSize - remainder;
		adjustedSize = minSize * minSizeScaler;
	}
	else {
		adjustedSize = bubbleScale * bubbleScale; // Multiplies scale by itself so image scales off total area instead of side length

		if (adjustedSize < minSize) { // So that bubbles that are too small don't exist
			adjustedSize = minSize;
		}
	}

	sprite->Scale(moveTimes[0], moveTimes[0], adjustedSize, adjustedSize);
}

// Adjust bubble velocity and density according to acceleration constant after each iteration of DrawBubble
void BubbleGenerator::VelocityController() {
	if (moveTotalTime >= minMoveTime) { // Ensures bubble doesn't move faster than minDropTime
		moveTotalTime *= (2.0f - acceleration);
	}

	bubbleCount *= acceleration;

	// Increments time after "row" of bubbles finish moving
	moveStartTime += moveTotalTime;
	moveEndTime += moveTotalTime;
}