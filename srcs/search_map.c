/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:11:47 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:10:37 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_search_map(char *tmp, t_mprms *mprms, t_list *list, int *res)
{
	if (*tmp == '\0' && (*res == 3))
		put_rtfm(EIMORDP);
	while (tmp && *tmp == 32)
		tmp++;
	if ((*tmp == '1' || *tmp == '\0') && *res != 2)
	{
		if (*tmp == '\0')
		{
			if (*res == 3)
				*res = 4;
			if (*res == 1)
				*res = 3;
			return (1);
		}
		*res = 1;
		return (0);
	}
	else
		return (-1 + (mprms->check = put_rtfm(EIMORDP)));
}

int		size_map(t_list *list, t_mprms *mprms)
{
	int len;
	int i;

	len = 0;
	i = 0;
	mprms->map.size = ft_lstsize(list) + 2;
	while (list)
	{
		if ((len = ft_strlen((char *)(list->content))) > mprms->map.len)
			mprms->map.len = len;
		list = list->next;
	}
	mprms->map.len += 2;
	if (!(mprms->map.map = ft_calloc(mprms->map.size + 1, sizeof(char *))))
		return (mprms->check = put_rtfm(EIM));
	mprms->map.map[mprms->map.size] = NULL;
	while (i < mprms->map.size && mprms->check)
	{
		if (!(mprms->map.map[i] = ft_calloc(mprms->map.len + 1, sizeof(char))))
			return (mprms->check = put_rtfm(EIM));
		mprms->map.map[i][mprms->map.len] = '\0';
		i++;
	}
	return (1);
}

void	map_copy(void *str, char *mprms, int len)
{
	int		i;
	char	*line;

	i = 0;
	line = (char *)str;
	while (i < len)
	{
		if (line && *line && i > 0)
		{
			mprms[i] = *line++;
			i++;
			continue;
		}
		mprms[i] = ' ';
		i++;
	}
	mprms[i] = '\0';
}

void	input_map(t_list *list, t_mprms *mprms)
{
	int i;

	i = 0;
	while (list)
	{
		if (i > 0)
		{
			map_copy(list->content, mprms->map.map[i], mprms->map.len);
			list = list->next;
		}
		else
			map_copy(" ", mprms->map.map[i], mprms->map.len);
		i++;
	}
	map_copy(" ", mprms->map.map[i], mprms->map.len);
	mprms->map.map[i + 1] = NULL;
}

int		map_creator(t_list *list, t_mprms *mprms)
{
	t_list *tmp;

	tmp = list;
	if (list)
	{
		if (size_map(tmp, mprms))
			input_map(tmp, mprms);
		else
			return (0);
	}
	return (1);
}
