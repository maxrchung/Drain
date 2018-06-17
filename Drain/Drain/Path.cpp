#include "Path.hpp"
// Be careful not to overlap file names
std::string getPath(Path path) {
	switch (path) {
		case Path::Circle:
			return "a";
		case Path::Pixel:
			return "b";
		case Path::Quarter:
			return "c";
		case Path::Square:
			return "d";
		case Path::Eighth:
			return "e";
	}
}