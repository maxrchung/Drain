#include "Storyboard.hpp"
#include <iostream>

int main() {
	// Put storyboard osb path inside of StoryboardInputPath.txt
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	storyboardInputPath >> path;

	Storyboard::Write(path);

	return 0;
}