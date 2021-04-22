#include "../include/cub3d.h"

void move_left(t_mprms *mprms, double speed)
{
	if (mprms->pres.turnleft)
	{
		if (mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_y * 0.1)]
			[(int)(mprms->plr.y)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x -	mprms->plr.dir_y * 0.1)]
			[(int)(mprms->plr.y)] != '2')
			mprms->plr.x -= mprms->plr.dir_y * speed;
		if (mprms->map.map[(int)(mprms->plr.x)]
			[(int)(mprms->plr.y + mprms->plr.dir_x * 0.1)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x)]
			[(int)(mprms->plr.y + mprms->plr.dir_x * 0.1)] != '2')
			mprms->plr.y += mprms->plr.dir_x * speed;
	}
}

void move_right(t_mprms *mprms, double speed)
{
	if (mprms->pres.turnright)
	{
		if (mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_y * 0.1)]
			[(int)(mprms->plr.y)] != '1' &&
			mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_y * 0.1)]
			[(int)(mprms->plr.y)] != '2')
			mprms->plr.x += mprms->plr.dir_y * speed;
		if (mprms->map.map[(int)(mprms->plr.x)][(int) (mprms->plr.y -
			mprms->plr.dir_x * 0.1)] != '1' && mprms->map.map[(int)(mprms->plr.x)]
			[(int) (mprms->plr.y - mprms->plr.dir_x * 0.1)] != '2')
			mprms->plr.y -= mprms->plr.dir_x * speed;
	}
}