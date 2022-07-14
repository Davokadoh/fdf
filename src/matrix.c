#include "fdf.h"

t_vec3d	translate(t_vec3d pt, int x, int y, int z)
{
	t_vec3d	res;

	res.x = pt.x + x;
	res.y = pt.y + y;
	res.z = pt.z + z;
	return (res);
}

t_vec3d	scale(t_vec3d pt, int zoom)
{
	t_vec3d	res;

	res.x = pt.x * zoom;
	res.y = pt.y * zoom;
	res.z = pt.z * zoom;
	return (res);
}

//a = alpha, b = beta, c = gamma
t_vec3d	rotate(t_vec3d pt, int a, int b, int c)
{
	t_vec3d	res;

	res.x = pt.x * cos(b) * cos(c)\
			+ pt.y * (sin(a) * sin(b) * cos(c) - cos(a) * sin(c))\
			+ pt.z * (cos(a) * sin(b) * cos(c) + sin(a) * sin(c));
	res.y = pt.y;
	res.z = pt.z;
	return (res);
}

//1. Translate map so center is @ origin
//2. Scale x,y,z
//3. Apply rotations
//4. Translate back to center of window
//5. Translate more if env
//6. Get color
t_vec2d	transform(t_vec3d pt)
{
	t_vec3d	res;

	res = translate(pt, -mid_map_w, -mid_map_h, -mid_map_z);
	res = scale(res, zoom);
	res = rotate(res, angle);
	res = translate(res, win_w / 2, win_h / 2, 0);
	res = translate(res, more);
	res.color = get_color(pt.z);
	return (project(res));
}

