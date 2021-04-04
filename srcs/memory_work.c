/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:13:23 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/31 20:47:27 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	struct_init_2(t_mprms *mprms)
{
	mprms->map.size = 0;
	mprms->map.len = 0;
	mprms->map.map = NULL;
	mprms->check = 1;
	mprms->plr.pl = '\0';
	mprms->plr.x = 0;
	mprms->plr.y = 0;
	mprms->plr.dir_x = 0;
	mprms->plr.dir_y = 0;
	mprms->ray.x = 0;
	mprms->ray.y = 0;
}

void	struct_init(t_mprms *mprms)
{
	mprms->colors.floor_color.r = -1;
	mprms->colors.floor_color.g = -1;
	mprms->colors.floor_color.b = -1;
	mprms->colors.cell_color.r = -1;
	mprms->colors.cell_color.g = -1;
	mprms->colors.cell_color.b = -1;
	mprms->full.f_clr = 0;
	mprms->full.c_clr = 0;
	mprms->full.sprt = 0;
	mprms->full.we = 0;
	mprms->full.ea = 0;
	mprms->full.no = 0;
	mprms->full.so = 0;
	mprms->full.res = 0;
	mprms->res.x = 0;
	mprms->res.y = 0;
	mprms->paths.so = NULL;
	mprms->paths.no = NULL;
	mprms->paths.ea = NULL;
	mprms->paths.we = NULL;
	mprms->paths.sprt = NULL;
	struct_init_2(mprms);
}

void	clean_struct(t_mprms *mprms)
{
	int i;

	i = 0;
	if (mprms->paths.sprt != NULL)
		free(mprms->paths.sprt);
	if (mprms->paths.we != NULL)
		free(mprms->paths.we);
	if (mprms->paths.ea != NULL)
		free(mprms->paths.ea);
	if (mprms->paths.no != NULL)
		free(mprms->paths.no);
	if (mprms->paths.so != NULL)
		free(mprms->paths.so);
	if (mprms->map.map)
	{
		while (mprms->map.map[i] != NULL)
		{
			free(mprms->map.map[i]);
			i++;
		}
		free(mprms->map.map);
	}
}

void	free_list(t_list **head)
{
	t_list *tmp;

	if (*head == NULL)
		return ;
	if (*head)
	{
		while ((*head)->next)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp->content);
			free(tmp);
		}
		free((*head)->content);
		free(*head);
	}
}
