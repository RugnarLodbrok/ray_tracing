#include "mlx_consts.h"
#include "rtx.h"

t_obj t_obj_new_sphere(t_vec pos, double r)
{
	t_obj obj;
	t_obj_sphere *o;

	obj.pos = pos;
	obj.m = (t_material){
			BLUE * 50,
			RED * 200,
			WHITE,
			8.,
			255
	};
	o = malloc(sizeof(t_obj_sphere));
	o->r = r;
	obj.obj = o;
	return obj;
}

double t_obj_sphere_distance(t_obj *obj, t_vec p)
{
	return t_vec_len(t_vec_sub(obj->pos, p)) - ((t_obj_sphere *)(obj->obj))->r;
}
