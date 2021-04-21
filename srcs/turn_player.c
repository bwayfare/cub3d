# include "../include/cub3d.h"

void 	turn_player_2(t_mprms *mprms)
{
	if (mprms->plr.pl == 'S')
	{
		mprms->plr.dir_x = 1.0;
		mprms->plr.dir_y = 0.0;
		mprms->plr.pl_x = 0.00;
		mprms->plr.pl_y = -0.66;
	}
	if (mprms->plr.pl == 'W')
	{
		mprms->plr.dir_x = 0.0;
		mprms->plr.dir_y = -1.0;
		mprms->plr.pl_x = -0.66;
		mprms->plr.pl_y = 0.00;
	}
}

void 	turn_player(t_mprms *mprms)
{
	if (mprms->plr.pl == 'E')
	{
		mprms->plr.dir_x = 0.0;
		mprms->plr.dir_y = 1.0;
		mprms->plr.pl_x = 0.66;
		mprms->plr.pl_y = 0.00;
	}
	if (mprms->plr.pl == 'N')
	{
		mprms->plr.dir_x = -1.0;
		mprms->plr.dir_y = 0.0;
		mprms->plr.pl_x = 0.00;
		mprms->plr.pl_y = 0.66;
	}
	turn_player_2(mprms);
}