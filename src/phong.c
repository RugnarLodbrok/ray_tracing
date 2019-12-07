#include "rtx.h"
#include <math.h>

uint phong_color(t_material *m, double diff, double spec, double i)
{
	uint r;
	uint g;
	uint b;
	double spec_v;

	spec_v = pow(spec, m->spec_exp) * m->spec_v;
	r = (uint)((diff * (m->diff & 0xFF) + spec_v) * i
			   + (m->amb & 0xFF) + .5);
	g = (uint)((diff * ((m->diff & 0xFF00) >> 8) + spec_v) * i
			   + ((m->amb & 0xFF00) >> 8) + .5);
	b = (uint)((diff * ((m->diff & 0xFF0000) >> 16) + spec_v) * i
			   + ((m->amb & 0xFF0000) >> 16) + .5);
	if (g > 255 && b > 255)
		r = r;
	return (r > 255 ? 255 : r) +
		   0x100 * (g > 255 ? 255 : g) +
		   0x10000 * (b > 255 ? 255 : b);
}

uint phong(t_material *m,
		   t_vec *normale, //normalized
		   t_vec *light, //normalized
		   double light_intencity,
		   t_vec *view) //normalized
{
	double diff;
	double spec;
	t_vec refl;

	diff = -t_vec_dot(*normale, *light);
	spec = 0;
	if (diff < 0)
		diff = 0;
	else
	{
		refl = t_vec_mul(*normale, 2 * t_vec_dot(*normale, *view));
		refl = t_vec_sub(refl, *view);
		spec = t_vec_dot(*light, refl);
	}
	return phong_color(m, diff, spec > 0 ? spec : 0, 1);
}
