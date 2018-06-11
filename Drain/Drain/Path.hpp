#pragma once
#include <string>
enum class Path {
	Circle,
	Pixel,
	Quarter,
	Square
};
std::string getPath(Path path);