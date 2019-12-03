#include "rtx.h"
#include "mlx_consts.h"
#include <math.h>

void t_vec_printf(t_vec v)
{
	ft_printf("vec<%.2f %.2f %.2f>\n", v.x, v.y, v.z);
}

void t_ray_printf(t_ray r)
{
	ft_printf("ray<%.2f %.2f %.2f>-<%.2f %.2f %.2f>\n",
			  r.pos.x, r.pos.y, r.pos.z,
			  r.dir.x, r.dir.y, r.dir.z);
}

void t_ray_transform(t_ray *r, t_mat *m)
{
	r->pos = t_vec_transform4(r->pos, m);
	r->dir = t_vec_transform3(r->dir, m);
}

uint t_ray_cast_naive(t_ray *r, t_obj *obj)
{
	t_vec d;
	t_vec p;
	uint color;

	d = t_vec_sub(obj->pos, r->pos);
	p = t_vec_proj(d, r->dir); //proj d onto r->dir;
	d = t_vec_sub(d, p);
	if (t_vec_len(d) > obj->r)
		color = 0;
	else
		color = (RED * 255);
	return color;
}

//return normale or zero-vec
t_vec t_ray_march(t_ray *r, t_obj *obj)
{
	double distance;
	t_vec pos;
	t_vec ret;

	distance = RAY_CAST_MAX_DISTANCE;
	pos = r->pos;
	while (distance > RAY_MARCH_EPS)
	{
		if (distance > RAY_CAST_MAX_DISTANCE)
		{
			return (t_vec){0, 0, 0};
		}
		distance = t_vec_len(t_vec_sub(obj->pos, pos)) - obj->r;
		t_vec_translate(&pos, t_vec_mul(r->dir, distance));
	}
	ret = t_vec_sub(pos, obj->pos);
	t_vec_normalize(&ret);
	return ret;
}

uint t_ray_cast(t_ray *r, t_obj *obj)
{
	t_vec normale;
	double dot;

	normale = t_ray_march(r, obj);
	dot = fabs(t_vec_dot(normale, (t_vec){1, 1, 1}));
	return RED * (int)(dot / 3 * 255);
//	return t_ray_cast_naive(r, obj);
}
