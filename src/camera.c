#include <math.h>
#include "libft.h"
#include "rtx.h"
#include "mlx_consts.h"

void t_cam_init_projection(t_cam *c)
{
	double tg;
	double near;
	double ze;

	ze = exp(c->zoom / 100);
	tg = sin(radians(FOV / 2)) / cos(radians(FOV / 2)) * ze;
	near = 10.;
	if (c->projection_type == PROJ_PERSPECTIVE)
		c->proj = projection_perspective(near, tg * near,
										 tg * near * WIN_H / WIN_W,
										 9999.);
	else
		c->proj = projection_isometric((double)WIN_W * ze,
									   (double)WIN_H * ze);
}

void t_cam_init(t_cam *c, t_point display_res)
{
	int w;
	int h;

	w = display_res.x;
	h = display_res.y;
	t_mat_reset(&c->v3);
	t_mat_translate(&c->v3, (t_vec){0, 0, -400});
	c->v1 = (t_mat){{
							{1, 0, 0, 0},
							{0, 0, -1, 0},
							{0, 1, 0, 0},
							{0, 0, 0, 1}}};
	t_mat_reset(&c->v2);
	c->disp = (t_mat){{
							  {.5 * w, 0, 0, .5 * w},
							  {0, .5 * h, 0, .5 * h},
							  {0, 0, 0, 0},
							  {0, 0, 0, 1}}};
	c->zoom = 0;
	c->projection_type = PROJ_PERSPECTIVE;
	t_cam_init_projection(c);
}

void t_cam_draw(t_cam *cam, t_framebuffer *fb, t_obj **objs)
{

}

void t_cam_move(t_cam *cam, t_controller *ctrl, double dt)
{
	int mouse_dx;
	int mouse_dy;

	if (ctrl->d_yaw)
	{
		cam->v1 = t_mat_mul(cam->v1, t_mat_rot(
				(t_vec){0, 0, 1},
				radians(ctrl->d_yaw)));
	}
	if (ctrl->d_pitch)
	{
		cam->v2 = t_mat_mul(cam->v2, t_mat_rot(
				(t_vec){1, 0, 0},
				radians(ctrl->d_pitch)));
	}
	if (ctrl->dx || ctrl->dz)
	{
		t_mat_translate(&cam->v3, (t_vec){ctrl->dx, 0, ctrl->dz});
	}
//	if (ctrl->d_zoom)
//	{
//		cam->zoom += ctrl->d_zoom;
//		t_cam_init_projection(cam);
//	}
	if (ctrl->mouse.buttons[MOUSE_B_LEFT])
	{
		mouse_dx = ctrl->mouse.click_pos[MOUSE_B_LEFT].x - ctrl->mouse.pos.x;
		mouse_dy = ctrl->mouse.click_pos[MOUSE_B_LEFT].y - ctrl->mouse.pos.y;
		cam->v1 = t_mat_mul(cam->v1, t_mat_rot(
				(t_vec){0, 0, 1},
				radians((double)mouse_dx / 100)));
		cam->v2 = t_mat_mul(cam->v2, t_mat_rot(
				(t_vec){1, 0, 0},
				radians((double)mouse_dy / 100)));
	}
}
