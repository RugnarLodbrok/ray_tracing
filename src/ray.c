#include "rtx.h"
#include "mlx_consts.h"

void t_vec_printf(t_vec v)
{
	ft_printf("vec<%.2f %.2f %.2f>\n", v.x, v.y, v.z);
}

void t_ray_transform(t_ray *r, t_mat *m)
{
	r->pos = t_vec_transform4(r->pos, m);
	r->dir = t_vec_transform3(r->dir, m);
}

uint t_ray_cast(t_ray *r, t_obj *obj)
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
