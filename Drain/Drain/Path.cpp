#include "Path.hpp"
// Be careful not to overlap file names
std::string getPath(Path path) {
	switch (path) {
		case Path::Circle:
			return "c";
		case Path::Pixel:
			return "p";
		case Path::Quarter:
			return "q";
		case Path::Square:
			return "s";
	}
}