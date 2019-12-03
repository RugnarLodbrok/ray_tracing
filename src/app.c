#include <time.h>
#include "libft.h"
#include "rtx.h"
#include "mlx.h"
#include "mlx_consts.h"

static int close_hook(int keycode, void *param)
{
	(void)param;
	exit(0);
}

static int loop_hook(t_app *app)
{
	double dt;

	app->time = clock();
	dt = (double)(app->time - app->frame_time) / CLOCKS_PER_SEC;
	if (dt > FRAME_TIME)
	{
		app->frame_time = app->time;
		app->update(app, dt);
		mlx_put_image_to_window(app->M, app->win,
								app->framebuffer.image,
								app->sidebar_w, 0);
	}
	return (0);
}

void t_app_init(t_app *app, void (*update)(t_app *app, double dt))
{
	ft_bzero(app, sizeof(t_app));
	app->w = WIN_W;
	app->h = WIN_H;
	app->sidebar_w = 0;
	app->time = clock();
	app->frame_time = app->time;
	app->update = update;

	app->objs = malloc(sizeof(t_obj *) * 2);
	app->objs[0] = malloc(sizeof(t_obj));
	app->objs[1] = 0;
	app->objs[0]->pos = (t_vec){0, 3., 0};
	app->objs[0]->r = 10.;
	t_cam_init(&app->cam, (t_point){WIN_W, WIN_H});
}

void t_app_up(t_app *app)
{
	app->M = mlx_init();
	app->win = mlx_new_window(app->M, app->sidebar_w + app->w, app->h, "rtx");
	bind_keys(app->win, &app->controller);
	t_framebuffer_init(&app->framebuffer, app->M, app->w, app->h);
}

void t_app_run(t_app *app)
{
	mlx_loop_hook(app->M, loop_hook, app);
	mlx_hook(app->win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	bind_keys(app->win, &app->controller);
	mlx_loop(app->M);

}