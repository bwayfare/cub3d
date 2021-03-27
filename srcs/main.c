/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:14:33 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/27 22:04:25 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void print(t_mprms *mprms)
{
	printf("R = %d %d\n", mprms->res.x, mprms->res.y);
	printf("C = %d %d %d\n", mprms->colors.cell_color.r, mprms->colors.cell_color.g, mprms->colors.cell_color.b);
	printf("F = %d %d %d\n", mprms->colors.floor_color.r, mprms->colors.floor_color.g, mprms->colors.floor_color.b);
	printf("S = %s\n", mprms->paths.sprt);
	printf("SO = %s\n", mprms->paths.so);
	printf("NO = %s\n", mprms->paths.no);
	printf("EA = %s\n", mprms->paths.ea);
	printf("WE = %s\n", mprms->paths.we);
	printf("check = %d %d %d %d %d %d %d %d = %d\n", mprms->full.res, mprms->full.c_clr, mprms->full.f_clr,
		   mprms->full.sprt, mprms->full.so, mprms->full.no, mprms->full.ea, mprms->full.we, mprms->check);
	for(int i = 0; mprms->map.map && mprms->map.map[i]; i++)
		printf("%s\n", mprms->map.map[i]);
	printf("size map = %d %d\n", mprms->map.len, mprms->map.size);
	printf("player position x = %d y = %d\n", mprms->plr.x, mprms->plr.y);
}

void f_get_map(char **line, t_list **list, int *fd, t_mprms *mprms)
{
	int res;

	res = 0;
	while (get_next_line(*fd, line) > 0
			&& ft_search_map(*line, mprms, *list, &res) > -1)
		if (res == 1)
			ft_lstadd_back(list, ft_lstnew(*line));
		else
		{
			free(*line);
			*line = NULL;
		}
	if (ft_search_map(*line, mprms, *list, &res) == 0)
		ft_lstadd_back(list, ft_lstnew(*line));
	else
	{
		free(*line);
		*line = NULL;
	}
	if (mprms->check)
	{
		map_creator(*list, mprms);
		if (ft_ch_elem_map(mprms))
			ch_wall(mprms, mprms->map.map);
	}
}

int ft_creat_mprms(int *fd, char *argv)
{
	t_mprms		mprms;
	t_list		*list;
	char		*line;

	list = NULL;
	struct_init(&mprms);
	if (!(*fd = open(argv, O_RDONLY)))
		return (0);
	while (mprms.check && ft_check_full(&mprms) != 8 &&
	get_next_line(*fd, &line) > 0 && (parse_line(&mprms, line) != -1))
	{
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (mprms.check)
		f_get_map(&line, &list, fd, &mprms);
	print(&mprms);
	free_list(&list);
	clean_struct(&mprms);
	return (1);
}

int main(int argc, char **argv) {
	int fd;

	fd = 0;
	if (argc == 2 || argc == 3)
		ft_creat_mprms(&fd, argv[1]);
	return (0);
}
