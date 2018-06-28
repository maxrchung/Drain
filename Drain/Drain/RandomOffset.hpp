#pragma once
// Helper class for calculating a random offset
// You can call this as an instance of an object or as static, prefer the former if you are going to reuse the instance
// RandomOffset(30, 10).calculate() and RandomOffset::calculate(30,10) will return numbers between 20 and 40
class RandomOffset {
public:
	RandomOffset(const int middle, const int variance);
	static int calculate(const int middle, int variance);
	int calculate();
	int middle;
	int variance;
};