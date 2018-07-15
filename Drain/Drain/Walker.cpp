#include "Walker.hpp"

#include "Time.hpp"
#include "Vector2.hpp"

class Walker {
public:
	float fov = 90;
	
	Walker();
	~Walker();

	void walk(Vector2 startPosition, Vector2 endPosition, Time startTime, Time endTime);
	void rotate(Vector2 startAngle, Vector2 endAngle, Time startTime, Time endTime);
private:
}
