/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 07:19:24 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:10:37 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_front(t_mprms *mprms, double speed)
{
	if (mprms->pres.up)
	{
		if (mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_x *
			speed)][(int)(mprms->plr.y)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x +
			mprms->plr.dir_x * speed)][(int)(mprms->plr.y)] != '2')
			mprms->plr.x += mprms->plr.dir_x * speed;
		if (mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y +
			mprms->plr.dir_y * speed)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y +
			mprms->plr.dir_y * speed)] != '2')
			mprms->plr.y += mprms->plr.dir_y * speed;
	}
}

void	move_back(t_mprms *mprms, double speed)
{
	if (mprms->pres.down)
	{
		if (mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_x *
			speed)][(int)(mprms->plr.y)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_x *
			speed)][(int)(mprms->plr.y)] != '2')
			mprms->plr.x -= mprms->plr.dir_x * speed;
		if (mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y -
			mprms->plr.dir_y * speed)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y -
			mprms->plr.dir_y * speed)] != '2')
			mprms->plr.y -= mprms->plr.dir_y * speed;
	}
}

void	turn_right(t_mprms *mprms, double speed)
{
	if (mprms->pres.right)
	{
		mprms->ray.oldDirX = mprms->plr.dir_x;
		mprms->plr.dir_x = mprms->plr.dir_x * cos(-speed) -
				mprms->plr.dir_y * sin(-speed);
		mprms->plr.dir_y = mprms->ray.oldDirX * sin(-speed) +
				mprms->plr.dir_y * cos(-speed);
		mprms->ray.oldPlaneX = mprms->plr.pl_x;
		mprms->plr.pl_x = mprms->plr.pl_x * cos(-speed) -
				mprms->plr.pl_y * sin(-speed);
		mprms->plr.pl_y = mprms->ray.oldPlaneX * sin(-speed) +
				mprms->plr.pl_y * cos(-speed);
	}
}

void	turn_left(t_mprms *mprms, double speed)
{
	if (mprms->pres.left)
	{
		mprms->ray.oldDirX = mprms->plr.dir_x;
		mprms->plr.dir_x = mprms->plr.dir_x * cos(speed) -
				mprms->plr.dir_y * sin(speed);
		mprms->plr.dir_y = mprms->ray.oldDirX * sin(speed) +
				mprms->plr.dir_y * cos(speed);
		mprms->ray.oldPlaneX = mprms->plr.pl_x;
		mprms->plr.pl_x = mprms->plr.pl_x * cos(speed) -
				mprms->plr.pl_y * sin(speed);
		mprms->plr.pl_y = mprms->ray.oldPlaneX * sin(speed) +
				mprms->plr.pl_y * cos(speed);
	}
}

int		main_move_plr(t_mprms *mprms)
{
	double speed;

	speed = 0.05;
	move_front(mprms, speed);
	move_back(mprms, speed);
	turn_right(mprms, speed);
	turn_left(mprms, speed);
	move_right(mprms, speed);
	move_left(mprms, speed);
	draw_floor_ceil(mprms);
	if (!mprms->pres.esc)
		draw(mprms, -1);
	return (1);
}