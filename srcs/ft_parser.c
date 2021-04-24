/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:14:16 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/22 08:10:37 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	prs_res(t_mprms *mprms, char *line)
{
	line++;
	if (*line != 32 || mprms->full.res == 1)
		return (-1 + (mprms->check = put_rtfm(EIR)));
	if (ft_res_check(line) == -1)
		return (-1 + (mprms->check = put_rtfm(EIR)));
	if (ft_jmp_sp(&line, line, '0') != -1)
		mprms->res.x = ft_atoi(&line);
	else
		return (-1 + (mprms->check = put_rtfm(EIR)));
	if (ft_jmp_sp(&line, line, '0') != -1)
		mprms->res.y = ft_atoi(&line);
	else
		return (-1 + (mprms->check = put_rtfm(EIR)));
	if (ft_jmp_sp(&line, line, '\0') == -1 || mprms->res.x < 1 ||
		mprms->res.y < 1)
		return (-1 + (mprms->check = put_rtfm(EIR)));
	mprms->full.res = 1;
	return (1);
}

int	prs_clr1(t_mprms *mprms, char *line)
{
	line++;
	if (*line != 32 || mprms->full.c_clr == 1)
		return (-1 + (mprms->check = put_rtfm(EICC)));
	if (ft_jmp_sp(&line, line, '0') != -1)
		mprms->colors.ceil.r = ft_atoi(&line);
	else
		return (-1 + (mprms->check = put_rtfm(EICC)));
	if (ft_jmp_sp(&line, line, ',') != -1)
		mprms->colors.ceil.g = ft_atoi(&line);
	else
		return (-1 + (mprms->check = put_rtfm(EICC)));
	if (ft_jmp_sp(&line, line, ',') != -1)
		mprms->colors.ceil.b = ft_atoi(&line);
	else
		return (-1 + (mprms->check = put_rtfm(EICC)));
	if (ft_jmp_sp(&line, line, '\0') == -1)
		return (-1 + (mprms->check = put_rtfm(EICC)));
	mprms->full.c_clr = 1;
	return (1);
}

int	prs_clr(t_mprms *mprms, char *line)
{
	if (*line == 'F')
	{
		if (*++line != 32 || mprms->full.f_clr == 1)
			return (-1 + (mprms->check = put_rtfm(EIFC)));
		if (ft_jmp_sp(&line, line, '0') != -1)
			mprms->colors.floor.r = ft_atoi(&line);
		else
			return (-1 + (mprms->check = put_rtfm(EIFC)));
		if (ft_jmp_sp(&line, line, ',') != -1)
			mprms->colors.floor.g = ft_atoi(&line);
		else
			return (-1 + (mprms->check = put_rtfm(EIFC)));
		if (ft_jmp_sp(&line, line, ',') != -1)
			mprms->colors.floor.b = ft_atoi(&line);
		else
			return (-1 + (mprms->check = put_rtfm(EIFC)));
		if (ft_jmp_sp(&line, line, '\0') == -1)
			return (-1 + (mprms->check = put_rtfm(EIFC)));
		mprms->full.f_clr = 1;
		return (ft_check_clr(mprms, EIFC));
	}
	if (*line == 'C')
		prs_clr1(mprms, line);
	return (ft_check_clr(mprms, EICC));
}

int	parse_line(t_mprms *mprms, char *line)
{
	ft_trimm_sp(&line);
	if (ft_strlen(line) == 1)
		return (-1 + (mprms->check = put_rtfm("Error\nInvalid param\n")));
	while (line && *line)
	{
		if (!(*line == 'R' || *line == 'F' || *line == 'C' || *line == 'N' ||
		*line == 'W' || *line == 'E' || *line == 'S'))
			return (-1 + (mprms->check = put_rtfm("Error\nInvalid param\n")));
		else if (*line == 'R')
			return (prs_res(mprms, line));
		else if (*line == 'F' || *line == 'C')
			return (prs_clr(mprms, line));
		else if (*line == 'N' || *line == 'W' || *line == 'E')
			return (prs_pth(mprms, line));
		else if (*line == 'S')
		{
			if (*(line + 1) == 'O' || *(line + 1) == 32)
				return (prs_pth(mprms, line));
			else
				return (-1 + (mprms->check = 0));
		}
		else
			return (-1 + (mprms->check = 0));
	}
	return (0);
}
