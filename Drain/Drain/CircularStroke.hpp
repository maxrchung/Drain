#pragma once
#include "Stroke.hpp"
class CircularStroke : public Stroke {
public:
	explicit CircularStroke(const Vector2& startPoint, const Vector2& endPoint);
};