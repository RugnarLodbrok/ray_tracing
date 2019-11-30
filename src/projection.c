#include "rtx.h"

t_mat projection_isometric(double fov_width, double fov_height)
{
	return ((t_mat){{
							{2. / fov_width, 0, 0, 0},
							{0, 2. / fov_height, 0, 0},
							{0, 0, 0, 0},
							{0, 0, 0, 1}}});
}

t_mat projection_perspective(double n, double w, double h, double f)
{
	double l;
	double r;
	double b;
	double t;

	l = -w / 2;
	r = w / 2;
	b = -h / 2;
	t = h / 2;
	return (t_mat){{
						   {2 * n / (r - l), 0, (r + l) / (r - l), 0},
						   {0, 2 * n / (t - b), (t + b) / (t - b), 0},
						   {0, 0, -(f + n) / (f - n), -2 * f * n / (f - n)},
						   {0, 0, -1, 0}}};
}
