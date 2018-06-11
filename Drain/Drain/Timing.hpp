#pragma once

class Timing {
public:
	static constexpr float bpm = 106.0f;
	// ~566 ms
	static constexpr float whole = 60.0f * 1000.0f / bpm;
	// ~283 ms
	static constexpr float half = whole / 2.0f;
	// ~142 ms
	static constexpr float quarter = half / 2.0f;
	// ~71 ms
	static constexpr float eighth = quarter / 2.0f;
	// ~35 ms
	static constexpr float sixteeth = eighth / 2.0f;
};