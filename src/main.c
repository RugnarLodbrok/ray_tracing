
#include "libft.h"
#include "rtx.h"
#include "mlx.h"
#include "mlx_consts.h"

int update(t_app *app, double dt)
{
	t_cam_move(&app->cam, &app->controller, dt);
	t_cam_draw(&app->cam, &app->framebuffer, app->objs);
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image,
							app->sidebar_w, 0);
}

int main()
{
	t_app app;

	t_app_init(&app, update);
	t_app_up(&app);
	t_app_run(&app);
	return (0);
}
