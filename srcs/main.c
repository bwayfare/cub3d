/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 07:17:34 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/23 00:45:43 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	f_get_map(char **line, t_list **list, int *fd, t_mprms *mprms)
{
	int res;

	res = 0;
	while (get_next_line(*fd, line) > 0)
		if (ft_search_map(*line, mprms, &res) > -1
			&& (res == 1 || res == 3))
			ft_lstadd_back(list, ft_lstnew(*line));
		else
			free_line(line);
	if (ft_search_map(*line, mprms, &res) == 0)
		ft_lstadd_back(list, ft_lstnew(*line));
	else
		free_line(line);
	if (mprms->check)
	{
		map_creator(*list, mprms);
		if (ft_ch_elem_map(mprms))
			ch_wall(mprms, mprms->map.map);
	}
}

int		ft_creat_mprms(int *fd, char *argv, t_mprms *mprms, t_list **list)
{
	char		*line;

	struct_init(mprms);
	if (!(*fd = open(argv, O_RDONLY)))
		put_rtfm("Error\nInvalid config file\n");
	if (read(*fd, &line, 0) < 0)
		put_rtfm("Error\nIt is directory\n");
	while (mprms->check && ft_check_full(mprms) != 8 &&
	get_next_line(*fd, &line) > 0 && (parse_line(mprms, line) != -1))
		free_line(&line);
	if (line)
		free_line(&line);
	if (mprms->check)
		f_get_map(&line, list, fd, mprms);
	return (1);
}

void	ft_get_screen_size(int *fd, char **argv, t_mprms *mprms, t_list **list)
{
	if (mprms->screenshot == 0 && mprms->argc == 2)
		ft_creat_mprms(fd, argv[1], mprms, list);
	else
		ft_creat_mprms(fd, argv[2], mprms, list);
	mlx_get_screen_size(mprms->data.mlx, &(mprms->res.screen_x),
	&(mprms->res.screen_y));
	if (mprms->screenshot == 0)
	{
		if (mprms->res.screen_x < mprms->res.x)
			mprms->res.x = mprms->res.screen_x;
		if (mprms->res.screen_y < mprms->res.y)
			mprms->res.y = mprms->res.screen_y;
	}
	else
	{
		if (mprms->res.screen_x < mprms->res.x)
			mprms->res.x = 10000;
		if (mprms->res.screen_y < mprms->res.y)
			mprms->res.y = 10000;
	}
}

void	start_create_param(int *fd, char **argv, t_mprms *mprms, t_list **list)
{
	if (mprms->argc == 3)
		mprms->screenshot = 1;
	else
		mprms->screenshot = 0;
	ft_get_screen_size(fd, argv, mprms, list);
	turn_player(mprms);
	mprms->data.mlx = mlx_init();
	init_texture(mprms);
	mprms->ray.z_buffer = (double *)malloc(mprms->res.x * sizeof(double));
	mprms->colors.floor.trns = create_trgb(mprms->colors.floor.r,
	mprms->colors.floor.g, mprms->colors.floor.b);
	mprms->colors.ceil.trns = create_trgb(mprms->colors.ceil.r,
	mprms->colors.ceil.g, mprms->colors.ceil.b);
	if (mprms->screenshot == 0)
		mprms->data.win = mlx_new_window(mprms->data.mlx,
		(int)W, (int)H, "cub3D");
	mprms->data.img = mlx_new_image(mprms->data.mlx, (int)W, (int)H);
	mprms->data.addr = mlx_get_data_addr(mprms->data.img,
	&mprms->data.bits_per_pixel, &mprms->data.line_length,
	&mprms->data.endian);
	turn_player(mprms);
	draw(mprms, -1);
	if (mprms->screenshot == 1)
		exit(0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_mprms	mprms;
	t_list	*list;

	fd = 0;
	list = NULL;
	if ((mprms.argc = argc) == 2 || (argc == 3 && argv[1][0] == '-' &&
	argv[1][1] == '-' && argv[1][2] == 's' && argv[1][3] == 'a' &&
	argv[1][4] == 'v' && argv[1][5] == 'e' && !argv[1][6]))
		start_create_param(&fd, argv, &mprms, &list);
	else
		put_rtfm("Error\nInvalid arguments\n");
	mlx_hook(mprms.data.win, 2, (1L << 0), &key_press, &mprms);
	mlx_hook(mprms.data.win, 3, (1L << 1), &key_release, &mprms);
	mlx_hook(mprms.data.win, 17, 0, &ft_exit, &mprms);
	mlx_loop_hook(mprms.data.mlx, &main_move_plr, &mprms);
	mlx_loop(mprms.data.mlx);
	free_list(&list);
	clean_struct(&mprms);
	return (0);
}
