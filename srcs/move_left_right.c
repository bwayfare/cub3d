/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 07:17:51 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:10:37 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_left(t_mprms *mprms, double speed)
{
	if (mprms->pres.turnright)
	{
		if (mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_y *
			(speed * 1.3))][(int)(mprms->plr.y)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_y *
			(speed * 1.3))][(int)(mprms->plr.y)] != '2')
			mprms->plr.x -= mprms->plr.dir_y * speed;
		if (mprms->map.map[(int)(mprms->plr.x)]
			[(int)(mprms->plr.y + mprms->plr.dir_x * (speed * 1.3))] != '1' &&
			mprms->map.map[(int)(mprms->plr.x)]
			[(int)(mprms->plr.y + mprms->plr.dir_x * (speed * 1.3))] != '2')
			mprms->plr.y += mprms->plr.dir_x * speed;
	}
}

void	move_right(t_mprms *mprms, double speed)
{
	if (mprms->pres.turnleft)
	{
		if (mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_y *
			(speed * 1.3))][(int)(mprms->plr.y)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_y *
			(speed * 1.3))][(int)(mprms->plr.y)] != '2')
			mprms->plr.x += mprms->plr.dir_y * speed;
		if (mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y -
			mprms->plr.dir_x * (speed * 1.3))] != '1' &&
			mprms->map.map[(int)(mprms->plr.x)]
			[(int)(mprms->plr.y - mprms->plr.dir_x * (speed * 1.3))] != '2')
			mprms->plr.y -= mprms->plr.dir_x * speed;
	}
}
