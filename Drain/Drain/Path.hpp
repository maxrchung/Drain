#pragma once
#include <string>
enum class Path {
	Circle,
	Pixel,
	Square
};
std::string getPath(Path path);