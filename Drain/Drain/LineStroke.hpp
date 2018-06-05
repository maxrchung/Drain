#pragma once
#include "Stroke.hpp"
class LineStroke : public Stroke {
public:
	explicit LineStroke(const Vector2& startPoint, const Vector2& endPoint);
};