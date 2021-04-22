/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:13:36 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:10:37 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		check_path(char *str)
{
	int		fd;
	char	*end;

	if (str == NULL)
		return (put_rtfm(EIP));
	end = str;
	while (*end)
		end++;
	if (*--end != 'm' || *--end != 'p' || *--end != 'x' ||
	*--end != '.' || !ft_isalnum(*--end))
		return (put_rtfm(EIP));
	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (put_rtfm(EIP));
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
	while (*line)
		*tmp++ = *line++;
	return (head);
}

int		prs_pth_third(t_mprms *mprms, char *line)
{
	if (*line == 'S' && *(line + 1) == ' ')
	{
		if (*line == 'S' && *++line == 32 && mprms->full.sprt != 1)
		{
			mprms->paths.sprt = get_path(line);
			mprms->full.sprt = check_path(mprms->paths.sprt);
			mprms->check = mprms->full.sprt;
		}
		else
			return (-1 + (mprms->check = put_rtfm(EIPARAM)));
		return (mprms->check);
	}
	return (-1);
}

int		prs_pth_second(t_mprms *mprms, char *st)
{
	if (*st == 'W' && *(st + 1) == 'E')
	{
		if (*st == 'W' && *++st == 'E' && *++st == 32 && mprms->full.we != 1)
		{
			mprms->paths.we = get_path(st);
			mprms->full.we = check_path(mprms->paths.we);
			mprms->check = mprms->full.we;
		}
		else
			return (-1 + (mprms->check = put_rtfm(EIPARAM)));
		return (1);
	}
	else if (*st == 'E' && *(st + 1) == 'A')
	{
		if (*st == 'E' && *++st == 'A' && *++st == 32 && mprms->full.ea != 1)
		{
			mprms->paths.ea = get_path(st);
			mprms->full.ea = check_path(mprms->paths.ea);
			mprms->check = mprms->full.ea;
		}
		else
			return (-1 + (mprms->check = put_rtfm(EIPARAM)));
		return (1);
	}
	return (prs_pth_third(mprms, st));
}

int		prs_pth(t_mprms *mprms, char *st)
{
	if (*st == 'N' && *(st + 1) == 'O')
	{
		if (*st == 'N' && *++st == 'O' && *++st == 32 && mprms->full.no != 1)
		{
			mprms->paths.no = get_path(st);
			mprms->full.no = check_path(mprms->paths.no);
			mprms->check = mprms->full.no;
		}
		else
			return (-1 + (mprms->check = put_rtfm(EIPARAM)));
		return (1);
	}
	else if (*st == 'S' && *(st + 1) == 'O')
	{
		if (*st == 'S' && *++st == 'O' && *++st == 32 && mprms->full.so != 1)
		{
			mprms->paths.so = get_path(st);
			mprms->full.so = check_path(mprms->paths.so);
			mprms->check = mprms->full.so;
		}
		else
			return (-1 + (mprms->check = put_rtfm(EIPARAM)));
		return (mprms->check);
	}
	return (prs_pth_second(mprms, st));
}
