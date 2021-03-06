#pragma once

float drand48();

vec3 random_in_unit_disk()
{
	vec3 p;
	do 
	{
		p = 2.0f * vec3(drand48(), drand48(), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
	} while (dot(p, p) >= 1.0f);

	return p;
}

class camera
{
public:
	camera(vec3 from, vec3 at, vec3 up, float vfov, float aspect, float aperture, float focus_dist)
	{
		lens_radius = aperture / 2.0f;
		float theta = vfov * float(M_PI) / 180.0f;
		float half_height = tanf(theta / 2.0f);
		float half_width = aspect * half_height;
		origin = from;
		w = unit_vector(from - at);
		u = unit_vector(cross(up, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
		horizontal = 2.0f * half_width * focus_dist * u;
		vertical = 2.0f * half_height * focus_dist * v;
	}
	ray get_ray(float s, float t)
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lens_radius;
};
