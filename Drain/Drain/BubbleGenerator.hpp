#pragma once
#include <vector>
#include "Bubble.hpp"
#include "Easing.hpp"
#include "Path.hpp"
#include "RandomRange.hpp"
#include "SpriteCollection.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Time.hpp"
#include "Timing.hpp"

class BubbleGenerator {
public:
	BubbleGenerator(bool isSecondSection = false, bool isMouth = false, Vector2 mouthBubblePos = { 0, 0 }, Time mouthBubbleStartTime = Time("00:00:000"), bool willSplatter = true);
	std::vector<Bubble*> GetSplatBubbles();

	std::vector<Bubble*> allSprites;

private:
	void SwitchToMouthBubble();
	void SwitchToSecondSection();
	void BubbleController();
	void DrawBubble();
	void MoveBubble(Bubble* sprites, std::vector<float> moveTimes, Vector2 startPos, bool isSplat = false);
	void MoveBubble(Sprite* sprite, std::vector<float> moveTimes, bool isSplat = false);
	Vector2 GetBubbleStartPos();
	std::vector<float> GetBubbleTiming();
	bool TimeOverflowCheck(float timeVariance, float adjustedTotalTime);
	float GetRandomSideMovement();
	float RandomBubbleSpeed();
	void ScaleBubbleSize(Bubble* sprites, std::vector<float> moveTimes);
	void ScaleBubbleSize(Sprite* sprite, std::vector<float> moveTimes);
	void VelocityController();
	void SplatterPos(Bubble* sprites, std::vector<float> moveTimes);
	void TrackSplatBubbles(Bubble* sprites);
	void TrackAllBubbles(Bubble* sprites);
	void ColorBubbles(Sprite* sprite, float startTime, float endTime);
	Bubble* CreateBubbleSprites();
	Sprite* CreateBubbleSprites(Vector2 startPos);

	Time startTime = Time("01:58:790");
	Time endTime = Time("02:36:890");
	bool willSplatter;
	Time splatterTime = Time("02:33:885");
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

	std::vector<Bubble*> splattingBubbles;

	// Mouth timing and shit are placeholders, should be edited with the actual values later
	bool isMouth;
	Time mouthBubblePeriod = Time(Timing::whole * 16);
	Time mouthStartTime;
	Time mouthEndTime; // If this is before splatterTime Bubblegen will get stuck in an infinite loop. maybe fix l8r lol
	float mouthX;
	float mouthY;
	const float mouthBubbleMaxSize = 0.7;
	const float mouthBubbleMinSize = 0.2;
	float mouthBubbleCount = 5; // amount of bubbles that are initially spawned

	bool isSecondSection;
};