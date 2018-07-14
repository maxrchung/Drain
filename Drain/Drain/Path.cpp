#include "Path.hpp"
#include <exception>
// Be careful not to overlap file names
std::string getPath(Path path) {
	switch (path) {
		case Path::Circle:
			return "a";
		case Path::Pixel:
			return "b";
		case Path::Square:
			return "c";
		case Path::QuarterInner:
			return "d";
		case Path::EighthBottomInner:
			return "e";
		case Path::EighthTopInner:
			return "f";
		case Path::QuarterOuter:
			return "g";
		case Path::EighthBottomOuter:
			return "h";
		case Path::EighthTopOuter:
			return "i";
	}
}
