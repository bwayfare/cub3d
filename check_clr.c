#include "cub3d.h"

int ft_check_clr(t_mprms *mprms)
{
	if (mprms->full.c_clr == 1 || mprms->colors.cell_color.r != -1)
	{
		if (mprms->colors.cell_color.r < 0 || mprms->colors.cell_color.r > 255)
			return (-1);
		if (mprms->colors.cell_color.g < 0 || mprms->colors.cell_color.g > 255)
			return (-1);
		if (mprms->colors.cell_color.b < 0 || mprms->colors.cell_color.b > 255)
			return (-1);
	}
	if (mprms->full.f_clr == 1 || mprms->colors.floor_color.r != -1)
	{
		if (mprms->colors.floor_color.r < 0 || mprms->colors.floor_color.r > 255)
			return (-1);
		if (mprms->colors.floor_color.g < 0 || mprms->colors.floor_color.g > 255)
			return (-1);
		if (mprms->colors.floor_color.b < 0 || mprms->colors.floor_color.b > 255)
			return (-1);
	}
	return (1);
}