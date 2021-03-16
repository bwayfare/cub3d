#include "cub3d.h"

void struct_init(t_mprms *mprms)
{
	mprms->colors.floor_color.r = -1;
	mprms->colors.floor_color.g = -1;
	mprms->colors.floor_color.b = -1;
	mprms->colors.cell_color.r = -1;
	mprms->colors.cell_color.g = -1;
	mprms->colors.cell_color.b = -1;
	mprms->full.f_clr = 0;
	mprms->full.c_clr = 0;
	mprms->full.sprt = 0;
	mprms->full.we = 0;
	mprms->full.ea = 0;
	mprms->full.no = 0;
	mprms->full.so = 0;
	mprms->full.res = 0;
	mprms->res.x = 0;
	mprms->res.y = 0;
	mprms->paths.so = NULL;
	mprms->paths.no = NULL;
	mprms->paths.ea = NULL;
	mprms->paths.we = NULL;
	mprms->paths.sprt = NULL;
}

void clean_struct(t_mprms *mprms)
{
	if (mprms->paths.sprt != NULL)
		free(mprms->paths.sprt);
	if (mprms->paths.we != NULL)
		free(mprms->paths.we);
	if (mprms->paths.ea != NULL)
		free(mprms->paths.ea);
	if (mprms->paths.no != NULL)
		free(mprms->paths.no);
	if (mprms->paths.so != NULL)
		free(mprms->paths.so);
}