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

//std::istringstream& operator>>(std::istringstream& iss, Vector2& const& obj)

Sketch::Sketch(const std::string& pointMapPath, const Time& startTime, const Time& endTime,
    const int thickness, const int resolution, const bool dynamic, const Path& brush, const int margin, const Easing& easing )
	: pointMapPath{ pointMapPath }, startTime{ startTime }, endTime{ endTime },
    thickness{ thickness }, resolution{ resolution }, dynamic{ dynamic }, brush { brush }, margin{ margin }, easing{ easing }
{
	brushPath = getPath(brush);
    totalLines = 0;
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

	// draw each point
	/*for (auto &point : points) {
		Storyboard::CreateSprite(brushPath, point)->Scale(startTime.ms, endTime.ms, 10, 10);
	}*/

    auto mpoints = std::vector<Vector2>();
    // find midpoint of points and draw line between them
    for (int i = 0; i < points.size() - 1; i++) {
        totalLines++;
        mpoints.push_back((points[i] + points[i + 1]) / 2);
        float dist = points[i].DistanceBetween(points[i + 1]);
        if (brush == Path::Taper) {
            dist *= 0.8;  // maybe want to scale with length of dist but this is fine for now
        }
        float angle = atan(-(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x + 0.001)); // negate y because osu!
        // experimental approximation optimization method
        /*if (totalLines % 2 != 0)
        continue;
        dist *= 2;*/
        // end experimental
        auto line = Storyboard::CreateSprite(brushPath, mpoints[i]);
        line->ScaleVector(startTime.ms, endTime.ms, Vector2(dist, thickness), Vector2(dist, thickness));  // osu! will optimize dup position
        if (abs(angle) > 0.1)    // only include a rotation command if the angle is significant
            line->Rotate(startTime.ms, startTime.ms, angle, angle); // startTime as endTime because ScaleVector controls lifetime
        Swatch::colorFgToFgSprites({ line }, startTime.ms, startTime.ms);
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
        if (!std::isfinite(step)){
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
    // todo: cap to numPoints (can have <= numPoints)
    int numPoints = b.length / resolution; // precheck if bezier is "short"
    if (numPoints < 2) // nothing to be drawn
        return 0;
    // find average 2nd derivative along bezier to determine "resolution"
    auto derivs = std::vector<double>();
    for (double i = 0.001; i < 1; i += 1 / static_cast<float>(numPoints)) {
        auto tmp = b.find2ndDerivative(i);
        derivs.push_back(abs(tmp.x) + abs(tmp.y));
    }
    auto resolution = std::accumulate(derivs.begin(), derivs.end(), 0) / numPoints;
    resolution /= this->resolution/2.0; // scale the generated resolution with resolution arg
    auto ans = 1;
    auto steps = std::vector<s>();
    steps.push_back(createS(0.001, derivs[0]));
    for (double i = 0.001;;) {
        auto tmp = b.find2ndDerivative(i);
        auto dist = resolution / (abs(tmp.x) + abs(tmp.y) + 1);
        // if points are too close together, don't add it
        if (dist < 0.001) {
            i += dist;
            continue;
        }
        i += dist;
        if (i > 1.0 - 0.001)
            break;
        steps.push_back(createS(i, abs(tmp.x) + abs(tmp.y)));
        //spacing.push_back(abs(dynamicResFactor / tmp.x) + abs(dynamicResFactor / tmp.y));
    }
    steps.push_back(createS(0.999, derivs[derivs.size()-1]));
    if (numPoints < steps.size()) { // if constRes results in fewer points, use constRes
        return constResolution(b);
    }
    for (auto& step : steps) {
        points.push_back(b.findPosition(step.pos));
        ans++;
    }
    return ans + 1;
    // sumSpacing = std::accumulate(spacing.begin(), spacing.end(), 0.0);
    // normalize spacing
    /*for (auto& e: spacing) {
        e /= sumSpacing;
    }*/
    // place points based on spacing
    /*points.push_back(b.findPosition(0.0));
    double progress = 0.0;
    for (int i = 1; i < numPoints-1; i++) {
        auto next = b.findPosition(spacing[i]);
        if (points.back().DistanceBetween(next) > resolution)
            continue;
        progress += spacing[i];
        points.push_back(b.findPosition(progress));
    }
    */
}

const int Sketch::make() {
    // returns 0 upon success
    std::size_t pos = pointMapPath.find(".txt");
    if (pos == std::string::npos)
        return 1;  // error if path doesn't contain .txt
    auto noTxt = pointMapPath.substr(0, pos);
    float xshift=0;
    float yshift=0;
    float xscale=1;
    float yscale=1;
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
        if (line2 == ";"){
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
    // experimental 2
    //auto vv = std::vector<Vector2>();
    //while (std::getline(ifs, line2)) {
    //    if (line2 == ";") {
    //        /*if (!std::getline(ifs, line1))
    //            break;*/
    //        auto bez = Bezier(vv);
    //        draw(bez);
    //        std::cout << ++numBeziers << "/" << count << std::endl;
    //        vv.clear();
    //        continue;
    //    }
    //    std::istringstream iss(line1);
    //    iss >> values[0] >> absorb >> values[1] >> values[2] >> absorb >> values[3] >> values[4] >> absorb >> values[5];
    //    std::istringstream iss2(line2);
    //    iss2 >> values[6] >> absorb >> values[7] >> values[8] >> absorb >> values[9] >> values[10] >> absorb >> values[11];
    //    vv.push_back({ (values[4] - xshift)*xscale, (values[5]+yshift)*yscale });
    //    vv.push_back({ (values[6] - xshift)*xscale, (values[7] + yshift)*yscale });
    //    line1 = line2;
    //}

    // experimental
    /*auto vv = std::vector<Vector2>();
    bool first = true;
    while (std::getline(ifs, line1)) {
        if (line1 == ";") {
            vv.pop_back();
            first = true;
            auto bez = Bezier(vv);
            draw(bez);
            std::cout << ++numBeziers << "/" << count << std::endl;
            vv.clear();
            continue;
        }
        std::istringstream iss(line1);
        iss >> values[0] >> absorb >> values[1] >> values[2] >> absorb >> values[3] >> values[4] >> absorb >> values[5];
        if (!first) {
            vv.push_back({ values[0], values[1] });
            first = false;
        }
        
        vv.push_back({ values[2], values[3] });
        vv.push_back({ values[4], values[5] });
    }*/
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
    *xshift = (minx + maxx) / 2;    // average of all X coordinates
    auto miny = *std::min_element(yvalues.begin(), yvalues.end());
    auto maxy = *std::max_element(yvalues.begin(), yvalues.end());
    *yshift = (miny + maxy) / 2;    // average of all Y coordinates
    //*xscale = (852 - margin * 2) / (abs(minx) + abs(maxx));
    //*yscale = (480 - margin * 2) / (abs(miny) + abs(maxy));
    *xscale = 1;
    *yscale = 1;
}
