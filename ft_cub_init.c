#include "cub3d.h"

void	cub_init(t_mprms *mparams)
{
	mparams->colors.cell_color.r = -1;
	mparams->colors.cell_color.g = -1;
	mparams->colors.cell_color.b = -1;
	mparams->colors.floor_color.r = -1;
	mparams->colors.floor_color.g = -1;
	mparams->colors.floor_color.b = -1;
	mparams->res.x = 0;
	mparams->res.y = 0;
}