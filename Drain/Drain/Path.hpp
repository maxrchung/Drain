#pragma once
#include <string>
// Enumeration for the different sprite images you can use
enum class Path {
	Circle,
	Pixel,
	QuarterInner,
	Square,
	EighthBottomInner,
	EighthTopInner,
	Blank,
	QuarterOuter,
	EighthBottomOuter,
	EighthTopOuter
};
// Function for converting the Path enumeration to actual file name
// Example usage: std::string stringPath = getPath(Path::Circle);
std::string getPath(Path path);