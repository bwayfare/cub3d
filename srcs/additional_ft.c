/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:13:52 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:10:37 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_trimm_sp(char **line)
{
	char	*str1;
	char	*str2;

	if (*line == NULL && **line == '\0')
		return ;
	str1 = *line;
	str2 = *line;
	while (*str1)
	{
		*str2 = *str1;
		if (*str1 == 32)
		{
			while (*(str1 + 1) == 32)
				str1++;
		}
		str1++;
		str2++;
	}
	*str2 = '\0';
}

int		ft_jmp_sp(char **line, char *str, char eof)
{
	int	flag;

	flag = 0;
	while ((*str >= '0' && *str <= '9') || *str == ' ' ||
	(*str == ',' && eof != '\0'))
	{
		if (*str >= '0' && *str <= '9' && eof != '\0')
		{
			*line = str;
			if (eof == ',' && flag != 1)
				return (-1);
			return (1);
		}
		if (*str == ',')
		{
			if (flag < 1 && eof == ',')
				flag = 1;
			else
				return (-1);
		}
		if (*str != ' ' && eof == '\0')
			return (-1);
		str++;
	}
	return (eof == '\0' && !(*str) ? 1 : -1);
}

int		ft_size_n(int n)
{
	int size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int		ft_res_check(char *str)
{
	char *line;

	line = str;
	while (*line)
	{
		if (*line != ' ')
			if (!(*line >= '0' && *line <= '9'))
				return (-1);
		line++;
	}
	return (1);
}
