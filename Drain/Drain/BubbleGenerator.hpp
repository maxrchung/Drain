#pragma once
#include "Time.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"
#include "RandomRange.hpp"

class BubbleGenerator {
public:
	BubbleGenerator();
	void BubbleController();
	void DrawBubble();
	void MoveBubble(Sprite* sprite);
	Vector2 GetBubbleStartPos();
	void VelocityController();

private:
	Time startTime = Time("01:58:79");
	Time endTime = Time("02:33:89");
	Time splatterTime;
	float acceleration = 1.08;
	float bubbleCount = 20;
	float minMoveTime = 750.0f; // Edit to cap max bubble velocity
	float screenBottom = -Vector2::ScreenSize.y / 2; 
	float screenTop = Vector2::ScreenSize.y / 2;

	float totalTime = static_cast<float>(endTime.ms - startTime.ms);
	float moveTotalTime = totalTime / bubbleCount;
	float moveStartTime = startTime.ms;
	float moveEndTime = startTime.ms + moveTotalTime;
};