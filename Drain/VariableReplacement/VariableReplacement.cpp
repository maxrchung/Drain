#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

char variableName = 0;
std::pair<std::string, std::string> addVariable(const std::string& variable) {
	if (variableName == '=' ||
		variableName == '$' ||
		variableName == ',' ||
		variableName == '\r' ||
		variableName == '\n' ||
		(variableName - '0' >= 0 && variableName - '0' <= 9)) {
		variableName++;
	}
	return std::make_pair(std::string("$") + variableName++, variable);
}

int main() {
	const auto variables = std::vector<std::pair<std::string, std::string>>({
		// General
		addVariable(R"(Sprite,Foreground,Centre,"a",)"),
		addVariable(R"(Sprite,Foreground,Centre,"k",)"),
		addVariable(R"(Sprite,Foreground,TopCentre,"k",)"),
		addVariable(R"(Sprite,Background,BottomLeft,"d",)"),
		addVariable(R"(Sprite,Background,BottomLeft,"e",)"),
		addVariable(R"(Sprite,Background,BottomLeft,"f",)"),
		addVariable(R"(Sprite,Background,BottomLeft,"g",)"),
		addVariable(R"(Sprite,Background,BottomLeft,"h",)"),
		addVariable(R"(Sprite,Background,BottomLeft,"i",)"),
		addVariable(R"(Sprite,Background,BottomRight,"b",)"),
		addVariable(R"(Sprite,Background,Centre,"a",)"),
		addVariable(R"(Sprite,Background,Centre,"j",)"),
		addVariable(R"(Sprite,Background,CentreLeft,"c",)"),
		addVariable(R"(Sprite,Background,TopLeft,"b",)"),
		addVariable("0,0,0"),
		addVariable("27,27,27"),
		addVariable("70,101,110"),
		addVariable("156,184,192"),
		addVariable("170,0,0"),
		addVariable("255,255,255"),
		addVariable(" C,0,"),
		addVariable(" F,0,"),
		addVariable(" M,0,"),
		addVariable(" M,1,"),
		addVariable(" MX,1,"),
		addVariable(" MX,15,"),
		addVariable(" MX,16,"),
		addVariable(" MY,15,"),
		addVariable(" MY,16,"),
		addVariable(" R,0,"),
		addVariable(" S,0,"),
		addVariable(" S,1,"),
		addVariable(" V,0,"),
		addVariable(" V,1,"),
		addVariable(" V,15,"),
		addVariable(" V,16,"),

		// Sketch
		addVariable(R"("320,240)"),
		addVariable(" L,"),
		addVariable("  F,0,0,566,1"),
		addVariable("  F,0,566,,1,0"),
		addVariable("  F,0,1132,,0,1"),
																			});

	// swag
	auto inputPathFile = std::ifstream("../Drain/StoryboardInputPath.txt");
	std::string inputPath;
	std::getline(inputPathFile, inputPath);
	auto storyboardFile = std::ifstream(inputPath);

	// Replace line by line
	std::stringstream builder;
	std::string line;
	while (std::getline(storyboardFile, line)) {
		for (const auto& variable : variables) {
			replaceAll(line, variable.second, variable.first);
			// Remove carriage return
			replaceAll(line, "\r", "");
		}
		builder << line << "\n";
	}

	auto outFile = std::ofstream(inputPath + '2', std::ios::out | std::ios::binary);
	outFile << "[Variables]\n";
	for (const auto& variable : variables) {
		outFile << variable.first << "=" << variable.second << "\n";
	}
	outFile << builder.str();
	return 0;
}