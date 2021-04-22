/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 07:00:10 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/23 01:00:55 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	dist_sort(t_mprms *mprms)
{
	int i;

	i = 0;
	while (i < mprms->spr.count)
	{
		mprms->spr.spr[i].dist = ((mprms->plr.x - mprms->spr.spr[i].x) *
				(mprms->plr.x - mprms->spr.spr[i].x) + (mprms->plr.y -
				mprms->spr.spr[i].y) * (mprms->plr.y - mprms->spr.spr[i].y));
		i++;
	}
	sort_sprites(mprms->spr.spr, mprms->spr.count);
}

void	draw_spr_param_init(t_mprms *mprms, int i)
{
	mprms->draw_spr.sprt_x = mprms->spr.spr[i].x - mprms->plr.x + 0.5;
	mprms->draw_spr.sprt_y = mprms->spr.spr[i].y - mprms->plr.y + 0.5;
	mprms->draw_spr.nv_det = 1.0 / (mprms->plr.pl_x * mprms->plr.dir_y -
			mprms->plr.dir_x * mprms->plr.pl_y);
	mprms->draw_spr.transf_x = mprms->draw_spr.nv_det * (mprms->plr.dir_y *
														 mprms->draw_spr.sprt_x - mprms->plr.dir_x *
									 mprms->draw_spr.sprt_y);
	mprms->draw_spr.transf_y = mprms->draw_spr.nv_det * (-mprms->plr.pl_y *
														 mprms->draw_spr.sprt_x + mprms->plr.pl_x *
									 mprms->draw_spr.sprt_y);
	mprms->draw_spr.sprt_scrn_x = (int)((W / 2) * (1 +
													 mprms->draw_spr.transf_x / mprms->draw_spr.transf_y));
	mprms->draw_spr.sprt_hght = abs((int)(H /
										  (mprms->draw_spr.transf_y)));
	mprms->draw_spr.drw_strt_y = -mprms->draw_spr.sprt_hght / 2 + H / 2;
	if (mprms->draw_spr.drw_strt_y < 0)
		mprms->draw_spr.drw_strt_y = 0;
	mprms->draw_spr.drw_end_y = mprms->draw_spr.sprt_hght / 2 + H / 2;
	if (mprms->draw_spr.drw_end_y >= H)
		mprms->draw_spr.drw_end_y = H - 1;
}

void	draw_spr_param_init_2(t_mprms *mprms)
{
	mprms->draw_spr.sprt_wdth = abs((int)(H / (mprms->draw_spr.transf_y)));
	mprms->draw_spr.drw_strt_x = -mprms->draw_spr.sprt_wdth /
								 2 + mprms->draw_spr.sprt_scrn_x;
	if (mprms->draw_spr.drw_strt_x < 0)
		mprms->draw_spr.drw_strt_x = 0;
	mprms->draw_spr.drw_end_x = mprms->draw_spr.sprt_wdth /
								2 + mprms->draw_spr.sprt_scrn_x;
	if (mprms->draw_spr.drw_end_x >= W)
		mprms->draw_spr.drw_end_x = W - 1;
}

void	circle_drap_spr(t_mprms *mprms, int stripe)
{
	int y;

	mprms->draw_spr.tx_x = (int)(256 * (stripe -
										(-mprms->draw_spr.sprt_wdth / 2 +
			 mprms->draw_spr.sprt_scrn_x)) * TEXWIDTH /
								 mprms->draw_spr.sprt_wdth) / 256;
	y = mprms->draw_spr.drw_strt_y;
	if (mprms->draw_spr.transf_y > 0 && stripe > 0 && stripe < W &&
		mprms->draw_spr.transf_y < mprms->ray.z_buffer[stripe])
		while (y < mprms->draw_spr.drw_end_y)
		{
			mprms->draw_spr.d = (y) * 256 - H * 128 +
								mprms->draw_spr.sprt_hght * 128;
			mprms->draw_spr.tx_y = ((mprms->draw_spr.d * TEXHEIGHT) /
									mprms->draw_spr.sprt_hght) / 256;
			mprms->draw_spr.color = ft_pixel_take(mprms->spr.obj,
			mprms->draw_spr.tx_x,
			mprms->draw_spr.tx_y);
			if ((int)(*mprms->draw_spr.color) != 0x000000)
				my_mlx_pixel_put(mprms, stripe, y,
				(int)(*mprms->draw_spr.color));
			y++;
		}
}