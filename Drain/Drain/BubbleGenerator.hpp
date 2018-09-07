#pragma once
#include <vector>
#include "Easing.hpp"
#include "Path.hpp"
#include "RandomRange.hpp"
#include "Storyboard.hpp"
#include "Time.hpp"
#include "Timing.hpp"

class BubbleGenerator {
public:
	BubbleGenerator(bool isMouth = false, Vector2 mouthBubblePos = { 0, 0 }, Time mouthBubbleStartTime = Time("00:00:000"), bool willSplatter = true);
	std::vector<Sprite*> GetSplatBubbles();

	std::vector<Sprite *> sprites;

private:
	void SwitchToMouthBubble();
	void BubbleController();
	void DrawBubble();
	void MoveBubble(Sprite* sprite, std::vector<float> moveTimes, bool isSplat = false);
	Vector2 GetBubbleStartPos();
	std::vector<float> GetBubbleTiming();
	float GetRandomSideMovement();
	float RandomBubbleSpeed();
	void ScaleBubbleSize(Sprite* sprite, std::vector<float> moveTimes);
	void VelocityController();
	void SplatterPos(Sprite* sprite, std::vector<float> moveTimes);
	void TrackSplatBubbles(Sprite* sprite);
	void TrackAllBubbles(Sprite* sprite);

	Time startTime = Time("01:58:790");
	Time endTime = Time("02:33:890");
	const Time constEndTime = Time("02:33:890");
	bool willSplatter;
	Time splatterTime = Time("02:25:890"); // Not the correct time edit later <---------
	float acceleration = 1.07;
	float bubbleCount = 9;
	float minMoveTime = 750.0f; // Edit to cap max bubble velocity
	float screenBottom = -Vector2::ScreenSize.y / 2; 
	float screenTop = Vector2::ScreenSize.y / 2;
	float endY;
	float splatEndY;

	float totalTime = static_cast<float>(endTime.ms - startTime.ms);
	float moveTotalTime = totalTime / bubbleCount;
	float moveStartTime = startTime.ms;
	float moveEndTime = startTime.ms + moveTotalTime;
	int sideMoveTimes = 2; // Amount of times a bubble moves to the sides

	float maxSize = 1.0f;
	float minSize = 0.2f;
	const float rainLength = 102; // because a.png is 102x102

	std::vector<Sprite*> splattingBubbles;

	/* Mouth timing and shit are placeholders, should be edited with the actual values later*/
	bool isMouth;
	Time mouthBubblePeriod = Time(Timing::whole * 16);
	Time mouthStartTime;
	Time mouthEndTime; // If this is before splatterTime Bubblegen will get stuck in an infinite loop. maybe fix l8r lol
	float mouthX;
	float mouthY;
	const float mouthBubbleMaxSize = 0.7;
	const float mouthBubbleMinSize = 0.2;
	float mouthBubbleCount = 5;
};