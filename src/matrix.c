#include "fdf.h"

t_vec	translate(t_vec pt, int x, int y, int z)
{
	t_vec	res;

	res.x = pt.x + x;
	res.y = pt.y + y;
	res.z = pt.z + z;
	return (res);
}

t_vec	scale(t_vec pt, int factor)
{
	t_vec	res;

	res.x = pt.x * factor;
	res.y = pt.y * factor;
	res.z = pt.z * factor;
	return (res);
}

//a = alpha, b = beta, c = gamma
t_vec	rotate(t_vec pt, int a, int b, int c)
{
	t_vec	res;

	res.x = pt.x * cos(b) * cos(c)\
			+ pt.y * (sin(a) * sin(b) * cos(c) - cos(a) * sin(c))\
			+ pt.z * (cos(a) * sin(b) * cos(c) + sin(a) * sin(c));
	res.y = pt.y; //Need actual formula
	res.z = pt.z; //Same
	return (res);
}

t_rgb	z_to_color(int z)
{
	t_rgb	rgb;

	rgb.r = z * int_to_rgb(z).r;
	rgb.g = z * int_to_rgb(z).g;
	rgb.b = z * int_to_rgb(z).b;
	return (rgb);
}

t_pixel project(t_vec v)
{
	t_pixel	pixel;

	pixel.x = v.x;
	pixel.y = v.y;
	pixel.color = z_to_color(v.z);
	return (pixel);
}

//1. Translate map so center is @ origin
//2. Scale x,y,z
//3. Apply rotations
//4. Translate to center of window
//5. Translate more if env
//7. Project to 2d pixels w/ color
t_pixel	transform(t_env *env, t_vec pt)
{
	t_vec	res;

	return ((t_pixel){pt.x, pt.y, {0, 0, 0}}); //testing
	//res = translate(pt, -env->map.width / 2, -env->map.height / 2, -env->map.z / 2); //z may be wrong
	res = translate(pt, -env->map.width / 2, -env->map.height / 2, 0); //z may be wrong
	res = scale(res, env->factor);
	res = rotate(res, env->angle, env->angle, env->angle);
	res = translate(res, env->win_w / 2, env->win_h / 2, 0);
	//res = translate(res, more);
	return (project(res));
}

