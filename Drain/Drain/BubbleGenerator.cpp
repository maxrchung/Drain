#include "BubbleGenerator.hpp"

BubbleGenerator::BubbleGenerator() {
	// TODO: fix side movement lmao also add easing to it lmao
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
	float xSideDelta = 55;

	float sideMoveTotalTime = (endMove - startMove) / sideMoveTimes;
	float oneDirTime = sideMoveTotalTime / 2; // Time for bubble to move in one direction, either left or right
	float oneDirMoveTimes = sideMoveTimes * 2;

	float startSideMove = startMove + 1;
	float endSideMove = startSideMove + oneDirTime;

	int leftOrRight = RandomRange::calculate(0, 1); // 0 (-1 later) = left 1 = right
	if (leftOrRight == 0) { // didnt know how to randomize btwn -1 or 1 so ye
		leftOrRight = -1;
	}

	if (leftOrRight == -1) { // So bubbles won't always start moving to the same side
		sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x - xSideDelta);
	}
	else if (leftOrRight == 1) {
		sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + xSideDelta);
	}

	startSideMove += oneDirTime;
	endSideMove += oneDirTime;

	for (int i = 0; i < oneDirMoveTimes - 1; i++) { // note to self add dependence on left or right and also switch direcitons every 2 iterations to fix bug adsljadasdfsdf
		if ((i % 2) == 0) {
			leftOrRight *= -1;
		}
		sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + (xSideDelta * leftOrRight));
		startSideMove += oneDirTime;
		endSideMove += oneDirTime;
	}
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