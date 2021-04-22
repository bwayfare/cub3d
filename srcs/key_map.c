/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 07:13:29 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:10:37 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		key_press(int key, t_mprms *mprms)
{
	if (key == 13)
		mprms->pres.up = 1;
	if (key == 1)
		mprms->pres.down = 1;
	if (key == 2)
		mprms->pres.right = 1;
	if (key == 0)
		mprms->pres.left = 1;
	if (key == 14)
		mprms->pres.turnright = 1;
	if (key == 12)
		mprms->pres.turnleft = 1;
	if (key == 53)
		exit(0);
	return (0);
}

int		key_release(int key, t_mprms *mprms)
{
	if (key == 13)
		mprms->pres.up = 0;
	if (key == 1)
		mprms->pres.down = 0;
	if (key == 2)
		mprms->pres.right = 0;
	if (key == 0)
		mprms->pres.left = 0;
	if (key == 14)
		mprms->pres.turnright = 0;
	if (key == 12)
		mprms->pres.turnleft = 0;
	return (0);
}
