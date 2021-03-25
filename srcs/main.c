/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:14:33 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/26 00:28:45 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	f_get_map(char **line, t_list **list, int *fd, t_mprms *mprms)
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
	if (mprms->check == 0)
		return ;
	if (mprms->check)
		map_creator(*list, mprms);
	ft_ch_elem_map(mprms);
	ch_wall(mprms);
}

int		ft_creat_mprms(int *fd, char *argv)
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
	free_list(&list);
	clean_struct(&mprms);
	return (1);
}

int		main(int argc, char **argv)
{
	int fd;

	fd = 0;
	if (argc == 2 || argc == 3)
		ft_creat_mprms(&fd, argv[1]);
	return (0);
}
