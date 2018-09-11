#include "Sketch.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Timing.hpp"

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
	thickness{ thickness }, resolution{ resolution }, dynamic{ dynamic }, brush{ brush }, brushPath{ getPath(brush) },
	margin{ margin }, easing{ easing }, drawIn{ drawIn }, drawOut{ drawOut }, fadeIn{ fadeIn }, fadeOut{ fadeOut } {
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

void Sketch::draw(Bezier& b) {
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
		if (times == 1) {   // not looping
			Swatch::colorFgToFgSprites({ line }, startTime.ms, endTime.ms);
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
			Swatch::colorFgToFgSprites({ line }, startTime.ms, loopEndTime);
			line->ScaleVector(startTime.ms, startTime.ms, Vector2(dist, thickness), Vector2(dist, thickness));  // Loop will dictate endTime
			Sprite temp = Sprite();
			auto commands = std::vector<std::string>();
			commands.push_back(temp.Fade(0, visDur, 1, 1));  // stay visible NOTE: THIS LINE IS REQUIRED FOR LOOP TO WORK
			commands.push_back(temp.Fade(visDur, visDur, 1, 0));  // disappear instantaneously
			commands.push_back(temp.Fade(visDur + hiddenDur, visDur + hiddenDur, 0, 1));  // reappear instantaneously
			line->Loop(startTime.ms, times, commands);
		}
	}
	points.clear();
}

int Sketch::constResolution(Bezier& b) {
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

int Sketch::dynamicResolution(Bezier& b) {
	points.push_back(b.findPosition(0));
	points.push_back(b.findPosition(RandomRange::calculate(30, 70, 100)));
	points.push_back(b.findPosition(1.0f));
	return 1;
	//int numPoints = b.length / this->resolution; // precheck if bezier is "short"
	//if (numPoints < 2) // nothing to be drawn
	//	return 0;
	//// find average 2nd derivative along bezier to determine "resolution"
	//auto derivs = std::vector<double>();
	//const auto step = 1 / static_cast<float>(numPoints);
	//for (double i = 0.001; i < 1; i += step) {
	//	auto tmp = b.find2ndDerivative(i);
	//	derivs.push_back(std::abs(tmp.x) + std::abs(tmp.y));
	//}
	//auto resolution = std::accumulate(derivs.begin(), derivs.end(), 0) / numPoints; // average of 2nd derivs
	//resolution /= this->resolution; // scale the generated resolution with resolution arg
	//auto ans = 1;
	//auto steps = std::vector<s>();
	//steps.push_back(createS(0.001, derivs[0]));
	//for (double i = 0.001;;) {
	//	auto tmp = b.find2ndDerivative(i);
	//	auto dist = resolution / (std::abs(tmp.x) + std::abs(tmp.y) + 1);
	//	// if points are too close together, don't add it
	//	if (dist < 0.001) {
	//		i += dist;
	//		break;
	//	}
	//	i += dist;
	//	if (i > 1.0 - 0.001)
	//		break;
	//	steps.push_back(createS(i, std::abs(tmp.x) + std::abs(tmp.y)));
	//}
	//steps.push_back(createS(0.999, derivs[derivs.size() - 1]));
	//if (numPoints < steps.size()) { // if constRes results in fewer points, use constRes
	//	return constResolution(b);
	//}
	//for (auto& step : steps) {
	//	points.push_back(b.findPosition(step.pos));
	//	ans++;
	//}
	//return ans + 1;
}

int Sketch::make() {
	// returns 0 upon success

	#if LINUX
	pointMapPath = "Drain/Drain/" + pointMapPath;
	#endif
	std::cout << pointMapPath << "\n";
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

void Sketch::loop(std::vector<Sketch>& v, int times) {
	auto durSoFar = 0;  // sum of duration of each iteration of the loop
	auto totalDur = 0;  // total duration of the loop
	// durSoFar will == totalDur at the end of this function
	for (auto& frame : v) {
		totalDur += frame.visDur;
	}
	const auto loopEndTime = v[0].startTime.ms + totalDur * times;
	for (auto& frame : v) {
		frame.loopEndTime = loopEndTime;
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

	// Lyric 1
	auto start = Time("00:00:489").ms - Timing::whole;
	auto eyesClosed000 = std::vector<Sketch>({
		Sketch("000 eyes closed", Time(start), Time("00:00:489")),
		Sketch("000 eyes closed", Time("00:00:489"), Time("00:01:055"), shift)
											 });
	loop(eyesClosed000, 4);
	make("005 eyes open", Time("00:04:452"), Time("00:05:018"));
	make("005 eyes open", Time("00:05:018"), Time("00:05:584"), shift);
	make("010 su", Time("00:05:584"), Time("00:05:867"));
	make("015 ffo", Time("00:05:867"), Time("00:06:150"));
	make("020 ca", Time("00:06:150"), Time("00:06:433"));
	make("025 ting", Time("00:06:433"), Time("00:06:999"));
	make("025 ting", Time("00:06:999"), Time("00:07:565"), shift);
	make("025 ting", Time("00:07:565"), Time("00:08:131"));
	make("035 puff", Time("00:08:131"), Time("00:08:414"));
	make("040 of", Time("00:08:414"), Time("00:08:697"));
	auto smoke045 = std::vector<Sketch>({
		Sketch("045 smoke", Time("00:08:697"), Time("00:09:263")),
		Sketch("045 smoke", Time("00:09:263"), Time("00:09:829"), shift)
										});
	loop(smoke045, 5);
	make("055 i", Time("00:14:357"), Time("00:14:640"));
	make("060 took", Time("00:14:640"), Time("00:14:923"));
	make("065 your", Time("00:14:923"), Time("00:15:206"));
	make("070 breath", Time("00:15:206"), Time("00:15:489"));
	make("075 in", Time("00:15:489"), Time("00:16:055"));
	make("075 in", Time("00:16:055"), Time("00:16:621"), shift);
	make("075 in", Time("00:16:621"), Time("00:17:187"));
	make("080 and", Time("00:17:187"), Time("00:17:470"));
	make("085 you", Time("00:17:470"), Time("00:17:753"));
	auto spoke090 = std::vector<Sketch>({
		Sketch("090 spoke", Time("00:17:753"), Time("00:18:319")),
		Sketch("090 spoke", Time("00:18:319"), Time("00:18:885"), shift)
										});
	loop(spoke090, 3);
	make("090 spoke", Time("00:21:150"), Time("00:21:999"));
	make("100 and", Time("00:21:963"), Time("00:22:282"));
	make("105 i", Time("00:22:282"), Time("00:22:565"));
	make("110 saw", Time("00:22:565"), Time("00:23:131"));
	make("115 the", Time("00:23:131"), Time("00:23:697"));
	auto world120 = std::vector<Sketch>({
		Sketch("120 world", Time("00:23:697"), Time("00:24:263")),
		Sketch("120 world", Time("00:24:263"), Time("00:24:829"), shift)
										});
	loop(world120, 2);
	make("120 world", Time("00:25:961"), Time("00:26:527"));
	make("125 turn", Time("00:26:527"), Time("00:27:093"));
	auto white130 = std::vector<Sketch>({
		Sketch("130 white", Time("00:27:093"), Time("00:27:659")),
		Sketch("130 white", Time("00:27:659"), Time("00:28:225"), shift)
										});
	loop(white130, 8);
	make("130 white", Time("00:36:150"), Time("00:36:433"));
	make("135 are", Time("00:36:433"), Time("00:36:716"));
	make("140 you", Time("00:36:716"), Time("00:37:140"));
	make("145 still", Time("00:37:140"), Time("00:37:423"));
	make("150 cal", Time("00:37:423"), Time("00:37:848"));
	make("155 ling", Time("00:37:848"), Time("00:38:131"));
	auto me160 = std::vector<Sketch>({
		Sketch("160 me", Time("00:38:131"), Time("00:38:697")),
		Sketch("160 me", Time("00:38:697"), Time("00:39:263"), shift)
									 });
	loop(me160, 2);
	make("170 i", Time("00:40:395"), Time("00:40:678"));
	auto melt175 = std::vector<Sketch>({
		Sketch("175 melt", Time("00:40:678"), Time("00:41:244")),
		Sketch("175 melt", Time("00:41:244"), Time("00:41:810"), shift)
									   });
	loop(melt175, 7);
	make("175 melt", Time("00:48:602"), Time("00:49:168"));
	make("175 melt", Time("00:49:168"), Time("00:49:452"), shift);
	make("180 in", Time("00:49:452"), Time("00:49:735"));
	make("185 to", Time("00:49:735"), Time("00:50:301"));
	make("185 to", Time("00:50:301"), Time("00:50:867"), shift);
	make("185 to", Time("00:50:867"), Time("00:51:433"));
	make("185 to", Time("00:51:433"), Time("00:51:716"), shift);
	make("190 your", Time("00:51:716"), Time("00:51:999"));
	make("195 voice", Time("00:51:999"), Time("00:54:263"), defaultResolution, true, Path::Taper, 0, 1, Easing::Linear, false, false, false, true);
	// Lyric 2
	make("205 push", Time("01:57:659"), Time("01:58:791"), shift, true, Path::Taper, 0, 1, Easing::Linear, false, false, true, false);
	make("205 push", Time("01:58:791"), Time("01:59:074"));
	make("210 ing", Time("01:59:074"), Time("01:59:357"));
	make("215 a", Time("01:59:357"), Time("01:59:640"));
	make("220 side", Time("01:59:640"), Time("02:00:206"));
	make("220 side", Time("02:00:206"), Time("02:00:772"), shift);
	make("220 side", Time("02:00:772"), Time("02:01:338"));
	make("225 my", Time("02:01:338"), Time("02:01:904"));
	auto pain230 = std::vector<Sketch>({
		Sketch("230 pain", Time("02:01:904"), Time("02:02:470")),
		Sketch("230 pain", Time("02:02:470"), Time("02:03:036"), shift),
									   });
	loop(pain230, 4);
	make("235 ex", Time("02:06:433"), Time("02:06:716"));
	make("240 changed", Time("02:06:716"), Time("02:06:999"));
	make("245 bo", Time("02:06:999"), Time("02:07:282"));
	make("250 dy", Time("02:07:282"), Time("02:07:565"));
	make("255 heat", Time("02:07:565"), Time("02:08:131"));
	make("255 heat", Time("02:08:131"), Time("02:08:697"), shift);
	make("255 heat", Time("02:08:697"), Time("02:09:263"));
	make("255 heat", Time("02:09:263"), Time("02:09:546"), shift);
	make("260 a", Time("02:09:546"), Time("02:09:829"));
	make("265 gain", Time("02:09:829"), Time("02:10:395"));
	make("270 and", Time("02:10:395"), Time("02:10:678"));
	make("275 a", Time("02:10:678"), Time("02:10:961"));
	auto gain280 = std::vector<Sketch>({
		Sketch("280 gain", Time("02:10:961"), Time("02:11:527")),
		Sketch("280 gain", Time("02:11:527"), Time("02:12:093"), shift)
									   });
	loop(gain280, 5);
	make("280 gain", Time("02:16:621"), Time("02:16:904"));
	make("285 su", Time("02:16:904"), Time("02:17:187"));
	make("290 ffo", Time("02:17:187"), Time("02:17:470"));
	make("295 ca", Time("02:17:470"), Time("02:17:753"));
	make("300 ting", Time("02:17:753"), Time("02:18:319"));
	make("300 ting", Time("02:18:319"), Time("02:18:885"), shift);
	make("300 ting", Time("02:18:885"), Time("02:19:452"));
	make("305 puff", Time("02:19:452"), Time("02:19:735"));
	make("310 of", Time("02:19:735"), Time("02:20:018"));
	auto smoke315 = std::vector<Sketch>({
		Sketch("315 smoke", Time("02:20:018"), Time("02:20:584")),
		Sketch("315 smoke", Time("02:20:584"), Time("02:21:150"), shift)
										});
	loop(smoke315, 3);
	make("315 smoke", Time("02:23:414"), Time("02:23:980"));
	make("315 smoke", Time("02:23:980"), Time("02:24:263"), shift);
	make("320 and", Time("02:24:263"), Time("02:24:546"));
	make("325 i", Time("02:24:546"), Time("02:24:829"));
	make("330 saw", Time("02:24:829"), Time("02:25:395"));
	make("335 the", Time("02:25:395"), Time("02:25:961"));
	auto world340 = std::vector<Sketch>({
		Sketch("340 world", Time("02:25:961"), Time("02:26:527")),
		Sketch("340 world", Time("02:26:527"), Time("02:27:093"), shift)
										});
	loop(world340, 2);
	make("340 world", Time("02:28:225"), Time("02:28:791"));
	make("345 turn", Time("02:28:791"), Time("02:29:357"));
	make("350 red", Time("02:29:357"), Time("02:33:885"), defaultResolution, true, Path::Taper, 0, 1, Easing::Linear, false, false, false, true);
	// Lyric 3
	make("360 dri", Time("04:02:187"), Time("04:04:168"), shift, true, Path::Taper, 0, 1, Easing::Linear, false, false, true, false);
	make("360 dri", Time("04:04:168"), Time("04:04:452"));
	make("365 pping", Time("04:04:452"), Time("04:05:018"));
	make("365 pping", Time("04:05:018"), Time("04:05:584"), shift);
	make("365 pping", Time("04:05:584"), Time("04:06:150"));
	make("365 pping", Time("04:06:150"), Time("04:06:433"), shift);
	make("370 tri", Time("04:06:433"), Time("04:06:716"));
	make("375 ckling", Time("04:06:716"), Time("04:07:282"));
	make("375 ckling", Time("04:07:282"), Time("04:07:848"), shift);
	make("375 ckling", Time("04:07:848"), Time("04:08:414"));
	make("375 ckling", Time("04:08:414"), Time("04:08:697"), shift);
	make("380 dri", Time("04:08:697"), Time("04:08:980"));
	auto bbling385 = std::vector<Sketch>({
		Sketch("385 bbling", Time("04:08:980"), Time("04:09:546")),
		Sketch("385 bbling", Time("04:09:546"), Time("04:10:112"), shift)
										 });
	loop(bbling385, 3);
	make("385 bbling", Time("04:12:376"), Time("04:12:942"));
	make("390 a", Time("04:12:942"), Time("04:13:225"));
	make("395 li", Time("04:13:225"), Time("04:13:791"));
	make("400 ttle", Time("04:13:791"), Time("04:14:074"));
	auto more405 = std::vector<Sketch>({
		Sketch("405 more", Time("04:14:074"), Time("04:14:640")),
		Sketch("405 more", Time("04:14:640"), Time("04:15:206"), shift)
									   });
	loop(more405, 3);
	make("410 give", Time("04:17:470"), Time("04:17:753"));
	make("415 me", Time("04:17:753"), Time("04:18:319"));
	make("420 some", Time("04:18:319"), Time("04:18:602"));
	auto more425 = std::vector<Sketch>({
		Sketch("425 more", Time("04:18:602"), Time("04:19:168")),
		Sketch("425 more", Time("04:19:168"), Time("04:19:735"), shift)
									   });
	loop(more425, 3);
	make("425 more", Time("04:21:999"), Time("04:22:282"));
	make("430 dri", Time("04:22:282"), Time("04:22:565"));
	make("435 pping", Time("04:22:565"), Time("04:23:131"));
	make("435 pping", Time("04:23:131"), Time("04:23:697"), shift);
	make("435 pping", Time("04:23:697"), Time("04:24:263"));
	make("435 pping", Time("04:24:263"), Time("04:24:546"), shift);
	make("440 trick", Time("04:24:546"), Time("04:24:829"));
	make("445 ling", Time("04:24:829"), Time("04:25:395"));
	make("445 ling", Time("04:25:395"), Time("04:25:961"), shift);
	make("445 ling", Time("04:25:961"), Time("04:26:527"));
	make("445 ling", Time("04:26:527"), Time("04:26:810"), shift);
	make("450 dri", Time("04:26:810"), Time("04:27:093"));
	auto bbling455 = std::vector<Sketch>({
		Sketch("455 bbling", Time("04:27:093"), Time("04:27:659")),
		Sketch("455 bbling", Time("04:27:659"), Time("04:28:225"), shift)
										 });
	loop(bbling455, 3);
	make("455 bbling", Time("04:30:489"), Time("04:31:055")),
		make("465 in", Time("04:31:055"), Time("04:31:338"));
	make("470 to", Time("04:31:338"), Time("04:31:904"));
	make("475 my", Time("04:31:904"), Time("04:32:187"));
	auto core480 = std::vector<Sketch>({
		Sketch("480 core", Time("04:32:187"), Time("04:32:753")),
		Sketch("480 core", Time("04:32:753"), Time("04:33:319"), shift)
									   });
	make("480 core", Time("04:43:508"), Time("04:44:074"));
	loop(core480, 10);
	//Lyric4
	make("490 i", Time("04:44:074"), Time("04:44:640"));
	make("495 dont", Time("04:44:640"), Time("04:45:206"));
	make("500 know", Time("04:45:206"), Time("04:45:772"));
	make("500 know", Time("04:45:772"), Time("04:46:338"), shift);
	make("500 know", Time("04:46:338"), Time("04:46:904"));
	make("505 when", Time("04:46:904"), Time("04:47:470"));
	make("510 i", Time("04:47:470"), Time("04:48:319"));
	make("515 lost", Time("04:48:319"), Time("04:49:168"));
	make("520 my", Time("04:49:168"), Time("04:49:735"));
	auto key525 = std::vector<Sketch>({
		Sketch("525 key", Time("04:49:735"), Time("04:50:301")),
		Sketch("525 key", Time("04:50:301"), Time("04:50:867"), shift)
									  });
	loop(key525, 6);
	make("530 take", Time("04:56:527"), Time("04:57:659"));
	make("535 a", Time("04:57:659"), Time("04:58:791"));
	make("540 vow", Time("04:58:791"), Time("04:59:357"));
	make("540 vow", Time("04:59:357"), Time("04:59:923"), shift);
	make("540 vow", Time("04:59:923"), Time("05:00:489"));
	make("545 and", Time("05:00:489"), Time("05:01:055"));
	make("550 just", Time("05:01:055"), Time("05:02:187"));
	make("555 kill", Time("05:02:187"), Time("05:03:319"));
	auto me560 = std::vector<Sketch>({
		Sketch("560 me", Time("05:03:319"), Time("05:03:885")),
		Sketch("560 me", Time("05:03:885"), Time("05:04:452"), shift)
									 });
	loop(me560, 4);
	auto pause1565 = std::vector<Sketch>({
		Sketch("565 pause1", Time("05:07:848"), Time("05:08:414")),
		Sketch("565 pause1", Time("05:08:414"), Time("05:08:980"), shift)
										 });
	loop(pause1565, 4);
	auto pause2570 = std::vector<Sketch>({
		Sketch("570 pause2", Time("05:12:376"), Time("05:12:942")),
		Sketch("570 pause2", Time("05:12:942"), Time("05:13:508"), shift)
										 });
	loop(pause2570, 4);
	auto pause3560 = std::vector<Sketch>({
		Sketch("575 pause3", Time("05:16:904"), Time("05:17:470")),
		Sketch("575 pause3", Time("05:17:470"), Time("05:18:036"), shift)
										 });
	loop(pause3560, 3);
	make("580 i", Time("05:20:301"), Time("05:20:867"));
	make("585 dont", Time("05:20:867"), Time("05:21:433"));
	make("590 know", Time("05:21:433"), Time("05:21:999"));
	make("590 know", Time("05:21:999"), Time("05:22:565"), shift);
	make("590 know", Time("05:22:565"), Time("05:23:131"));
	make("595 when", Time("05:23:131"), Time("05:23:697"));
	make("600 i", Time("05:23:697"), Time("05:24:546"));
	make("605 lost", Time("05:24:546"), Time("05:25:395"));
	make("610 my", Time("05:25:395"), Time("05:25:961"));
	auto key615 = std::vector<Sketch>({
		Sketch("615 key", Time("05:25:961"), Time("05:26:527")),
		Sketch("615 key", Time("05:26:527"), Time("05:27:093"), shift)
									  });
	loop(key615, 6);
	make("625 take", Time("05:32:753"), Time("05:33:885"));
	make("630 a", Time("05:33:885"), Time("05:35:018"));
	make("635 vow", Time("05:35:018"), Time("05:35:584"));
	make("635 vow", Time("05:35:584"), Time("05:36:150"), shift);
	make("635 vow", Time("05:36:150"), Time("05:36:716"));
	make("640 and", Time("05:36:716"), Time("05:37:282"));
	make("645 just", Time("05:37:282"), Time("05:38:414"));
	make("650 kill", Time("05:38:414"), Time("05:39:546"));
	auto me655 = std::vector<Sketch>({
		Sketch("655 me", Time("05:39:546"), Time("05:40:112")),
		Sketch("655 me", Time("05:40:112"), Time("05:40:678"), shift)
									 });
	loop(me655, 6);
	make("660 collapse1", Time("05:46:338"), Time("05:46:904"));
	make("665 collapse2", Time("05:46:904"), Time("05:47:470"));
	make("670 collapse3", Time("05:47:470"), Time("05:57:659"), defaultResolution, false, Path::Taper, 0, 1, Easing::Linear, false, false, false, true);
	// Last
	make("675 eyes open", Time("06:24:829"), Time("06:31:055"), shift, true, Path::Taper, 0, 1, Easing::Linear, false, false, true, false);
	auto eyesOpen675 = std::vector<Sketch>({
		Sketch("675 eyes open", Time("06:31:055"), Time("06:31:621")),
		Sketch("675 eyes open", Time("06:31:621"), Time("06:32:187"), shift)
										   });
	loop(eyesOpen675, 3);
	make("675 eyes open", Time("06:34:452"), Time("06:34:735"), shift);
	auto eyesClosed680 = std::vector<Sketch>({
		Sketch("680 eyes closed", Time("06:34:735"), Time("06:35:301")),
		Sketch("680 eyes closed", Time("06:35:301"), Time("06:35:867"), shift)
											 });
	loop(eyesClosed680, 2);
	make("680 eyes closed", Time("06:36:999"), Time("06:37:565"));
	make("680 eyes closed", Time("06:37:565"), Time("06:37:848"), shift);
}
