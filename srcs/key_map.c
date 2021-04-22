#include "../include/cub3d.h"

int 		key_press(int key, t_mprms *mprms)
{
	if (key == 13)//119)
		mprms->pres.up = 1;
	if (key == 1)//115)
		mprms->pres.down = 1;
	if (key == 2)//100)
		mprms->pres.right = 1;
	if (key == 0)//97)
		mprms->pres.left = 1;
	if (key == 14)//101)
		mprms->pres.turnright = 1;
	if (key == 12)//113)
		mprms->pres.turnleft = 1;
	if (key == 53)//65307)
		exit(0);
	return (0);
}

int 		key_release(int key, t_mprms * mprms)
{
	if (key == 13)//119)
		mprms->pres.up = 0;
	if (key == 1)//115)
		mprms->pres.down = 0;
	if (key == 2)//100)
		mprms->pres.right = 0;
	if (key == 0)//97)
		mprms->pres.left = 0;
	if (key == 14)//101)
		mprms->pres.turnright = 0;
	if (key == 12)//113)
		mprms->pres.turnleft = 0;
	return (0);
}