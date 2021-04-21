#include "../include/cub3d.h"

void 	dist_sort(t_mprms *mprms)
{
	int i;

	i = 0;
	while (i < mprms->spr.count)
	{
		mprms->spr.spr[i].dist = ((mprms->plr.x - mprms->spr.spr[i].x) *
				(mprms->plr.x - mprms->spr.spr[i].x) + (mprms->plr.y -
				mprms->spr.spr[i].y) * (mprms->plr.y - mprms->spr.spr[i].y));
	i++;
	}
	sort_sprites(mprms->spr.spr, mprms->spr.count);
}

void 	draw_spr_param_init(t_mprms *mprms, int i)
{
	mprms->draw_spr.spriteX = mprms->spr.spr[i].x - mprms->plr.x + 0.5;
	mprms->draw_spr.spriteY = mprms->spr.spr[i].y - mprms->plr.y + 0.5;
	mprms->draw_spr.invDet = 1.0 / (mprms->plr.pl_x * mprms->plr.dir_y -
			mprms->plr.dir_x * mprms->plr.pl_y);
	mprms->draw_spr.transformX = mprms->draw_spr.invDet * (mprms->plr.dir_y *
			mprms->draw_spr.spriteX - mprms->plr.dir_x *
			mprms->draw_spr.spriteY);
	mprms->draw_spr.transformY = mprms->draw_spr.invDet * (-mprms->plr.pl_y *
			mprms->draw_spr.spriteX + mprms->plr.pl_x *
			mprms->draw_spr.spriteY);
	mprms->draw_spr.spriteScreenX = (int)((W / 2) * (1 +
			mprms->draw_spr.transformX / mprms->draw_spr.transformY));
	mprms->draw_spr.spriteHeight = abs((int)(H /
			(mprms->draw_spr.transformY)));
	mprms->draw_spr.drawStartY = -mprms->draw_spr.spriteHeight / 2 + H / 2;
	if (mprms->draw_spr.drawStartY < 0)
		mprms->draw_spr.drawStartY = 0;
	mprms->draw_spr.drawEndY = mprms->draw_spr.spriteHeight / 2 + H / 2;
	if (mprms->draw_spr.drawEndY >= H)
		mprms->draw_spr.drawEndY = H - 1;
}

void 	draw_spr_param_init_2(t_mprms *mprms)
{
	mprms->draw_spr.spriteWidth = abs((int)(H / (mprms->draw_spr.transformY)));
	mprms->draw_spr.drawStartX = -mprms->draw_spr.spriteWidth /
			2 + mprms->draw_spr.spriteScreenX;
	if (mprms->draw_spr.drawStartX < 0)
		mprms->draw_spr.drawStartX = 0;
	mprms->draw_spr.drawEndX = mprms->draw_spr.spriteWidth /
			2 + mprms->draw_spr.spriteScreenX;
	if (mprms->draw_spr.drawEndX >= W)
		mprms->draw_spr.drawEndX = W - 1;
}

void 	circle_drap_spr(t_mprms *mprms, int stripe)
{
	int y;
	mprms->draw_spr.texX = (int)(256 * (stripe -
			(-mprms->draw_spr.spriteWidth / 2 +
			mprms->draw_spr.spriteScreenX)) * texWidth /
					mprms->draw_spr.spriteWidth) / 256;
	y = mprms->draw_spr.drawStartY;
	if (mprms->draw_spr.transformY > 0 && stripe > 0 && stripe < W &&
		mprms->draw_spr.transformY < mprms->ray.ZBuffer[stripe])
		while (y < mprms->draw_spr.drawEndY)
		{
			mprms->draw_spr.d = (y) * 256 - H * 128 +
								mprms->draw_spr.spriteHeight * 128;
			mprms->draw_spr.texY = ((mprms->draw_spr.d * texHeight) /
					mprms->draw_spr.spriteHeight) / 256;
			mprms->draw_spr.color = ft_pixel_take(mprms->spr.obj,
										 mprms->draw_spr.texX,
										 mprms->draw_spr.texY);
			if ((int)(*mprms->draw_spr.color) != 0x000000)
				my_mlx_pixel_put(mprms, stripe, y,
					 (int)(*mprms->draw_spr.color));
			y++;
		}
}