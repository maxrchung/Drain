#include <fstream>
#include <string>
#include <vector>

// https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

char variableName = 33;
std::pair<std::string, std::string> addVariable(const std::string& variable) {
	return std::make_pair(std::string("$") + variableName++, variable);
}

int main() {
	// swag
	auto inputPathFile = std::ifstream("../Drain/StoryboardInputPath.txt");
	std::string inputPath;
	std::getline(inputPathFile, inputPath);
	// http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
	auto storyboardFile = std::ifstream(inputPath, std::ios::in | std::ios::binary);
	std::string storyboard;
	storyboardFile.seekg(0, std::ios::end);
	storyboard.resize(storyboardFile.tellg());
	storyboardFile.seekg(0, std::ios::beg);
	storyboardFile.read(&storyboard[0], storyboard.size());

	char variableName = 33;
	const auto variables = std::vector<std::pair<std::string, std::string>>({
		addVariable("Sprite,Background,Centre,\""),
		addVariable("Sprite,Background,BottomLeft,\""),
		addVariable("Sprite,Background,TopLeft,\""),
		addVariable("Sprite,Background,CentreLeft,\""),
		addVariable("Sprite,Background,BottomRight,\""),
		addVariable("Sprite,Foreground,Centre,\""),
		addVariable("\",320,240"),
		addVariable("27,27,27"),
		addVariable("114,187,180"),
		addVariable("218,236,236"),
		addVariable("170,0,0"),
		addVariable(" V,0,"),
		addVariable(" C,0,"),
		addVariable(" S,0,"),
		addVariable(" R,0,"),
		addVariable(" M,0,"),
		addVariable(" MX,15,"),
		addVariable(" MX,16,"),
		addVariable(" MY,15,"),
		addVariable(" MY,16,"),
		addVariable(" V,16,"),
		addVariable(" V,15,"),
		addVariable(" F,0,"),
	});
	
	replaceAll(storyboard, "\r", "");
	for (const auto& variable : variables) {
		replaceAll(storyboard, variable.second, variable.first);
	}

	auto outFile = std::ofstream(inputPath + '2');
	outFile << "[Variables]\n";
	for (const auto& variable : variables) {
		outFile << variable.first << "=" << variable.second << "\n";
	}
	outFile << storyboard;
	return 0;
}