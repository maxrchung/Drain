#pragma once
#include "Vector2.hpp"
class Stroke {
public:
	explicit Stroke(const Vector2& startPoint, const Vector2& endPoint);
	virtual void getLength() = 0;
private:
	const Vector2 startPoint;
	const Vector2 endPoint;
};