#pragma once
// Helper class for calculating a random offset
// You can call this as an instance of an object or as static, prefer the former if you are going to reuse it elsewhere
// RandomRange(20, 40).calculate() and RandomOffset::calculate(20, 40) will return numbers between 20 and 40
class RandomRange {
public:
	RandomRange(const int start, const int end);
	static int calculate(const int start, int end);
	int calculate();
	int start;
	int end;
};