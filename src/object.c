#include "mlx_consts.h"
#include "rtx.h"

t_obj t_obj_sphere(t_vec pos, double r)
{
	t_obj obj;

	obj.r = r;
	obj.pos = pos;
	obj.m = (t_material){
			RED * 30,
			RED * 200,
			WHITE,
			8.,
			255
	};
	return obj;
}
