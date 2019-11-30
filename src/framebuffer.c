#include "mlx.h"
#include "libft.h"
#include "rtx.h"

void t_framebuffer_init(t_framebuffer *fb, void *mlx, int w, int h)
{
	fb->image = mlx_new_image(mlx, WIN_W, WIN_H);
	fb->data = (uint *)mlx_get_data_addr(
			fb->image,
			&fb->bpp,
			&fb->row_len,
			&fb->endian);
	fb->bpp /= 8;
	fb->row_len /= fb->bpp;
	fb->w = w;
	fb->h = h;
}

void t_framebuffer_clear(t_framebuffer *fb)
{
	ft_bzero(fb->data, fb->w * fb->h * sizeof(uint));
}

uint		blend_alpha(uint c1, uint c2, uint a)
{
	uint c;
	uint res;

	c1 &= 0xFFFFFF;
	c2 &= 0xFFFFFF;
	res = 0;
	c = (c1 & 0x0000FF) * (255 - a) + (c2 & 0x0000FF) * a;
	c /= 255;
	res += c;
	c = ((c1 & 0x00FF00) >> 8) * (255 - a) + ((c2 & 0x00FF00) >> 8) * a;
	c /= 255;
	res += c << 8;
	c = ((c1 & 0xFF0000) >> 16) * (255 - a) + ((c2 & 0xFF0000) >> 16) * a;
	c /= 255;
	res += c << 16;
	return (res);
}

void	t_fb_put_pixela(t_app *app, int x, int y, uint color)
{
	unsigned char	a;
	uint			*d;

	if (x < 0 || y < 0 || x >= app->w || y >= app->h)
		return ;
	a = color >> 24;
	d = &app->framebuffer.data[y * app->framebuffer.w + x];
	*d = blend_alpha(*d, color, a);
}

void	t_fb_put_pixel(t_framebuffer *f, int x, int y, uint color)
{
	if (x < 0 || y < 0 || x >= f->w || y >= f->h)
		return ;
	f->data[y * f->w + x] = color;
}
