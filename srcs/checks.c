/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:14:09 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/25 22:20:08 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_check_clr(t_mprms *mprms, char *str)
{
	if (mprms->full.c_clr == 1 || mprms->colors.ceil.r != -1)
	{
		if (mprms->colors.ceil.r < 0 ||
			mprms->colors.ceil.r > 255)
			return (-1 + (mprms->check = put_rtfm(str)));
		if (mprms->colors.ceil.g < 0 ||
			mprms->colors.ceil.g > 255)
			return (-1 + (mprms->check = put_rtfm(str)));
		if (mprms->colors.ceil.b < 0 ||
			mprms->colors.ceil.b > 255)
			return (-1 + (mprms->check = put_rtfm(str)));
	}
	if (mprms->full.f_clr == 1 || mprms->colors.floor.r != -1)
	{
		if (mprms->colors.floor.r < 0 ||
			mprms->colors.floor.r > 255)
			return (-1 + (mprms->check = put_rtfm(str)));
		if (mprms->colors.floor.g < 0 ||
			mprms->colors.floor.g > 255)
			return (-1 + (mprms->check = put_rtfm(str)));
		if (mprms->colors.floor.b < 0 ||
			mprms->colors.floor.b > 255)
			return (-1 + (mprms->check = put_rtfm(str)));
	}
	return (1);
}

int		ft_check_full(t_mprms *mprms)
{
	int count;

	count = mprms->full.f_clr + mprms->full.c_clr + mprms->full.sprt +
	mprms->full.we + mprms->full.ea + mprms->full.no + mprms->full.so +
	mprms->full.res;
	return (count);
}
