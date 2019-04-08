#include "ray.h"
#include "material.h"
#include "light.h"

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade( Scene *scene, const ray& r, const isect& i ) const
{
	// YOUR CODE HERE

	// For now, this method just returns the diffuse color of the object.
	// This gives a single matte color for every distinct surface in the
	// scene, and that's it.  Simple, but enough to get you started.
	// (It's also inconsistent with the phong model...)

	// Your mission is to fill in this method with the rest of the phong
	// shading model, including the contributions of all the light sources.
    // You will need to call both distanceAttenuation() and shadowAttenuation()
    // somewhere in your code in order to compute shadows and light falloff.
	//!!!!!!!! TODO If we ever want to do the ambient light, we need to update the shade !!!!!!!!! 
	extern TraceUI* traceUI;
	vec3f I = ke;
	vec3f transparency = vec3f(1, 1, 1) - kt;
	vec3f ambient = prod(vec3f(traceUI->m_nAmbientLight, traceUI->m_nAmbientLight, traceUI->m_nAmbientLight), scene->getAmbient());
	ambient = prod(ka, ambient);

	I += prod(transparency, ambient);
	
	for (Scene::cliter iterator = scene->beginLights(); iterator != scene->endLights(); iterator++) {
		vec3f p = r.at(i.t);
		vec3f out_p = p + i.N * RAY_EPSILON;
		//According to Phong Model
		vec3f attenuation = (*iterator)->distanceAttenuation(p)*(*iterator)->shadowAttenuation(out_p);
		vec3f diffuse = prod(transparency, maximum((*iterator)->getDirection(p).normalize().dot(i.N), 0.0) * kd);
		vec3f reflection = (2 * (i.N.dot((*iterator)->getDirection(p).normalize()))*i.N - (*iterator)->getDirection(p)).normalize();
		vec3f specular = pow(maximum(-r.getDirection() * (reflection), 0.0), shininess*128.0) * ks;
		I += prod(attenuation, (diffuse + specular));
	}
	I = I.clamp();
	return I;
}
