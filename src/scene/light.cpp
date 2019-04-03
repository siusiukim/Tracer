#include <cmath>

#include "light.h"

double DirectionalLight::distanceAttenuation( const vec3f& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


vec3f DirectionalLight::shadowAttenuation( const vec3f& P ) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.

	vec3f direction = getDirection(P);
	vec3f currentPoint = P;
	ray shadowRay(currentPoint, direction);
	vec3f coleur = getColor(P);
	isect intersectPt;
	while ((scene->intersect(shadowRay, intersectPt)) == true) {
		if (intersectPt.getMaterial().kt.iszero()) return vec3f(0, 0, 0); //Soleil source is completely blocked
		currentPoint = shadowRay.at(intersectPt.t);
		shadowRay = ray(currentPoint, direction);
		coleur = prod(coleur, intersectPt.getMaterial().kt);
	}
	return coleur;
}

vec3f DirectionalLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f DirectionalLight::getDirection( const vec3f& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const vec3f& P ) const
{
	// YOUR CODE HERE

	// You'll need to modify this method to attenuate the intensity 
	// of the light based on the distance between the source and the 
	// point P.  For now, I assume no attenuation and just return 1.0

	double d2 = (P - position).length_squared();
	double d = sqrt(d2);
	
	return 1.0;
}

vec3f PointLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f PointLight::getDirection( const vec3f& P ) const
{
	return (position - P).normalize();
}


vec3f PointLight::shadowAttenuation(const vec3f& P) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.

	const vec3f &dir = getDirection(P);
	isect i;
	ray R(P, dir);
	if (scene->intersect(R, i)) {
		const double light_t = (position - P).length();
		if (i.t < light_t) {
			return vec3f();
		}
		else {
			return vec3f(1.0, 1.0, 1.0);
		}
	}
	else {
		return vec3f(1.0, 1.0, 1.0);
	}
}
