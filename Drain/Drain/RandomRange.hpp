#pragma once
// Helper class for calculating a random offset
// You can call this as an instance of an object or as static, prefer the former if you are going to reuse it elsewhere
// auto r = RandomRange(20, 40); r.calculate(); RandomOffset::calculate(20, 40); will return numbers between 20 and 40
// Optionally specify a multipler or divisor: RandomRange(20, 40, 10).calculate() and RandomOffset::calculate(20, 40, 10) will return numbers between 2 and 4
class RandomRange {
public:
	explicit RandomRange(const int start, const int end, const float divisor = 1.0f);
	static float calculate(const int start, int end, const float divisor = 1.0f);
	float calculate() const;
	int start;
	int end;
	float divisor;
};