#ifndef RTX_H
# define RTX_H


# define WIN_W 320
# define WIN_H 240
# define WIN_W_2 ((int)(WIN_W/2))
# define WIN_H_2 ((int)(WIN_H/2))

# define FRAME_RATE 10
# define FRAME_TIME 1./FRAME_RATE

# define FOV 100.
# define PROJ_PERSPECTIVE 1
# define PROJ_ISOMETRIC 0

# include "libft.h"
# include "ft_linalg.h"

typedef struct
{
	t_mat m;
	t_vec pos;
	double r;
} t_obj;

typedef struct
{
	t_vec pos;
	t_vec dir;
} t_ray;

typedef struct
{
	int w;
	int h;
	void *image;
	uint *data;
	int bpp;
	int endian;
	int row_len;
} t_framebuffer;


typedef struct
{
	double zoom;
	int projection_type;
	t_mat v1;
	t_mat v2;
	t_mat v3;
	t_mat proj;
	t_mat disp;
} t_cam;

typedef struct
{
	int buttons[8];
	t_point pos;
	t_point click_pos[8];
	t_point release_pos[8];
} t_mouse;


typedef struct
{
	int keyboard[128];
	t_mouse mouse;
	int d_yaw;
	int d_pitch;
	int d_tilt;
	int dx;
	int dy;
	int dz;
} t_controller;

typedef struct s_app
{
	void *M;
	void *win;
	int w;
	int h;
	int sidebar_w;
	t_cam cam;
	t_framebuffer framebuffer;
	t_controller controller;
	t_obj **objs;
	time_t time;
	time_t frame_time;
	void (*update)(struct s_app *app, double dt);
} t_app;

void t_app_init(t_app *app, void (*update)(t_app *app, double dt));
void t_app_up(t_app *app);
void t_app_run(t_app *app);

void t_cam_init(t_cam *c, t_point display_res);
void t_cam_init_projection(t_cam *c);
void t_cam_draw(t_cam *cam, t_framebuffer *fb, t_obj *obj);
void t_cam_move(t_cam *cam, t_controller *ctrl, double dt);

t_mat projection_isometric(double fov_width, double fov_height);
t_mat projection_perspective(double n, double w, double h, double f);
void bind_keys(void *win, t_controller *c);
void t_framebuffer_init(t_framebuffer *fb, void *mlx, int w, int h);
void t_framebuffer_clear(t_framebuffer *fb);
void t_fb_put_pixel(t_framebuffer *f, int x, int y, uint color);

void t_ray_transform(t_ray *r, t_mat *m);
uint t_ray_cast(t_ray *r, t_obj *obj);
void t_ray_printf(t_ray r);

#endif
