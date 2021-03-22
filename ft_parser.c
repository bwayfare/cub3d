#include "cub3d.h"

int 	prs_res(t_mprms *mprms, char *line)
{
	line++;
	if (*line != 32 || mprms->full.res == 1)
		return (-1 + (mprms->check = 0));
	if (ft_res_check(line) == -1)
		return (-1 + (mprms->check = 0));
	if (ft_jmp_sp(&line, line, '0') != -1)
		mprms->res.x = ft_atoi(&line);
	else
		return (-1 + (mprms->check = 0));
	if (ft_jmp_sp(&line, line, '0') != -1)
		mprms->res.y = ft_atoi(&line);
	else
		return (-1 + (mprms->check = 0));
	if (ft_jmp_sp(&line, line, '\0') == -1 || mprms->res.x < 1 ||
	mprms->res.y < 1)
	    return (-1 + (mprms->check = 0));
	mprms->full.res = 1;
	return (1);
}

int		prs_clr1(t_mprms *mprms, char *line)
{
	line++;
	if (*line != 32 || mprms->full.c_clr == 1)
		return (-1 + (mprms->check = 0));
	if (ft_jmp_sp(&line, line, '0') != -1)
		mprms->colors.cell_color.r = ft_atoi(&line);
	else
		return (-1 + (mprms->check = 0));
	if (ft_jmp_sp(&line, line, ',') != -1)
		mprms->colors.cell_color.g = ft_atoi(&line);
	else
		return (-1 + (mprms->check = 0));
	if (ft_jmp_sp(&line, line, ',') != -1)
		mprms->colors.cell_color.b = ft_atoi(&line);
	else
		return (-1 + (mprms->check = 0));
	if (ft_jmp_sp(&line, line, '\0') == -1)
		return (-1 + (mprms->check = 0));
	if (ft_check_clr(mprms) != -1)
		mprms->full.c_clr = 1;
	return (1);
}

int		prs_clr(t_mprms *mprms, char *line)
{
	if (*line == 'F')
	{
		if (*++line != 32|| mprms->full.f_clr == 1)
			return (-1 + (mprms->check = 0));
		if (ft_jmp_sp(&line, line, '0') != -1)
			mprms->colors.floor_color.r = ft_atoi(&line);
		else
			return (-1 + (mprms->check = 0));
		if (ft_jmp_sp(&line, line, ',') != -1)
			mprms->colors.floor_color.g = ft_atoi(&line);
		else
			return (-1 + (mprms->check = 0));
		if (ft_jmp_sp(&line, line, ',') != -1)
			mprms->colors.floor_color.b = ft_atoi(&line);
		else
			return (-1 + (mprms->check = 0));
		if (ft_jmp_sp(&line, line, '\0') == -1)
			return (-1 + (mprms->check = 0));
		if (ft_check_clr(mprms) != -1)
			mprms->full.f_clr = 1;
		return (ft_check_clr(mprms));
	}
	else
		if (prs_clr1(mprms, line) != -1)
			return (ft_check_clr(mprms));
	return (-1 + (mprms->check = 0));
}


int    parse_line(t_mprms *mprms, char *line)
{
	ft_trimm_sp(&line);
	if (ft_strlen(line) == 1)
		return (-1 + (mprms->check = 0));
	while (line && *line)
	{
		if (*line == 32)
			line++;
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