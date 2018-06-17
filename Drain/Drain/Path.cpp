#include "Path.hpp"
#include <exception>
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
		case Path::EighthBottom:
			return "e";
		case Path::EighthTop:
			return "f";
		case Path::Blank:
			return "g";
		case Path::TwoThirds:
			return "h";
		default:
			throw new std::exception("Unsupported path");
	}
}