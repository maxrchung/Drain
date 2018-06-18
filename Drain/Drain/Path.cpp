#include "Path.hpp"
#include <exception>
// Be careful not to overlap file names
std::string getPath(Path path) {
	switch (path) {
		case Path::Circle:
			return "a";
		case Path::Pixel:
			return "b";
		case Path::QuarterInner:
			return "c";
		case Path::Square:
			return "d";
		case Path::EighthBottomInner:
			return "e";
		case Path::EighthTopInner:
			return "f";
		case Path::Blank:
			return "g";
		case Path::QuarterOuter:
			return "h";
		case Path::EighthBottomOuter:
			return "i";
		case Path::EighthTopOuter:
			return "j";
		default:
			throw new std::exception("Unsupported path");
	}
}