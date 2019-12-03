#include "rtx.h"
#include "mlx.h"
#include <time.h>

void update(t_app *app, double dt)
{
	static int frame_cnt = 0;

	frame_cnt++;
	ft_printf("framerate: %f\n", (double)(frame_cnt * CLOCKS_PER_SEC) / clock());

	t_cam_move(&app->cam, &app->controller, dt);
	t_cam_draw(&app->cam, &app->framebuffer, app->objs[0]);
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
