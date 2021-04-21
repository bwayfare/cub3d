#include "../include/cub3d.h"

void            my_mlx_pixel_put(t_mprms *mprms, int x, int y, int color)
{
	char    *dst;

	dst = mprms->data.addr + (y * mprms->data.line_length +
			x * (mprms->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 		draw_floor_ceil(t_mprms *mprms)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < mprms->res.y / 2)
	{
		while (x < mprms->res.x)
			my_mlx_pixel_put(mprms, x++, y, mprms->colors.ceil.trns);
		y++;
		x = 0;
	}
	while (y < mprms->res.y)
	{
		while (x < mprms->res.x)
			my_mlx_pixel_put(mprms, x++, y, mprms->colors.floor.trns);
		y++;
		x = 0;
	}
}

int		create_trgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

void sort_sprites(t_spr *spr, int count)
{
	t_spr tmp;
	int i;
	int j;

	i = 0;
	while (i < count - 1)
	{
		j = i;
		while (j < count)
		{
			if (spr[i].dist < spr[j].dist)
			{
				tmp = spr[i];
				spr[i] = spr[j];
				spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

unsigned int	*ft_pixel_take(t_tex tex, int x, int y)
{
	return ((unsigned int *)(tex.w_img.addr +
			(y * tex.w_img.line_l + x * (tex.w_img.bpp / 8))));
}