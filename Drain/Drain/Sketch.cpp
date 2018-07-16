#include "Sketch.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <memory>
#include <sstream>


/*
This class reads from a text file, parses it, and creates a vector of
Bezier curves to sketch an image
*/

//std::istringstream& operator>>(std::istringstream& iss, Vector2& const& obj)

Sketch::Sketch(const std::string& pointMapPath, const Time& startTime, const Time& endTime,
    const int thickness, const int resolution, const int margin, const Easing& easing, const Path& brush )
	: pointMapPath{ pointMapPath }, startTime{ startTime }, endTime{ endTime },
    thickness{ thickness }, resolution{ resolution }, margin{ margin }, easing { easing }, brush{ brush }
{
	brushPath = getPath(brush);
    totalLines = 0;
}

void Sketch::draw(Bezier b) {
    // todo: tapering effect
	int numPoints = b.length / resolution;	// truncate
    if (!numPoints)
        return;
	auto points = std::vector<Vector2>();
	for (int i = 0; i < numPoints; i++) {
		points.push_back(b.findPosition(static_cast<float>(i) / numPoints));
	}
	// draw each point
	/*for (auto &point : points) {
		Storyboard::CreateSprite(brushPath, point)->Scale(startTime.ms, endTime.ms, thickness, thickness);
	}*/
	auto mpoints = std::vector<Vector2>();
	// find midpoint of points and draw line between them
	for (int i = 0; i < points.size() - 1; i++) {
        totalLines++;
		mpoints.push_back((points[i] + points[i + 1]) / 2);
		float dist = points[i].DistanceBetween(points[i + 1]);
		float angle = atan(-(points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x)); // negate y because osu!
        // some stupid experimental shit
        if (totalLines % 2 == 0)
            continue;
        dist *= 2;
        // end stupid
        auto line = Storyboard::CreateSprite(brushPath, mpoints[i]);
		line->ScaleVector(startTime.ms, endTime.ms, Vector2(dist, thickness), Vector2(dist, thickness));  // osu! will optimize dup position
		line->Rotate(startTime.ms, startTime.ms, angle, angle); // startTime as endTime because ScaleVector controls lifetime
        Swatch::colorFgToFgSprites({ line }, startTime.ms, startTime.ms);
    }
}

const int Sketch::make() {
    // returns 0 upon success
    std::size_t pos = pointMapPath.find(".txt");
    if (pos == std::string::npos)
        return 1;  // error if path doesn't contain .txt
    auto noTxt = pointMapPath.substr(0, pos);
    float xshift;
    float yshift;
    float xscale;
    float yscale;
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
        line1 = line2;
    }
    
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
    *xscale = (852 - margin * 2) / (abs(minx) + abs(maxx));
    *yscale = (480 - margin * 2) / (abs(miny) + abs(maxy));
}
