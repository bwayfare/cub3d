/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:13:13 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/31 22:20:44 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_ch_elem_if(t_mprms *mprms, char tmp)
{
	if (tmp != '0')
		if (tmp != '1')
			if (tmp != '2')
				if (tmp != ' ')
				{
					if (tmp == 'N' || tmp == 'W' || tmp == 'S' || tmp == 'E')
					{
						if (mprms->plr.pl == '\0')
							mprms->plr.pl = tmp;
						else
							mprms->check = put_rtfm("Invalid map\n");
					}
					else
						mprms->check = put_rtfm("Invalid map\n");
				}
}

int		ft_ch_elem_map(t_mprms *mprms)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (i < mprms->map.size && mprms->check)
	{
		j = 0;
		while (j < mprms->map.len && mprms->check)
		{
			tmp = mprms->map.map[i][j];
			ft_ch_elem_if(mprms, tmp);
			j++;
		}
		i++;
	}
	if (mprms->plr.pl == '\0')
		mprms->check = put_rtfm("No player\n");
	return (mprms->check);
}

void	ch_wall_if(t_mprms *mprms, char **arr, int i, int j)
{
	if (i != 0 && j != 0 && !(arr[i - 1][j - 1] == '\0' ||
		arr[i - 1][j - 1] == ' ' || arr[i - 1][j - 1] == '1'))
		mprms->check = 0;
	if (i > 0 && !(arr[i - 1][j] == '\0' ||
		arr[i - 1][j] == ' ' || arr[i - 1][j] == '1'))
		mprms->check = 0;
	if (i > 0 && !(arr[i - 1][j + 1] == '\0' ||
		arr[i - 1][j + 1] == ' ' || arr[i - 1][j + 1] == '1'))
		mprms->check = 0;
	if (j > 0 && !(arr[i][j - 1] == '\0' ||
		arr[i][j - 1] == ' ' || arr[i][j - 1] == '1'))
		mprms->check = 0;
	if (!(arr[i][j + 1] == '\0' || arr[i][j + 1] == ' ' ||
		arr[i][j + 1] == '1'))
		mprms->check = 0;
	if (i < (mprms->map.size - 1) && j != 0 && !(arr[i + 1][j - 1] == '\0' ||
		arr[i + 1][j - 1] == ' ' || arr[i + 1][j - 1] == '1'))
		mprms->check = 0;
	if (i < (mprms->map.size - 1) && !(arr[i + 1][j] == '\0' ||
		arr[i + 1][j] == ' ' || arr[i + 1][j] == '1'))
		mprms->check = 0;
	if (i < (mprms->map.size - 1) && !(arr[i + 1][j + 1] == '\0' ||
		arr[i + 1][j + 1] == ' ' || arr[i + 1][j + 1] == '1'))
		mprms->check = 0;
}

int		ch_wall(t_mprms *mprms, char **arr)
{
	int		i;
	int		j;

	i = 0;
	while (i < mprms->map.size && mprms->check)
	{
		j = 0;
		while (j < mprms->map.len && mprms->check)
		{
			if (arr[i][j] == ' ')
				ch_wall_if(mprms, arr, i, j);
			if (arr[i][j] == 'N' || arr[i][j] == 'E' || arr[i][j] == 'S'
				|| arr[i][j] == 'W')
			{
				mprms->plr.x = i + 0.5;
				mprms->plr.y = j + 0.5;
			}
			j++;
		}
		i++;
	}
	if (mprms->check == 0)
		put_rtfm("Error\nInvalid wall in map\n");
	return (mprms->check);
}
