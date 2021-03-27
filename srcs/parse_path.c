/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:13:36 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/27 17:38:36 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		check_path(char *str)
{
	int		fd;
	char	*end;

	if (str == NULL)
		return (-1 + (put_rtfm("Invalid path\n")));
	end = str;
	while (*end)
		end++;
	if (*--end != 'm' || *--end != 'p' || *--end != 'x' ||
	*--end != '.' || !ft_isalnum(*--end))
		return (-1 + (put_rtfm("Invalid path\n")));
	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (-1 + (put_rtfm("Invalid path\n")));
}

char	*get_path(char *line)
{
	char	*tmp;
	int		len;
	char	*str;
	char	*head;

	len = 0;
	while (*line == 32)
		line++;
	if (*line != '.')
		if (*line != '~')
			if (*line != '/')
				return (NULL);
	str = line;
	while (*str)
	{
		len++;
		str++;
	}
	tmp = (char *)ft_calloc(len + 1, sizeof(char));
	head = tmp;
	while (*line != 32 && *line)
		*tmp++ = *line++;
	return (head);
}

int		prs_pth_third(t_mprms *mprms, char *line)
{
	if (*line == 'S' || mprms->full.sprt != 1)
	{
		line++;
		if (*line == 32)
		{
			mprms->paths.sprt = get_path(line);
			mprms->full.sprt = check_path(mprms->paths.sprt);
			if (mprms->full.sprt == -1)
				return (-1 + (mprms->check = 0));
		}
	}
	return (1);
}

int		prs_pth_second(t_mprms *mprms, char *line)
{
	if (*line == 'W')
	{
		if (*++line == 'E')
			if (*++line == 32 && mprms->full.we != 1)
			{
				mprms->paths.we = get_path(line);
				mprms->full.we = check_path(mprms->paths.we);
				if (mprms->full.we == -1)
					return (-1 + (mprms->check = 0));
			}
		return (1);
	}
	else if (*line == 'E')
	{
		if (*++line == 'A')
			if (*++line == 32 && mprms->full.ea != 1)
			{
				mprms->paths.ea = get_path(line);
				mprms->full.ea = check_path(mprms->paths.ea);
				if (mprms->full.ea == -1)
					return (-1 + (mprms->check = 0));
			}
		return (1);
	}
	return (prs_pth_third(mprms, line));
}

int		prs_pth(t_mprms *mprms, char *line)
{
	if (*line == 'N')
	{
		if (*++line == 'O')
			if (*++line == 32 && mprms->full.no != 1)
			{
				mprms->paths.no = get_path(line);
				mprms->full.no = check_path(mprms->paths.no);
				if (mprms->full.no == -1)
					return (-1 + (mprms->check = 0));
			}
		return (1);
	}
	else if (*line == 'S' && *(line + 1) == 'O')
	{
		if (*++line == 'O')
			if (*++line == 32 && mprms->full.so != 1)
			{
				mprms->paths.so = get_path(line);
				mprms->full.so = check_path(mprms->paths.so);
				if (mprms->full.so == -1)
					return (-1 + (mprms->check = 0));
			}
		return (1);
	}
	return (prs_pth_second(mprms, line));
}