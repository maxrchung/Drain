#pragma once
#include "Vector2.hpp"
class Stroke {
public:
	explicit Stroke(const Vector2& start, const Vector2& end);
	virtual float calculateLength() const = 0;
protected:
	const Vector2 start;
	const Vector2 end;
};