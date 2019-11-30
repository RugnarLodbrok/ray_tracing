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

void t_framebuffer_upscale(t_framebuffer *fb, int scale)
{
	int i;
	int j;

	i = fb->w;
	while (--i >= 0)
	{
		j = fb->h;
		while (--j >= 0)
		{
			fb->data[fb->w * j + i] =
					fb->data[fb->w * (j / scale) + i / scale];
		}
	}
}
