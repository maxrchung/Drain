#ifndef EASING_HPP
#define EASING_HPP

#include <string>

enum class Easing {
	Linear,
	EasingOut, // Same as QuadOut - cl8n
	EasingIn, // Same as QuadIn - cl8n
	QuadIn,
	QuadOut,
	QuadInOut,
	CubicIn,
	CubicOut,
	CubicInOut,
	QuartIn,
	QuartOut, // 10
	QuartInOut,
	QuintIn,
	QuintOut,
	QuintInOut,
	SineIn,
	SineOut,
	SineInOut,
	ExpoIn,
	ExpoOut,
	ExpoInOut, // 20
	CircIn,
	CircOut,
	CircInOut,
	ElasticIn,
	ElasticOut,
	ElasticHalfOut,
	ElasticQuarterOut,
	ElasticInOut,
	BackIn,
	BackOut, // 30
	BackInOut,
	BounceIn,
	BounceOut,
	BounceInOut,
	Count
};

static std::string* Easings() {
	static std::string easings[static_cast<int>(Easing::Count)]{
		"Linear",
		"EasingOut",
		"EasingIn",
		"QuadIn",
		"QuadOut",
		"QuadInOut",
		"CubicIn",
		"CubicOut",
		"CubicInOut",
		"QuartIn",
		"QuartOut", // 10
		"QuartInOut",
		"QuintIn",
		"QuintOut",
		"QuintInOut",
		"SineIn",
		"SineOut",
		"SineInOut",
		"ExpoIn",
		"ExpoOut",
		"ExpoInOut", // 20
		"CircIn",
		"CircOut",
		"CircInOut",
		"ElasticIn",
		"ElasticOut",
		"ElasticHalfOut",
		"ElasticQuarterOut",
		"ElasticInOut",
		"BackIn",
		"BackOut", // 30
		"BackInOut",
		"BounceIn",
		"BounceOut",
		"BounceInOut"
	};
	return easings;
}

static Easing mirrorEasing(Easing easingEnum) {
    int easing = static_cast<int>(easingEnum);
    switch (easing) {
    case 0:
    case 26:
    case 27:
    case 28:
    case 31:
        return static_cast<Easing>(easing);
    case 1:
        return static_cast<Easing>(2);
    case 2:
        return static_cast<Easing>(1);
    case 29:
        return static_cast<Easing>(30);
    case 30:
        return static_cast<Easing>(29);
    case 32:
        return static_cast<Easing>(33);
    case 33:
        return static_cast<Easing>(32);
    }
    // 3 to 4, 4 to 3, 5 to 5; 6 to 7, 7 to 6, 8 to 8
    switch ((easing - 3) % 3) {
    case 0:
        return static_cast<Easing>(easing + 1);
    case 1:
        return static_cast<Easing>(easing - 1);
    case 2:
        return static_cast<Easing>(easing);
    }
}

#endif//EASING_HPP