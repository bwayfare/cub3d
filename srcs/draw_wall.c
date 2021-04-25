/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 07:02:29 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/23 00:56:10 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	wall_draw_init(t_mprms *mprms, int x)
{
	mprms->ray.cam_x = 2 * x / (double)W - 1;
	mprms->ray.r_dir_x = mprms->plr.dir_x + mprms->plr.pl_x *
	mprms->ray.cam_x;
	mprms->ray.r_dir_y = mprms->plr.dir_y + mprms->plr.pl_y *
	mprms->ray.cam_x;
	mprms->ray.mp_x = (int)mprms->plr.x;
	mprms->ray.mp_y = (int)mprms->plr.y;
	if (mprms->ray.r_dir_y == 0)
		mprms->ray.dlt_dst_x = 0;
	else if (mprms->ray.r_dir_x == 0)
		mprms->ray.dlt_dst_x = 1;
	else
		mprms->ray.dlt_dst_x = fabs(1 / mprms->ray.r_dir_x);
	if (mprms->ray.r_dir_x == 0)
		mprms->ray.dlt_dst_y = 0;
	else if (mprms->ray.r_dir_y == 0)
		mprms->ray.dlt_dst_y = 1;
	else
		mprms->ray.dlt_dst_y = fabs(1 / mprms->ray.r_dir_y);
	mprms->ray.hit = 0;
	mprms->ray.sd_dst_x = 0;
}

void	wall_draw_init_2(t_mprms *mprms)
{
	if (mprms->ray.r_dir_x < 0)
	{
		mprms->ray.stp_x = -1;
		mprms->ray.sd_dst_x = (mprms->plr.x - mprms->ray.mp_x) *
		mprms->ray.dlt_dst_x;
	}
	else
	{
		mprms->ray.stp_x = 1;
		mprms->ray.sd_dst_x = (mprms->ray.mp_x + 1.0 - mprms->plr.x) *
		mprms->ray.dlt_dst_x;
	}
	if (mprms->ray.r_dir_y < 0)
	{
		mprms->ray.stp_y = -1;
		mprms->ray.sd_dts_y = (mprms->plr.y - mprms->ray.mp_y) *
		mprms->ray.dlt_dst_y;
	}
	else
	{
		mprms->ray.stp_y = 1;
		mprms->ray.sd_dts_y = (mprms->ray.mp_y + 1.0 -
				mprms->plr.y) * mprms->ray.dlt_dst_y;
	}
}

void	while_ray_hit(t_mprms *mprms)
{
	while (mprms->ray.hit == 0)
	{
		if (mprms->ray.sd_dst_x < mprms->ray.sd_dts_y)
		{
			mprms->ray.sd_dst_x += mprms->ray.dlt_dst_x;
			mprms->ray.mp_x += mprms->ray.stp_x;
			mprms->ray.side = 0;
		}
		else
		{
			mprms->ray.sd_dts_y += mprms->ray.dlt_dst_y;
			mprms->ray.mp_y += mprms->ray.stp_y;
			mprms->ray.side = 1;
		}
		if (WWORLDMAP[mprms->ray.mp_x][mprms->ray.mp_y] == '1')
			mprms->ray.hit = 1;
	}
}

void	calculate_draw_wall(t_mprms *mprms)
{
	if (mprms->ray.side == 0)
		mprms->ray.prp_wall_dst = (mprms->ray.mp_x - mprms->plr.x +
		(1.0 - mprms->ray.stp_x) / 2) / mprms->ray.r_dir_x;
	else
		mprms->ray.prp_wall_dst = (mprms->ray.mp_y - mprms->plr.y +
		(1.0 - mprms->ray.stp_y) / 2) / mprms->ray.r_dir_y;
	mprms->ray.line_hght = (int)(H / mprms->ray.prp_wall_dst);
	mprms->ray.drw_start = -mprms->ray.line_hght / 2 + H / 2;
	if (mprms->ray.drw_start < 0)
		mprms->ray.drw_start = 0;
	mprms->ray.drw_end = mprms->ray.line_hght / 2 + H / 2;
	if (mprms->ray.drw_end >= H)
		mprms->ray.drw_end = H;
	mprms->ray.tx_num = WWORLDMAP[mprms->ray.mp_x][mprms->ray.mp_y] - 1;
	if (mprms->ray.side == 0)
		mprms->ray.wll_x = mprms->plr.y + mprms->ray.prp_wall_dst *
		mprms->ray.r_dir_y;
	else
		mprms->ray.wll_x = mprms->plr.x + mprms->ray.prp_wall_dst *
		mprms->ray.r_dir_x;
	mprms->ray.wll_x -= floor((mprms->ray.wll_x));
	mprms->ray.tx_x = (int)(mprms->ray.wll_x * (double)TEXWIDTH);
	if (mprms->ray.side == 0 && mprms->ray.r_dir_x > 0)
		mprms->ray.tx_x = TEXWIDTH - mprms->ray.tx_x - 1;
}

void	circle_draw(t_mprms *mprms, int x, int y)
{
	t_tex tex;

	if (mprms->ray.side == 1 && mprms->ray.r_dir_y < 0)
		mprms->ray.tx_x = TEXWIDTH - mprms->ray.tx_x - 1;
	mprms->ray.step = 1.0 * TEXHEIGHT / mprms->ray.line_hght;
	mprms->ray.tx_pos = (mprms->ray.drw_start - H / 2.0 +
	mprms->ray.line_hght / 2.0) * mprms->ray.step;
	while (y < mprms->ray.drw_end)
	{
		if (mprms->ray.side == 0 && mprms->ray.stp_x > 0)
			tex = mprms->tex.south;
		else if (mprms->ray.side == 0 && mprms->ray.stp_x < 0)
			tex = mprms->tex.north;
		else if (mprms->ray.side == 1 && mprms->ray.stp_y > 0)
			tex = mprms->tex.east;
		else
			tex = mprms->tex.west;
		mprms->ray.tx_y = (int)mprms->ray.tx_pos & (TEXHEIGHT - 1);
		mprms->ray.tx_pos += mprms->ray.step;
		mprms->ray.color = ft_pixel_take(tex, mprms->ray.tx_x,
		mprms->ray.tx_y);
		my_mlx_pixel_put(mprms, x, y, (int)(*mprms->ray.color));
		y++;
	}
	mprms->ray.z_buffer[x] = mprms->ray.prp_wall_dst;
}
