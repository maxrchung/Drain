#include "Path.hpp"
std::string getPath(Path path) {
	switch (path) {
		case Path::Circle:
			return "c";
		case Path::Pixel:
			return "p";
		case Path::Square:
			return "s";
	}
}