#include <cmath>
#include <assert.h>
#include <limits.h>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false

	double Tfar = numeric_limits<double>::infinity();
	double Tnear = -Tfar;

	int nearAxis = 0;

	vec3f rDirection = r.getDirection();
	vec3f rOrigin = r.getPosition();

	for (int plane = 0; plane < 3; plane++) {

		// Check if parallel
		if (abs(rDirection[plane]) < RAY_EPSILON * 10) {
			// the position not inside the slabs.
			if (rOrigin[plane] < -0.5 || rOrigin[plane] > 0.5) {
				return false;
			}
		}

		// Compute the intersection distance of the planes
		double t1 = (-0.5 - rOrigin[plane]) / rDirection[plane];
		double t2 = (0.5 - rOrigin[plane]) / rDirection[plane];

		if (t1 > t2) {
			//swap t1 and t2
			double temp = t1;
			t1 = t2;
			t2 = temp;
		}

		if (t1 > Tnear) {
			Tnear = t1;
			nearAxis = plane;
		}

		if (t2 < Tfar) {
			Tfar = t2;
		}

		if (Tnear > Tfar || Tfar < 0) {
			return false;
		}
	}

	vec3f normal(0, 0, 0);
	if (rDirection[nearAxis] < 0.0) {
		normal[nearAxis] = 1.0;
	}
	else {
		normal[nearAxis] = -1.0;
	}

	i.obj = this;
	i.setT(Tnear);
	i.setN(normal);

	return true;
}
