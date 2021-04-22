/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 07:02:29 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:13:49 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	wall_draw_init(t_mprms *mprms, int x)
{
	mprms->ray.cam_x = 2 * x / (double)W - 1;
	mprms->ray.rayDirX = mprms->plr.dir_x + mprms->plr.pl_x *
			mprms->ray.cam_x;
	mprms->ray.rayDirY = mprms->plr.dir_y + mprms->plr.pl_y *
			mprms->ray.cam_x;
	mprms->ray.mapX = (int)mprms->plr.x;
	mprms->ray.mapY = (int)mprms->plr.y;
	if (mprms->ray.rayDirY == 0)
		mprms->ray.deltaDistX = 0;
	else if (mprms->ray.rayDirX == 0)
		mprms->ray.deltaDistX = 1;
	else
		mprms->ray.deltaDistX = fabs(1 / mprms->ray.rayDirX);
	if (mprms->ray.rayDirX == 0)
		mprms->ray.deltaDistY = 0;
	else if (mprms->ray.rayDirY == 0)
		mprms->ray.deltaDistY = 1;
	else
		mprms->ray.deltaDistY = fabs(1 / mprms->ray.rayDirY);
	mprms->ray.hit = 0;
	mprms->ray.sideDistX = 0;
}

void	wall_draw_init_2(t_mprms *mprms, int x)
{
	if (mprms->ray.rayDirX < 0)
	{
		mprms->ray.stepX = -1;
		mprms->ray.sideDistX = (mprms->plr.x - mprms->ray.mapX) *
				mprms->ray.deltaDistX;
	}
	else
	{
		mprms->ray.stepX = 1;
		mprms->ray.sideDistX = (mprms->ray.mapX + 1.0 - mprms->plr.x) *
				mprms->ray.deltaDistX;
	}
	if (mprms->ray.rayDirY < 0)
	{
		mprms->ray.stepY = -1;
		mprms->ray.sideDistY = (mprms->plr.y - mprms->ray.mapY) *
				mprms->ray.deltaDistY;
	}
	else
	{
		mprms->ray.stepY = 1;
		mprms->ray.sideDistY = (mprms->ray.mapY + 1.0 - mprms->plr.y) *
				mprms->ray.deltaDistY;
	}
}

void	while_ray_hit(t_mprms *mprms)
{
	while (mprms->ray.hit == 0)
	{
		if (mprms->ray.sideDistX < mprms->ray.sideDistY)
		{
			mprms->ray.sideDistX += mprms->ray.deltaDistX;
			mprms->ray.mapX += mprms->ray.stepX;
			mprms->ray.side = 0;
		}
		else
		{
			mprms->ray.sideDistY += mprms->ray.deltaDistY;
			mprms->ray.mapY += mprms->ray.stepY;
			mprms->ray.side = 1;
		}
		if (WWORLDMAP[mprms->ray.mapX][mprms->ray.mapY] == '1')
			mprms->ray.hit = 1;
	}
}

void	calculate_draw_wall(t_mprms *mprms)
{
	if (mprms->ray.side == 0)
		mprms->ray.perpWallDist = (mprms->ray.mapX - mprms->plr.x +
				(1.0 - mprms->ray.stepX) / 2) / mprms->ray.rayDirX;
	else
		mprms->ray.perpWallDist = (mprms->ray.mapY - mprms->plr.y +
				(1.0 - mprms->ray.stepY) / 2) / mprms->ray.rayDirY;
	mprms->ray.lineHeight = (int)(H / mprms->ray.perpWallDist);
	mprms->ray.drawStart = -mprms->ray.lineHeight / 2 + H / 2;
	if (mprms->ray.drawStart < 0)
		mprms->ray.drawStart = 0;
	mprms->ray.drawEnd = mprms->ray.lineHeight / 2 + H / 2;
	if (mprms->ray.drawEnd >= H)
		mprms->ray.drawEnd = H - 1;
	mprms->ray.texNum = WWORLDMAP[mprms->ray.mapX][mprms->ray.mapY] - 1;
	if (mprms->ray.side == 0)
		mprms->ray.wallX = mprms->plr.y + mprms->ray.perpWallDist *
				mprms->ray.rayDirY;
	else
		mprms->ray.wallX = mprms->plr.x + mprms->ray.perpWallDist *
				mprms->ray.rayDirX;
	mprms->ray.wallX -= floor((mprms->ray.wallX));
	mprms->ray.texX = (int)(mprms->ray.wallX * (double)TEXWIDTH);
	if (mprms->ray.side == 0 && mprms->ray.rayDirX > 0)
		mprms->ray.texX = TEXWIDTH - mprms->ray.texX - 1;
}

void	circle_draw(t_mprms *mprms, int x, int y)
{
	t_tex tex;

	if (mprms->ray.side == 1 && mprms->ray.rayDirY < 0)
		mprms->ray.texX = TEXWIDTH - mprms->ray.texX - 1;
	mprms->ray.step = 1.0 * TEXHEIGHT / mprms->ray.lineHeight;
	mprms->ray.texPos = (mprms->ray.drawStart - H / 2.0 +
			mprms->ray.lineHeight / 2.0) * mprms->ray.step;
	while (y < mprms->ray.drawEnd)
	{
		if (mprms->ray.side == 0 && mprms->ray.stepX > 0)
			tex = mprms->tex.east;
		else if (mprms->ray.side == 0 && mprms->ray.stepX < 0)
			tex = mprms->tex.west;
		else if (mprms->ray.side == 1 && mprms->ray.stepY > 0)
			tex = mprms->tex.south;
		else
			tex = mprms->tex.north;
		mprms->ray.texY = (int)mprms->ray.texPos & (TEXHEIGHT - 1);
		mprms->ray.texPos += mprms->ray.step;
		mprms->ray.color = ft_pixel_take(tex, mprms->ray.texX,
		mprms->ray.texY);
		my_mlx_pixel_put(mprms, x, y, (int)(*mprms->ray.color));
		y++;
	}
	mprms->ray.ZBuffer[x] = mprms->ray.perpWallDist;
}
