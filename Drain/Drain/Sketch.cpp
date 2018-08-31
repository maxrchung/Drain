#include "Sketch.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>
#include <numeric>


/*
This class reads from a text file, parses it, and creates a vector of
Bezier curves to sketch an image
*/

Sketch::Sketch(const std::string& pointMapPath, const Time& startTime, const Time& endTime,
			   const float resolution, const bool dynamic, const Path& brush,
			   const int margin, const int thickness, const Easing& easing, const bool drawIn, const bool drawOut, const bool fadeIn, const bool fadeOut)
	: pointMapPath{ pointMapPath + ".txt" }, startTime{ startTime }, endTime{ endTime },
	thickness{ thickness }, resolution{ resolution }, dynamic{ dynamic }, brush{ brush }, brushPath { getPath(brush) },
	margin{ margin }, easing{ easing }, drawIn{ drawIn }, drawOut{ drawOut }, fadeIn{ fadeIn }, fadeOut{ fadeOut }
{
	totalLines = 0;
	visDur = endTime.ms - startTime.ms;
	times = 1;
	relStart = 0;
	hiddenDur = 0;
}

bool Sketch::inBounds(const Vector2& point) {
	const auto half = Vector2::ScreenSize / 2;
	if (point.x > -half.x + 5 && point.x < half.x - 5 &&
		point.y > -half.y + 5 && point.y < half.y - 5) {
		return true;
	}
	return false;
}

void Sketch::draw(Bezier b) {
	if (dynamic) {
		if (!Sketch::dynamicResolution(b))
			return;
	}
	else {
		if (!Sketch::constResolution(b))
			return;
	}
	assert(points.size());

	auto mpoints = std::vector<Vector2>();
	// find midpoint of points and draw line between them
	for (int i = 0; i < points.size() - 1; i++) {
		totalLines++;
		mpoints.push_back((points[i] + points[i + 1]) / 2);
		if (!inBounds(points[i]) && !inBounds(points[i + 1])) {
			continue;
		}
		float dist = points[i].DistanceBetween(points[i + 1]);
		if (brush == Path::Taper) {
			dist *= 0.8;  // maybe want to scale with length of dist but this is fine for now
		}
		float angle = atan(-(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x + 0.001)); // negate y because osu!
		auto line = Storyboard::CreateSprite(brushPath, mpoints[i]);    // the actual line being drawn
		sprites.push_back(line);    // add it to the global sprites list
		if (std::abs(angle) > 0.01)    // only include a rotation command if the angle is significant
			line->Rotate(startTime.ms, startTime.ms, angle, angle);
		Swatch::colorFgToFgSprites({ line }, startTime.ms, endTime.ms);
		if (times == 1) {   // not looping
			if (drawIn && drawOut) {
				line->ScaleVector(startTime.ms, startTime.ms + visDur / 2, Vector2(0, thickness), Vector2(dist, thickness), easing);
				line->ScaleVector(startTime.ms + visDur / 2, endTime.ms, Vector2(dist, thickness), Vector2(0, thickness), mirrorEasing(easing));
			}
			else if (drawIn)
				line->ScaleVector(startTime.ms, endTime.ms, Vector2(0, thickness), Vector2(dist, thickness), easing);
			else if (drawOut)
				line->ScaleVector(startTime.ms, endTime.ms, Vector2(dist, thickness), Vector2(0, thickness), easing);
			else
				line->ScaleVector(startTime.ms, endTime.ms, Vector2(dist, thickness), Vector2(dist, thickness), easing);  // this will dictate endTime
			if (fadeIn && fadeOut) {
				line->Fade(startTime.ms, startTime.ms + visDur / 2, 0, 1, easing);
				line->Fade(startTime.ms + visDur / 2, endTime.ms, 1, 0, mirrorEasing(easing));
			}
			else if (fadeIn)
				line->Fade(startTime.ms, endTime.ms, 0, 1, easing);
			else if (fadeOut)
				line->Fade(startTime.ms, endTime.ms, 1, 0, easing);  // this will dictate endTime
			else;
			continue;
		}
		else {
			line->ScaleVector(startTime.ms, startTime.ms, Vector2(dist, thickness), Vector2(dist, thickness));  // Loop will dictate endTime
		}
		Sprite tmpSprite = Sprite();

		auto commands = std::vector<std::string>();
		commands.push_back(tmpSprite.Fade(0, visDur, 1, 1));  // stay visible NOTE: THIS LINE IS REQUIRED FOR LOOP TO WORK
		commands.push_back(tmpSprite.Fade(visDur, visDur, 1, 0));  // disappear instantaneously
		commands.push_back(tmpSprite.Fade(visDur + hiddenDur, visDur + hiddenDur, 0, 1));  // reappear instantaneously
		line->Loop(startTime.ms, times, commands);
	}
	points.clear();
}

int Sketch::constResolution(Bezier b) {
	// original linear resolution, returns numPoints
	int numPoints = b.length / resolution;	// truncate
	if (numPoints < 2) // nothing to be drawn
		return 0;
	for (int i = 0; i < numPoints; i++) {
		auto step = static_cast<float>(i) / (numPoints - 1);
		if (!std::isfinite(step)) {
			step = 0.999;
		}
		points.push_back(b.findPosition(step));
	}
	return numPoints;
}

s createS(double pos, double secondDeriv) {
	auto ans = s();
	ans.pos = pos;
	ans.secondDeriv = secondDeriv;
	return ans;
}

int Sketch::dynamicResolution(Bezier b) {
	int numPoints = b.length / resolution; // precheck if bezier is "short"
	if (numPoints < 2) // nothing to be drawn
		return 0;
	// find average 2nd derivative along bezier to determine "resolution"
	auto derivs = std::vector<double>();
	for (double i = 0.001; i < 1; i += 1 / static_cast<float>(numPoints)) {
		auto tmp = b.find2ndDerivative(i);
		derivs.push_back(std::abs(tmp.x) + std::abs(tmp.y));
	}
	auto resolution = std::accumulate(derivs.begin(), derivs.end(), 0) / numPoints; // average of 2nd derivs
	resolution /= this->resolution; // scale the generated resolution with resolution arg
	auto ans = 1;
	auto steps = std::vector<s>();
	steps.push_back(createS(0.001, derivs[0]));
	for (double i = 0.001;;) {
		auto tmp = b.find2ndDerivative(i);
		auto dist = resolution / (std::abs(tmp.x) + std::abs(tmp.y) + 1);
		// if points are too close together, don't add it
		if (dist < 0.001) {
			i += dist;
			break;
		}
		i += dist;
		if (i > 1.0 - 0.001)
			break;
		steps.push_back(createS(i, std::abs(tmp.x) + std::abs(tmp.y)));
	}
	steps.push_back(createS(0.999, derivs[derivs.size() - 1]));
	if (numPoints < steps.size()) { // if constRes results in fewer points, use constRes
		return constResolution(b);
	}
	for (auto& step : steps) {
		points.push_back(b.findPosition(step.pos));
		ans++;
	}
	return ans + 1;
}

int Sketch::make() {
	// returns 0 upon success
	std::size_t pos = pointMapPath.find(".txt");
	if (pos == std::string::npos)
		return 1;  // error if path doesn't contain .txt
	auto noTxt = pointMapPath.substr(0, pos);
	float xshift = 0;
	float yshift = 0;
	float xscale = 1;
	float yscale = 1;
	getTransform(&xshift, &yshift, &xscale, &yscale);
	std::ifstream ifs;
	//std::ofstream ofs;
	ifs.open(pointMapPath);
	//ofs.open(noTxt + std::string(".parsed"));
	float values[12];
	char absorb;
	std::string line1;
	std::string line2;
	assert(std::getline(ifs, line1));
	assert(line1 != ";");
	int numBeziers = 0;
	// original
	while (std::getline(ifs, line2)) {
		if (line2 == ";") {
			if (!std::getline(ifs, line1))
				break;
			continue;
		}
		std::istringstream iss(line1);
		iss >> values[0] >> absorb >> values[1] >> values[2] >> absorb >> values[3] >> values[4] >> absorb >> values[5];
		std::istringstream iss2(line2);
		iss2 >> values[6] >> absorb >> values[7] >> values[8] >> absorb >> values[9] >> values[10] >> absorb >> values[11];
		auto bez = Bezier({ Vector2((values[2] - xshift) * xscale, (-values[3] + yshift) * yscale),
							Vector2((values[4] - xshift) * xscale, (-values[5] + yshift) * yscale),
							Vector2((values[6] - xshift) * xscale, (-values[7] + yshift) * yscale),
							Vector2((values[8] - xshift) * xscale, (-values[9] + yshift) * yscale) });
		draw(bez);
		numBeziers++;
		line1 = line2;
	}
	std::cout << totalLines << std::endl;
	return 0;
}

void Sketch::getTransform(float *xshift, float *yshift, float *xscale, float *yscale) {
	// This function outputs parameters so that the entire image is centered and scaled to fit
	std::ifstream ifs;
	ifs.open(pointMapPath);
	auto xvalues = std::vector<float>();
	auto yvalues = std::vector<float>();
	std::string line;
	char absorb;
	while (std::getline(ifs, line)) {
		if (line == ";") {
			count++;
			continue;
		}
		std::istringstream iss(line);
		float tempx;
		float tempy;
		while (iss >> tempx >> absorb >> tempy) {
			xvalues.push_back(tempx);
			yvalues.push_back(tempy);
		}
	}
	auto minx = *std::min_element(xvalues.begin(), xvalues.end());
	auto maxx = *std::max_element(xvalues.begin(), xvalues.end());
	*xshift = Vector2::ScreenSize.x / 2.0f;    // average of all X coordinates
	auto miny = *std::min_element(yvalues.begin(), yvalues.end());
	auto maxy = *std::max_element(yvalues.begin(), yvalues.end());
	*yshift = Vector2::ScreenSize.y / 2.0f;    // average of all Y coordinates
	//*xscale = (852 - margin * 2) / (abs(minx) + abs(maxx));
	//*yscale = (480 - margin * 2) / (abs(miny) + abs(maxy));
	*xscale = 1;
	*yscale = 1;
}

void Sketch::loop(int times, std::vector<Sketch> v) {
	auto durSoFar = 0;  // sum of duration of each iteration of the loop
	auto totalDur = 0;  // total duration of the loop
	// durSoFar will == totalDur at the end of this function
	for (auto& frame : v) {
		totalDur += frame.visDur;
	}
	for (auto& frame : v) {
		frame.times = times;
		frame.relStart = durSoFar;
		frame.hiddenDur = totalDur - frame.visDur;
		frame.make();
		durSoFar += frame.visDur;
	}
}

void Sketch::make(const std::string& pointMapPath, const Time& startTime, const Time& endTime,
				  const float resolution, const bool dynamic, const Path& brush,
				  const int margin, const int thickness, const Easing& easing, const bool drawIn, const bool drawOut, const bool fadeIn, const bool fadeOut) {
	Sketch(pointMapPath, startTime, endTime, resolution, dynamic, brush, margin, thickness, easing, drawIn, drawOut, fadeIn, fadeOut).make();
}

void Sketch::render() {
	std::cout << "Rendering Sketch..." << std::endl;
	// art idea: have the image gradually lower in resolution and fade away
	//Sketch("1.txt", Time("00:00:900"), Time("00:04:200"), 1, 4.5, true, Path::Taper, margin, Easing::ExpoOut, true, true, true, true).make();
	//auto v = std::vector<Sketch>();
	//v.push_back(Sketch("1.txt", Time("00:05:000"), Time("00:05:300"), 1, 4, true, Path::Taper));      // 651
	//v.push_back(Sketch("1.txt", Time("00:05:300"), Time("00:05:600"), 1, 4.7, false, Path::Taper));   // 562
	//v.push_back(Sketch("1.txt", Time("00:05:600"), Time("00:05:900"), 1, 4.5, true, Path::Taper));    // 541
	//v.push_back(Sketch("1.txt", Time("00:05:900"), Time("00:06:200"), 1, 4.5, false, Path::Taper));   // 629
	//loop(3, v);     // loop duration is 1200ms

	make("010 su", Time("00:05:584"), Time("00:05:867"), 5, true, Path::Taper, 0, 1, Easing::EasingOut, false, false, true, false);
	make("015 ffo", Time("00:05:867"), Time("00:06:150"));
	make("020 ca", Time("00:06:150"), Time("00:06:433"));
	make("025 ting", Time("00:06:433"), Time("00:06:999"));
	make("025 ting", Time("00:06:999"), Time("00:07:565"), 1, 5.5);
	make("025 ting", Time("00:07:565"), Time("00:08:131"));
	//auto ting = std::vector<Sketch>();
	//ting.push_back(Sketch("025 ting.txt", Time("00:06:433"), Time("00:06:999"), 1, 5, true));
	//ting.push_back(Sketch("025 ting.txt", Time("00:06:999"), Time("00:07:565"), 1, 6, true));
	//loop(2, ting);
	make("035 puff", Time("00:08:131"), Time("00:08:414"));
	make("040 of", Time("00:08:414"), Time("00:08:697"));
	auto smoke = std::vector<Sketch>();
	smoke.push_back(Sketch("045 smoke", Time("00:08:697"), Time("00:09:546")));
	smoke.push_back(Sketch("045 smoke", Time("00:09:546"), Time("00:10:112"), 5.5));
	loop(4, smoke);
	make("055 i", Time("00:14:357"), Time("00:14:640"));
	make("060 took", Time("00:14:640"), Time("00:14:923"));
	make("065 your", Time("00:14:923"), Time("00:15:206"));
	make("070 breath", Time("00:15:206"), Time("00:15:489"));
	make("075 in", Time("00:15:489"), Time("00:17:187"));
	make("080 and", Time("00:17:187"), Time("00:17:470"));
	make("085 you", Time("00:17:470"), Time("00:17:753"));
	make("090 spoke", Time("00:17:753"), Time("00:21:963"));
	make("100 and", Time("00:21:963"), Time("00:22:282"));
	make("105 i", Time("00:22:282"), Time("00:22:565"));
	make("110 saw", Time("00:22:565"), Time("00:23:131"));
	make("115 the", Time("00:23:131"), Time("00:23:697"));
	make("120 world", Time("00:23:697"), Time("00:26:527"));
	make("125 turn", Time("00:26:527"), Time("00:27:093"));
	make("130 white", Time("00:27:093"), Time("00:36:574"));
	make("135 are", Time("00:36:574"), Time("00:36:716"));
	make("140 you", Time("00:36:716"), Time("00:37:140"));
	make("145 still", Time("00:37:140"), Time("00:37:423"));
	make("150 cal", Time("00:37:423"), Time("00:37:848"));
	make("155 ling", Time("00:37:848"), Time("00:38:131"));
	make("160 me", Time("00:38:131"), Time("00:40:395"));
	make("170 i", Time("00:40:395"), Time("00:40:749"));
	make("175 melt", Time("00:40:749"), Time("00:49:452"));
	make("180 in", Time("00:49:452"), Time("00:49:735"));
	make("185 to", Time("00:49:735"), Time("00:51:716"));
	make("190 your", Time("00:51:716"), Time("00:51:999"));
	make("195 voice", Time("00:51:999"), Time("00:52:565"), 5, true, Path::Taper, 0, 1, Easing::EasingIn, false, false, false, true);
}