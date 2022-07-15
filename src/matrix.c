#include "fdf.h"

t_vec3d	translate(t_vec3d pt, int x, int y, int z)
{
	t_vec3d	res;

	res.x = pt.x + x;
	res.y = pt.y + y;
	res.z = pt.z + z;
	return (res);
}

t_vec3d	scale(t_vec3d pt, int factor)
{
	t_vec3d	res;

	res.x = pt.x * factor;
	res.y = pt.y * factor;
	res.z = pt.z * factor;
	return (res);
}

//a = alpha, b = beta, c = gamma
t_vec3d	rotate(t_vec3d pt, int a, int b, int c)
{
	t_vec3d	res;

	res.x = pt.x * cos(b) * cos(c)\
			+ pt.y * (sin(a) * sin(b) * cos(c) - cos(a) * sin(c))\
			+ pt.z * (cos(a) * sin(b) * cos(c) + sin(a) * sin(c));
	res.y = pt.y; //Need actual formula
	res.z = pt.z; //Same
	return (res);
}

t_pixel project(t_vec v)
{
	t_pixel	pixel;

	pixel.x = v.x;
	pixel.y = v.y;
	pixel.color = get_color(v.z);
	return (pixel);
}

//1. Translate map so center is @ origin
//2. Scale x,y,z
//3. Apply rotations
//4. Translate to center of window
//5. Translate more if env
//7. Project to 2d pixels w/ color
t_vec2d	transform(t_vec3d pt)
{
	t_vec3d	res;

	res = translate(pt, -map.w / 2, -map.h / 2, -map.z / 2); //z may be wrong
	res = scale(res, factor);
	res = rotate(res, angle);
	res = translate(res, win_w / 2, win_h / 2, 0);
	res = translate(res, more);
	return (project(res));
}

