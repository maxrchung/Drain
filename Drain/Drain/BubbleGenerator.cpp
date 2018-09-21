#include "BubbleGenerator.hpp"

BubbleGenerator::BubbleGenerator(bool isSecondSection, bool isMouth, Vector2 mouthBubblePos, Time mouthBubbleStartTime, bool willSplatter)
	: isSecondSection{ isSecondSection }, isMouth { isMouth }, willSplatter{ willSplatter }, mouthX{ mouthBubblePos.x }, mouthY{ mouthBubblePos.y }, mouthStartTime{ mouthBubbleStartTime } {
	// TODO: bbbles pop individually, one by one? one more bub gen seciotn
	// TODO: bubbles precise timing lol, 2nd section bubble, bubble slow before freeze
	// FIX: sprite sizes wt f

	if (isMouth) { 
		SwitchToMouthBubble();
	}

	if (isSecondSection) {
		SwitchToSecondSection();
	}

	while (moveEndTime < endTime.ms) {
		BubbleController();
	}

	//test
	//Bubble* meme = new Bubble();
	//Vector2 startPos = { 0,0 };
	//float endY = startPos.y + 200;
	//meme->MoveY(Time("00:01:000").ms, Time("00:03:600").ms, startPos.y, startPos.y + 200);
	////meme->MoveX(Time("00:01:200").ms, Time("00:03:800").ms, startPos.x, startPos.x + 200);
}

// Switches appropriate variables if instance of class is mouth bubble instead of default bubble
void BubbleGenerator::SwitchToMouthBubble() {
	maxSize = mouthBubbleMaxSize;
	minSize = mouthBubbleMinSize;
	startTime = mouthStartTime;
	endTime = mouthEndTime = mouthStartTime.ms + mouthBubblePeriod.ms;
	bubbleCount = mouthBubbleCount;
	totalTime = static_cast<float>(endTime.ms - startTime.ms);
	moveTotalTime = totalTime / bubbleCount;
	moveStartTime = startTime.ms;
	moveEndTime = startTime.ms + moveTotalTime;
	willSplatter = false; // Because mouth bubbles do not splatter
}

// second section of default bubble, only 2 exist currently but change l8r if more
void BubbleGenerator::SwitchToSecondSection() {
	startTime = Time("03:10:112").ms;
	endTime = Time("03:23:016").ms;
	splatterTime = Time("03:19:168").ms;
}

// Handles the overall creation of bubbles
void BubbleGenerator::BubbleController() {
	DrawBubble();
	VelocityController();
}

// Spawns bubble onto screen which will be moved to create visual effect 
void BubbleGenerator::DrawBubble() {
	for (int i = 0; i < bubbleCount; ++i) {
		Vector2 startPos = GetBubbleStartPos();
		std::vector<float> moveTimes = GetBubbleTiming();
		// Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(startPos.x, startPos.y));

		if (isMouth) {
			Sprite* sprites = CreateBubbleSprites(startPos);
			ScaleBubbleSize(sprites, moveTimes);
			ColorBubbles(sprites, moveTimes[0], moveTimes[1]);

			MoveBubble(sprites, moveTimes);
		}
		else {
			Bubble* sprites = CreateBubbleSprites();
			ScaleBubbleSize(sprites, moveTimes);
			TrackAllBubbles(sprites);

			if (willSplatter && (splatterTime.ms >= moveTimes[0] && splatterTime.ms <= moveTimes[1])) { // Checks whether bubble is visible during splatterTime
				SplatterPos(sprites, moveTimes);
				MoveBubble(sprites, moveTimes, startPos, true);
			}
			else {
				MoveBubble(sprites, moveTimes, startPos);
			}
		}
	}
}

// Create Bubble object which will contain the layered bubble sprites
Bubble* BubbleGenerator::CreateBubbleSprites() {
	return new Bubble();
}

// mouth bubble version, only single sprite
Sprite* BubbleGenerator::CreateBubbleSprites(Vector2 startPos) {
	Sprite* sprite = Storyboard::CreateSprite(getPath(Path::Circle), Vector2(startPos.x, startPos.y));
	return sprite;
}

// Returns position of where bubble should be spawned
Vector2 BubbleGenerator::GetBubbleStartPos() {
	Vector2 startPos;
	if (!isMouth) {
		startPos.x = RandomRange::calculate(-Vector2::ScreenSize.x / 2, Vector2::ScreenSize.x / 2); // Random x-coordinate in osu! screen
		startPos.y = screenBottom - ((rainLength / 2) * maxSize);
	}
	else {
		float xMouthVariance = 25;
		float yMouthVariance = 13;
		float xMouthDelta = RandomRange::calculate(-xMouthVariance, xMouthVariance);
		float yMouthDelta = RandomRange::calculate(-yMouthVariance, yMouthVariance);
		startPos.x = mouthX + xMouthDelta;
		startPos.y = mouthY + yMouthDelta;
	}

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
	} while (adjustedStartTime < startTime.ms || ((adjustedEndTime > (splatterTime.ms + adjustedTotalTime)) && willSplatter) || ((adjustedEndTime > endTime.ms) && !willSplatter));

	return {adjustedStartTime, adjustedEndTime};
}

// Handles all bubble movement from bottom of screen to top including side movement (default bubble ver.)
void BubbleGenerator::MoveBubble(Bubble* sprites, std::vector<float> moveTimes, Vector2 startPos, bool isSplat) {
	float endMove;
	if (!isSplat) {
		endY = screenTop + ((rainLength / 2) * maxSize);
		endMove = moveTimes[1];
	}
	else {
		endY = splatEndY;
		endMove = splatterTime.ms;
	}

	float startMove = moveTimes[0];

	sprites->MoveY(startMove, endMove, startPos.y, endY); // Handles only vertical movement

	float sideMoveLength = Vector2::ScreenSize.y / sideMoveTimes;
	float oneDirMoveLength = sideMoveLength / 2;
	float xSideDelta = GetRandomSideMovement();

	float sideMoveTotalTime = (endMove - startMove) / sideMoveTimes;
	float oneDirTime = sideMoveTotalTime / 2; // Time for bubble to move in one direction, either left or right
	float oneDirMoveTimes = sideMoveTimes * 2;

	float startSideMove = startMove + 1; // +1 to avoid conflict with sprite->Move
	float endSideMove = startSideMove + oneDirTime;

	int leftOrRight = RandomRange::calculate(0, 1) * 2 - 1; // randomly chooses either 1 or -1; -1 = left 1 = right

	if (leftOrRight == -1) { // So bubbles won't always start moving to the same side
		sprites->MoveX(startSideMove, endSideMove, startPos.x, startPos.x - xSideDelta, Easing::SineOut);
	}
	else if (leftOrRight == 1) {
		sprites->MoveX(startSideMove, endSideMove, startPos.x, startPos.x + xSideDelta, Easing::SineOut);
	}

	startSideMove += oneDirTime;
	endSideMove += oneDirTime;

	for (int i = 0; i < oneDirMoveTimes - 1; i++) {
		if ((i % 2) == 0) { // Bubble moving inwards
			leftOrRight *= -1; // Change direction every other iteration
			sprites->MoveX(startSideMove, endSideMove, sprites->sprites.position.x, sprites->sprites.position.x + (xSideDelta * leftOrRight), Easing::SineIn);
		}
		else if ((i % 2) == 1) { // Bubble moving outwards
			sprites->MoveX(startSideMove, endSideMove, sprites->sprites.position.x, sprites->sprites.position.x + (xSideDelta * leftOrRight), Easing::SineOut);
		}

		startSideMove += oneDirTime;
		endSideMove += oneDirTime;
	}
}

// Handles all bubble movement from bottom of screen to top including side movement (mouth bubble ver.)
void BubbleGenerator::MoveBubble(Sprite* sprite, std::vector<float> moveTimes, bool isSplat) {
	float endMove;
	if (!isSplat) {
		endY = screenTop + ((rainLength / 2) * maxSize);
		endMove = moveTimes[1];
	}
	else {
		endY = splatEndY;
		endMove = splatterTime.ms;
	}

	float startMove = moveTimes[0];

	sprite->MoveY(startMove, endMove, sprite->position.y, endY); // Handles only vertical movement

	float sideMoveLength = Vector2::ScreenSize.y / sideMoveTimes;
	float oneDirMoveLength = sideMoveLength / 2;
	float xSideDelta = GetRandomSideMovement();

	float sideMoveTotalTime = (endMove - startMove) / sideMoveTimes;
	float oneDirTime = sideMoveTotalTime / 2; // Time for bubble to move in one direction, either left or right
	float oneDirMoveTimes = sideMoveTimes * 2;

	float startSideMove = startMove + 1; // +1 to avoid conflict with sprite->Move
	float endSideMove = startSideMove + oneDirTime;

	int leftOrRight = RandomRange::calculate(0, 1) * 2 - 1; // randomly chooses either 1 or -1; -1 = left 1 = right

	if (leftOrRight == -1) { // So bubbles won't always start moving to the same side
		sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x - xSideDelta, Easing::SineOut);
	}
	else if (leftOrRight == 1) {
		sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + xSideDelta, Easing::SineOut);
	}

	startSideMove += oneDirTime;
	endSideMove += oneDirTime;

	for (int i = 0; i < oneDirMoveTimes - 1; i++) {
		if ((i % 2) == 0) { // Bubble moving inwards
			leftOrRight *= -1; // Change direction every other iteration
			sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + (xSideDelta * leftOrRight), Easing::SineIn);
		}
		else if ((i % 2) == 1) { // Bubble moving outwards
			sprite->MoveX(startSideMove, endSideMove, sprite->position.x, sprite->position.x + (xSideDelta * leftOrRight), Easing::SineOut);
		}

		startSideMove += oneDirTime;
		endSideMove += oneDirTime;
	}
}

// Returns a random value for the x variation in a bubble's movement
float BubbleGenerator::GetRandomSideMovement() {
	float xSideMaxDelta = 40;
	float xSideMinDelta = 5;
	float xSideRandomizer = xSideMaxDelta - xSideMinDelta;
	float xSideDeltaDelta = RandomRange::calculate(0, xSideRandomizer);
	float negOrPos;

	do {
		negOrPos = RandomRange::calculate(-1, 1);
	} while (negOrPos == 0);

	float xSideDelta = negOrPos * (xSideMinDelta + xSideDeltaDelta);

	return xSideDelta;
}

// Returns the actual total time(ms) it takes for a bubble to float to the top of the screen; Smaller bubble sizes (slower speed) are made more probable for visual effect
float BubbleGenerator::RandomBubbleSpeed() {
	float adjustedTotalTime;
	static const float sections = 5; // How many different "sections" of velocity are to be sorted by probability
	static const float veloDelta = 10;
	float sectionLength = moveTotalTime / sections;
	float randNum = RandomRange::calculate(0, 10000, 1000);

	if (randNum >= 0 && randNum <= 5) { // Gets speed of bubbles based on number randNum which ranges from 1-10
		adjustedTotalTime = RandomRange::calculate(sectionLength * 4, moveTotalTime);
	}
	else if (randNum > 5 && randNum <= 7) {
		adjustedTotalTime = RandomRange::calculate(sectionLength * 3, sectionLength * 4);
	}
	else if (randNum > 7 && randNum <= 8.7) {
		adjustedTotalTime = RandomRange::calculate(sectionLength * 2, sectionLength * 3);
	}
	else if (randNum > 8.7 && randNum <= 9.6) {
		adjustedTotalTime = RandomRange::calculate(sectionLength, sectionLength * 2);
	}
	else if (randNum > 9.6 && randNum <= 10) {
		adjustedTotalTime = RandomRange::calculate(minMoveTime, sectionLength);
	}

	return adjustedTotalTime;
}

// Scales bubbles to appropriate size based on speed (default bubble ver.)
void BubbleGenerator::ScaleBubbleSize(Bubble* sprites, std::vector<float> moveTimes) {
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

	//std::cout << sprites->sprites.size << "\n";
	sprites->Scale(moveTimes[0], moveTimes[0], adjustedSize, adjustedSize);
}

// Scales bubbles to appropriate size based on speed (mouth bubble ver.)
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

// Gets the appropriate x and y positions for a bubble that will splatter (default bubble ver.)
void BubbleGenerator::SplatterPos(Bubble* sprites, std::vector<float> moveTimes) {
	Vector2 splatterPos;
	float startX = sprites->sprites.position.x;
	float endX = startX;
	float startY = screenBottom - ((rainLength / 2) * maxSize);
	float endY = screenTop + ((rainLength / 2) * maxSize);

	float totalTime = moveTimes[1] - moveTimes[0];
	float untilSplat = splatterTime.ms - moveTimes[0];
	float ratio = untilSplat / totalTime;
	float xDiff = endX - startX; // x doesn't vary in vertical movement, should be 0
	float yDiff = endY - startY;

	float splatterDiffX = xDiff * ratio;
	float splatterDiffY = yDiff * ratio;

	splatterPos.x = startX + splatterDiffX; // Currently useless, keeping it in case I need it later
	splatterPos.y = startY + splatterDiffY;

	TrackSplatBubbles(sprites); // Save the sprite to a sprite vector, will be used by splat boi

	splatEndY = splatterPos.y;
}

void BubbleGenerator::ColorBubbles(Sprite* sprite, float startTime, float endTime) {
	Swatch::colorFgToFgSprites({ sprite }, startTime, endTime);
}

void BubbleGenerator::TrackSplatBubbles(Bubble* sprites) {
	splattingBubbles.push_back(sprites);
}

void BubbleGenerator::TrackAllBubbles(Bubble* sprites) {
	allSprites.push_back(sprites);
}

std::vector<Bubble*> BubbleGenerator::GetSplatBubbles() {
	return splattingBubbles;
}
