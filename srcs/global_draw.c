#include "../include/cub3d.h"

int		draw(t_mprms *mprms, int x)
{
	draw_floor_ceil(mprms);
	while (++x < W)
	{
		wall_draw_init(mprms, x);
		wall_draw_init_2(mprms, x);
		while_ray_hit(mprms);
		calculate_draw_wall(mprms);
		circle_draw(mprms, x, mprms->ray.drawStart);
	}
	if (mprms->spr.count)
		draw_spr(mprms);
	if (mprms->screenshot == 1)
		screenshot(mprms);
	mlx_put_image_to_window(mprms->data.mlx, mprms->data.win,
							mprms->data.img, 0, 0);
	mlx_destroy_image(mprms->data.mlx, mprms->data.img);
	mprms->data.addr = NULL;
	mprms->data.img = NULL;
	mprms->data.img = mlx_new_image(mprms->data.mlx, (int)W, (int)H);
	mprms->data.addr = mlx_get_data_addr(mprms->data.img,
	&mprms->data.bits_per_pixel, &mprms->data.line_length,
	&mprms->data.endian);
	return (0);
}

void 	draw_spr(t_mprms *mprms)
{
	dist_sort(mprms);
	for (int i = 0; i < mprms->spr.count; i++)
	{
		int stripe;
		draw_spr_param_init(mprms, i);
		draw_spr_param_init_2(mprms);
		stripe = mprms->draw_spr.drawStartX;
		while (stripe < mprms->draw_spr.drawEndX)
		{
			circle_drap_spr(mprms, stripe);
			stripe++;
		}
	}
}