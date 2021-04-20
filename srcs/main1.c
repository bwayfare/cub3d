#include "../include/cub3d.h"

int		draw(t_mprms *mprms);

void print(t_mprms *mprms)
{
	printf("R = %d %d\n", mprms->res.x, mprms->res.y);
	printf("C = %d %d %d\n", mprms->colors.ceil.r, mprms->colors.ceil.g, mprms->colors.ceil.b);
	printf("F = %d %d %d\n", mprms->colors.floor.r, mprms->colors.floor.g, mprms->colors.floor.b);
	printf("S = %s\n", mprms->paths.sprt);
	printf("SO = %s\n", mprms->paths.so);
	printf("NO = %s\n", mprms->paths.no);
	printf("EA = %s\n", mprms->paths.ea);
	printf("WE = %s\n", mprms->paths.we);
	printf("check = %d %d %d %d %d %d %d %d = %d\n", mprms->full.res, mprms->full.c_clr, mprms->full.f_clr,
		   mprms->full.sprt, mprms->full.so, mprms->full.no, mprms->full.ea, mprms->full.we, mprms->check);
	for(int i = 0; mprms->map.map && mprms->map.map[i]; i++)
		printf("%s\n", mprms->map.map[i]);
	printf("size map = %d %d\n", mprms->map.len, mprms->map.size);
	printf("player position x = %f y = %f\n", mprms->plr.x, mprms->plr.y);
}

int		create_trgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}


void f_get_map(char **line, t_list **list, int *fd, t_mprms *mprms)
{
	int res;

	res = 0;
	while (get_next_line(*fd, line) > 0)
		if (ft_search_map(*line, mprms, *list, &res) > -1
			&& (res == 1 || res == 3))
			ft_lstadd_back(list, ft_lstnew(*line));
		else
			free_line(line);
	if (ft_search_map(*line, mprms, *list, &res) == 0)
		ft_lstadd_back(list, ft_lstnew(*line));
	else
		free_line(line);
	if (mprms->check)
	{
		map_creator(*list, mprms);
		if (ft_ch_elem_map(mprms))
			ch_wall(mprms, mprms->map.map);
	}
}

int ft_creat_mprms(int *fd, char *argv, t_mprms *mprms, t_list **list)
{
	char		*line;

	struct_init(mprms);
	if (!(*fd = open(argv, O_RDONLY)))
		return (0);
	while (mprms->check && ft_check_full(mprms) != 8 &&
		   get_next_line(*fd, &line) > 0 && (parse_line(mprms, line) != -1))
		free_line(&line);
	if (line)
		free_line(&line);
	if (mprms->check)
		f_get_map(&line, list, fd, mprms);
	print(mprms);
	return (1);
}

void            my_mlx_pixel_put(t_mprms *mprms, int x, int y, int color)
{
	char    *dst;

	dst = mprms->data.addr + (y * mprms->data.line_length + x * (mprms->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int 		key_press(int key, t_mprms *mprms)
{
//		printf("key = %d \n", key);
//100
//97
	if (key == /*13)*/119)
		mprms->pres.up = 1;
	if (key == /*1)*/115)
		mprms->pres.down = 1;
	if (key == /*2)*/100)
		mprms->pres.right = 1;
	if (key == /*0)*/97)
		mprms->pres.left = 1;
	if (key == /*14)*/101)
		mprms->pres.turnright = 1;
	if (key == /*12)*/113)
		mprms->pres.turnleft = 1;
	if (key == /*53)*/65307)
		exit(0);
//	write(1, "press\n", 6);
	return (0);
}

/*
key = 12
key = 13
key = 14
key = 0
key = 1
key = 2

 */

int 		key_release(int key, t_mprms * mprms)
{
	if (key == /*13)*/119)
		mprms->pres.up = 0;
	if (key == /*1)*/115)
		mprms->pres.down = 0;
	if (key == /*2)*/100)
		mprms->pres.right = 0;
	if (key == /*0)*/97)
		mprms->pres.left = 0;
	if (key == /*14)*/101)
		mprms->pres.turnright = 0;
	if (key == /*12)*/113)
		mprms->pres.turnleft = 0;
//	write(1, "releas\n", 7);
	return (0);
}

void 		draw_floor_ceil(t_mprms *mprms)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < mprms->res.y / 2)
	{
		while (x < mprms->res.x)
			my_mlx_pixel_put(mprms, x++, y, mprms->colors.ceil.trns);
		y++;
		x = 0;
	}
	while (y < mprms->res.y)
	{
		while (x < mprms->res.x)
			my_mlx_pixel_put(mprms, x++, y, mprms->colors.floor.trns);
		y++;
		x = 0;
	}
}

int 		move_plr(t_mprms *mprms)
{
	double speed;

	speed = 0.05;
//		write(1, "test\n", 5);
//	printf("key = %d \n", key);
	if(mprms->pres.up)
	{
		if(mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_x * speed)][(int)(mprms->plr.y)] != '1' &&
				mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_x * speed)][(int)(mprms->plr.y)] != '2')
			mprms->plr.x += mprms->plr.dir_x * speed;
		if(mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y + mprms->plr.dir_y * speed)] != '1' &&
				mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y + mprms->plr.dir_y * speed)] != '2')
			mprms->plr.y += mprms->plr.dir_y * speed;
//		write(1, "test\n", 5);
	}
	//move backwards if no wall behind you
	if(mprms->pres.down)
	{
		if(mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_x * speed)][(int)(mprms->plr.y)] != '1' &&
				mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_x * speed)][(int)(mprms->plr.y)] != '2')
			mprms->plr.x -= mprms->plr.dir_x * speed;
		if(mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y - mprms->plr.dir_y * speed)] != '1' &&
				mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y - mprms->plr.dir_y * speed)] != '2')
			mprms->plr.y -= mprms->plr.dir_y * speed;
//		write(1, "test2\n", 6);
	}
	if (mprms->pres.right)
	{
		//both camera direction and camera plane must be rotated
		mprms->ray.oldDirX = mprms->plr.dir_x;
		mprms->plr.dir_x = mprms->plr.dir_x * cos(-speed) - mprms->plr.dir_y * sin(-speed);
		mprms->plr.dir_y = mprms->ray.oldDirX * sin(-speed) + mprms->plr.dir_y * cos(-speed);
		mprms->ray.oldPlaneX = mprms->plr.pl_x;
		mprms->plr.pl_x = mprms->plr.pl_x * cos(-speed) - mprms->plr.pl_y * sin(-speed);
		mprms->plr.pl_y = mprms->ray.oldPlaneX * sin(-speed) + mprms->plr.pl_y * cos(-speed);
	}
	//rotate to the left
	if (mprms->pres.left)
	{
		//both camera direction and camera plane must be rotated
		mprms->ray.oldDirX = mprms->plr.dir_x;
		mprms->plr.dir_x = mprms->plr.dir_x * cos(speed) - mprms->plr.dir_y * sin(speed);
		mprms->plr.dir_y = mprms->ray.oldDirX * sin(speed) + mprms->plr.dir_y * cos(speed);
		mprms->ray.oldPlaneX = mprms->plr.pl_x;
		mprms->plr.pl_x = mprms->plr.pl_x * cos(speed) - mprms->plr.pl_y * sin(speed);
		mprms->plr.pl_y = mprms->ray.oldPlaneX * sin(speed) + mprms->plr.pl_y * cos(speed);
	}

	if (mprms->pres.turnleft)
	{
		if (mprms->map.map[(int) (mprms->plr.x - mprms->plr.dir_y * 0.1)]
			[(int) (mprms->plr.y)] != '1' && mprms->map.map[(int) (mprms->plr.x - mprms->plr.dir_y * 0.1)]
			[(int) (mprms->plr.y)] != '2')
		{
			mprms->plr.x -= mprms->plr.dir_y * 0.05;
		}
		if (mprms->map.map[(int) (mprms->plr.x)]
			[(int) (mprms->plr.y + mprms->plr.dir_x * 0.1)] != '1' && mprms->map.map[(int) (mprms->plr.x)]
			[(int) (mprms->plr.y + mprms->plr.dir_x * 0.1)] != '2')
		{
			mprms->plr.y += mprms->plr.dir_x * 0.05;
		}
	}
	if (mprms->pres.turnright)
	{
		if (mprms->map.map[(int) (mprms->plr.x + mprms->plr.dir_y * 0.1)]
			[(int) (mprms->plr.y)] != '1' && mprms->map.map[(int) (mprms->plr.x + mprms->plr.dir_y * 0.1)]
			[(int) (mprms->plr.y)] != '2')
		{
			mprms->plr.x += mprms->plr.dir_y * 0.05;
		}
		if (mprms->map.map[(int) (mprms->plr.x)]
			[(int) (mprms->plr.y - mprms->plr.dir_x * 0.1)] != '1' && mprms->map.map[(int) (mprms->plr.x)]
			[(int) (mprms->plr.y - mprms->plr.dir_x * 0.1)] != '2')
		{
			mprms->plr.y -= mprms->plr.dir_x * 0.05;
		}
	}

//	mprms->ray.color += 1;
	draw_floor_ceil(mprms);
	if (!mprms->pres.esc)
		draw(mprms);
	return (1);
}

void sort_sprites(t_spr *spr, int count)
{
	t_spr tmp;
	int i;
	int j;

	i = 0;
	while (i < count - 1)
	{
		j = i;
		while (j < count)
		{
			if (spr[i].dist < spr[j].dist)
			{
				tmp = spr[i];
				spr[i] = spr[j];
				spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int		draw(t_mprms *mprms)
{
	int x = -1;
	while (++x < W)
	{
		mprms->ray.cameraX = 2 * x / (double)W - 1; //x-coordinate in camera space
		mprms->ray.rayDirX = mprms->plr.dir_x + mprms->plr.pl_x * mprms->ray.cameraX;
		mprms->ray.rayDirY = mprms->plr.dir_y + mprms->plr.pl_y * mprms->ray.cameraX;

		//which box of the map we're in
		mprms->ray.mapX = (int)mprms->plr.x;
		mprms->ray.mapY = (int)mprms->plr.y;

		//length of ray from one x or y-side to next x or y-side
//		mprms->ray.deltaDistX = fabs(1 / mprms->ray.rayDirX);
//		mprms->ray.deltaDistY = fabs(1 / mprms->ray.rayDirY);

		mprms->ray.deltaDistX = (mprms->ray.rayDirY == 0) ? 0 : ((mprms->ray.rayDirX == 0) ? 1 : fabs(1 / mprms->ray.rayDirX));
		mprms->ray.deltaDistY = (mprms->ray.rayDirX == 0) ? 0 : ((mprms->ray.rayDirY == 0) ? 1 : fabs(1 / mprms->ray.rayDirY));

		mprms->ray.hit = 0; //was there a wall hit?
		mprms->ray.sideDistX = 0;
		if(mprms->ray.rayDirX < 0)
		{
			mprms->ray.stepX = -1;
			mprms->ray.sideDistX = (mprms->plr.x - mprms->ray.mapX) * mprms->ray.deltaDistX;
		}
		else
		{
			mprms->ray.stepX = 1;
			mprms->ray.sideDistX = (mprms->ray.mapX + 1.0 - mprms->plr.x) * mprms->ray.deltaDistX;
		}
		if(mprms->ray.rayDirY < 0)
		{
			mprms->ray.stepY = -1;
			mprms->ray.sideDistY = (mprms->plr.y - mprms->ray.mapY) * mprms->ray.deltaDistY;
		}
		else
		{
			mprms->ray.stepY = 1;
			mprms->ray.sideDistY = (mprms->ray.mapY + 1.0 - mprms->plr.y) * mprms->ray.deltaDistY;
		}
		while (mprms->ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (mprms->ray.sideDistX < mprms->ray.sideDistY)
			{
				mprms->ray.sideDistX += mprms->ray.deltaDistX;
				mprms->ray.mapX += mprms->ray.stepX;
				mprms->ray.side = 0;
			}
			else
			{
				mprms->ray.sideDistY += mprms->ray.deltaDistY;
				mprms->ray.mapY += mprms->ray.stepY;
				mprms->ray.side = 1;
			}
			//Check if ray has hit a wall
//			write(1, "tes1\n", 5);
//			printf("x = %d y = %d\n\n", mprms->ray.mapY, mprms->ray.mapX);
//			printf("%c", WWORLDMAP[mprms->ray.mapY][mprms->ray.mapX]);
			if (WWORLDMAP[mprms->ray.mapX][mprms->ray.mapY] == '1')
				mprms->ray.hit = 1;
//			write(1, "tes2\n", 5);
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
//		write(1, "test\n", 5);
		if (mprms->ray.side == 0)
		{
			mprms->ray.perpWallDist = (mprms->ray.mapX - mprms->plr.x + (1.0 - mprms->ray.stepX) / 2) / mprms->ray.rayDirX;
//			printf("mapX - %d, posX - %f, dirX - %f, perpWallDist - %f\n", mprms->ray.mapX, mprms->character.posX, mprms->ray.rayDirX, mprms->ray.perpWallDist);
		}
		else
		{
			mprms->ray.perpWallDist = (mprms->ray.mapY - mprms->plr.y + (1.0 - mprms->ray.stepY) / 2) / mprms->ray.rayDirY;
//			printf("mapY - %d, posY - %f, dirY - %f, perpWallDist - %f\n", mprms->ray.mapY, mprms->character.posY, mprms->ray.rayDirY, mprms->ray.perpWallDist);
		}
		//Calculate height of line to draw on screen
		mprms->ray.lineHeight = (int)(H / mprms->ray.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		mprms->ray.drawStart = -mprms->ray.lineHeight / 2 + H / 2;
		if(mprms->ray.drawStart < 0) mprms->ray.drawStart = 0;
		mprms->ray.drawEnd = mprms->ray.lineHeight / 2 + H / 2;
		if(mprms->ray.drawEnd >= H) mprms->ray.drawEnd = H - 1;

		//texturing calculations
		mprms->ray.texNum = WWORLDMAP[mprms->ray.mapX][mprms->ray.mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
//		mprms->ray.wallX; //where exactly the wall was hit
//		if(mprms->ray.side == 0) mprms->ray.wallX = mprms->plr.y + mprms->ray.perpWallDist * mprms->ray.rayDirY;
//		else mprms->ray.wallX = mprms->plr.x + mprms->ray.perpWallDist * mprms->ray.rayDirX;
//		mprms->ray.wallX -= floor((mprms->ray.wallX));

		if(mprms->ray.side == 0) mprms->ray.wallX = mprms->plr.y + mprms->ray.perpWallDist * mprms->ray.rayDirY;
		else          mprms->ray.wallX = mprms->plr.x + mprms->ray.perpWallDist * mprms->ray.rayDirX;
		mprms->ray.wallX -= floor((mprms->ray.wallX));

		//x coordinate on the texture
		mprms->ray.texX = (int)(mprms->ray.wallX * (double)texWidth);
		if(mprms->ray.side == 0 && mprms->ray.rayDirX > 0) mprms->ray.texX = texWidth - mprms->ray.texX - 1;
		if(mprms->ray.side == 1 && mprms->ray.rayDirY < 0) mprms->ray.texX = texWidth - mprms->ray.texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		mprms->ray.step = 1.0 * texHeight / mprms->ray.lineHeight;
		// Starting texture coordinate
		mprms->ray.texPos = (mprms->ray.drawStart - H / 2.0 + mprms->ray.lineHeight / 2.0) * mprms->ray.step;
//		printf("x - %d\n", x);
//		printf("drawStart - %d\n", mprms->ray.drawStart);
//		printf("drawEnd - %d\n", mprms->ray.drawEnd);
		for(int y = mprms->ray.drawStart; y < mprms->ray.drawEnd; y++)
		{
			t_tex tex;
			if (mprms->ray.side == 0 && mprms->ray.stepX > 0)
				tex = mprms->tex.east;
			else if (mprms->ray.side == 0 && mprms->ray.stepX < 0)
				tex = mprms->tex.west;
			else if (mprms->ray.side == 1 && mprms->ray.stepY > 0)
				tex = mprms->tex.south;
			else //if (mprms->ray.side == 0 && mprms->ray.stepY < 0)
				tex = mprms->tex.north;
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			mprms->ray.texY = (int)mprms->ray.texPos & (texHeight - 1);
			mprms->ray.texPos += mprms->ray.step;
//			if(mprms->ray.side == 1) mprms->ray.color = 0xff00ff; // (mprms->ray.color >> 1) & 8355711;
//			printf("x - %d, y - %d\n", x, y);
			mprms->ray.color = ft_pixel_take(tex, mprms->ray.texX, mprms->ray.texY);
			my_mlx_pixel_put(mprms, x, y, (int)(*mprms->ray.color)); // mprms->ray.color);
		}
		mprms->ray.ZBuffer[x] = mprms->ray.perpWallDist;
	}
//	printf("spr count = %d\n", mprms->spr.count);
	if (mprms->spr.count)
		draw_spr(mprms);
//	printf("spr count = %d\n", mprms->spr.count);
	mlx_put_image_to_window(mprms->data.mlx, mprms->data.win, mprms->data.img, 0, 0);
	mlx_destroy_image(mprms->data.mlx, mprms->data.img);
	mprms->data.addr = NULL;
	mprms->data.img = NULL;
	mprms->data.img = mlx_new_image(mprms->data.mlx, (int)W, (int)H);
	mprms->data.addr = mlx_get_data_addr(mprms->data.img, &mprms->data.bits_per_pixel, &mprms->data.line_length, &mprms->data.endian);
	return (0);
}

void 	draw_spr(t_mprms *mprms)
{
	for(int i = 0; i < mprms->spr.count; i++)
	{
		mprms->spr.spr[i].dist = ((mprms->plr.x - mprms->spr.spr[i].x) * (mprms->plr.x - mprms->spr.spr[i].x) +
								 (mprms->plr.y - mprms->spr.spr[i].y) * (mprms->plr.y - mprms->spr.spr[i].y)); //sqrt not taken, unneeded
	}
	sort_sprites(mprms->spr.spr, mprms->spr.count);
	for (int i = 0; i < mprms->spr.count; i++)
	{
		//translate sprite position to relative to camera
		mprms->draw_spr.spriteX = mprms->spr.spr[i].x - mprms->plr.x + 0.5;
		mprms->draw_spr.spriteY = mprms->spr.spr[i].y - mprms->plr.y + 0.5;

		mprms->draw_spr.invDet = 1.0 / (mprms->plr.pl_x * mprms->plr.dir_y - mprms->plr.dir_x *
																			 mprms->plr.pl_y); //required for correct matrix multiplication

		mprms->draw_spr.transformX = mprms->draw_spr.invDet * (mprms->plr.dir_y * mprms->draw_spr.spriteX -
															   mprms->plr.dir_x * mprms->draw_spr.spriteY);
		mprms->draw_spr.transformY = mprms->draw_spr.invDet * (-mprms->plr.pl_y * mprms->draw_spr.spriteX +
															   mprms->plr.pl_x *
															   mprms->draw_spr.spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		mprms->draw_spr.spriteScreenX = (int) ((W / 2) * (1 + mprms->draw_spr.transformX / mprms->draw_spr.transformY));

		//calculate height of the sprite on screen
		mprms->draw_spr.spriteHeight = abs((int) (H / (mprms->draw_spr.transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		mprms->draw_spr.drawStartY = -mprms->draw_spr.spriteHeight / 2 + H / 2;
		if (mprms->draw_spr.drawStartY < 0)
			mprms->draw_spr.drawStartY = 0;
		mprms->draw_spr.drawEndY = mprms->draw_spr.spriteHeight / 2 + H / 2;
		if (mprms->draw_spr.drawEndY >= H)
			mprms->draw_spr.drawEndY = H - 1;

		//calculate width of the sprite
		mprms->draw_spr.spriteWidth = abs((int) (H / (mprms->draw_spr.transformY)));
		mprms->draw_spr.drawStartX = -mprms->draw_spr.spriteWidth / 2 + mprms->draw_spr.spriteScreenX;
		if (mprms->draw_spr.drawStartX < 0)
			mprms->draw_spr.drawStartX = 0;
		mprms->draw_spr.drawEndX = mprms->draw_spr.spriteWidth / 2 + mprms->draw_spr.spriteScreenX;
		if (mprms->draw_spr.drawEndX >= W)
			mprms->draw_spr.drawEndX = W - 1;

		//loop through every vertical stripe of the sprite on screen
//		printf("mprms->draw_spr.drawStartX = %d\n mprms->draw_spr.drawEndX = %d\n W = %d H = %d\n",
//		 mprms->draw_spr.drawStartX,mprms->draw_spr.drawEndX, W, H);
//			getchar();
		for (int stripe = mprms->draw_spr.drawStartX; stripe < mprms->draw_spr.drawEndX; stripe++)
		{
			mprms->draw_spr.texX =
					(int) (256 * (stripe - (-mprms->draw_spr.spriteWidth / 2 + mprms->draw_spr.spriteScreenX)) *
						   texWidth / mprms->draw_spr.spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (mprms->draw_spr.transformY > 0 && stripe > 0 && stripe < W &&
				mprms->draw_spr.transformY < mprms->ray.ZBuffer[stripe])
				for (int y = mprms->draw_spr.drawStartY;
					 y < mprms->draw_spr.drawEndY; y++) //for every pixel of the current stripe
				{
//					write(1, "1", 1);
					mprms->draw_spr.d = (y) * 256 - H * 128 +
										mprms->draw_spr.spriteHeight * 128; //256 and 128 factors to avoid floats
//					write(1, "2", 1);
					mprms->draw_spr.texY = ((mprms->draw_spr.d * texHeight) / mprms->draw_spr.spriteHeight) / 256;
//					write(1, "3", 1);
					mprms->draw_spr.color = ft_pixel_take(mprms->spr.obj, mprms->draw_spr.texX,
														  mprms->draw_spr.texY);//get current color from the texture
//					write(1, "4", 1);
					if ((int)(*mprms->draw_spr.color) != 0x000000)
						my_mlx_pixel_put(mprms, stripe, y, (int)(*mprms->draw_spr.color));
//					write(1, "5", 1);
//					if((mprms->draw_spr.color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
	}
}

//void	ft_init_sprite(t_mprms *mprms)
//{
//	t_spr_info	sprite;
//
//	sprite.s_img.img = mlx_xpm_file_to_image(mprms->win.mlx, \
//		mprms->info.spr_path, &(sprite.width), &(sprite.height));
//	sprite.s_img.addr = mlx_get_data_addr(sprite.s_img.img, \
//		&(sprite.s_img.bpp), &(sprite.s_img.line_l), &(sprite.s_img.end));
//	mprms->sprite = sprite;
//}

void	ft_convert_file_to_image(t_mprms *mprms)
{
	mprms->tex.north.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.no, &(mprms->tex.north.width), \
		&(mprms->tex.north.height));
	if (mprms->tex.north.w_img.img == NULL || mprms->tex.north.height != 64
		|| mprms->tex.north.width != 64)
		put_rtfm("Error\nTexture crahed\n");
	mprms->tex.south.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.so, &(mprms->tex.south.width), \
		&(mprms->tex.south.height));
	if (mprms->tex.south.w_img.img == NULL || mprms->tex.south.height != 64
		|| mprms->tex.south.width != 64)
		put_rtfm("Error\nTexture crahed\n");
	mprms->tex.west.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.we, &(mprms->tex.west.width), \
		&(mprms->tex.west.height));
	if (mprms->tex.west.w_img.img == NULL || mprms->tex.west.height != 64
		|| mprms->tex.west.width != 64)
		put_rtfm("Error\nTexture crahed\n");
	mprms->tex.east.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.ea, &(mprms->tex.east.width), \
		&(mprms->tex.east.height));
	if (mprms->tex.east.w_img.img == NULL || mprms->tex.east.height != 64
		|| mprms->tex.east.width != 64)
		put_rtfm("Error\nTexture crahed\n");
	mprms->spr.obj.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx,
		mprms->paths.sprt, &(mprms->spr.obj.width), &(mprms->spr.obj.height));
	if (mprms->spr.obj.w_img.img == NULL || mprms->spr.obj.width != 64
		|| mprms->spr.obj.height != 64)
		put_rtfm("Error\nTexture crahed\n");
	mprms->spr.obj.w_img.addr = mlx_get_data_addr(mprms->spr.obj.w_img.img,
		&(mprms->spr.obj.w_img.bpp), &(mprms->spr.obj.w_img.line_l),
		&(mprms->spr.obj.w_img.end));
}

void	ft_get_addr(t_all_tex *textures)
{
	textures->north.w_img.addr = mlx_get_data_addr(textures->north.w_img.img, \
		&(textures->north.w_img.bpp), &(textures->north.w_img.line_l), \
		&(textures->north.w_img.end));
	textures->south.w_img.addr = mlx_get_data_addr(textures->south.w_img.img, \
		&(textures->south.w_img.bpp), &(textures->south.w_img.line_l), \
		&(textures->south.w_img.end));
	textures->west.w_img.addr = mlx_get_data_addr(textures->west.w_img.img, \
		&(textures->west.w_img.bpp), &(textures->west.w_img.line_l), \
		&(textures->west.w_img.end));
	textures->east.w_img.addr = mlx_get_data_addr(textures->east.w_img.img, \
		&(textures->east.w_img.bpp), &(textures->east.w_img.line_l), \
		&(textures->east.w_img.end));
}

void	ft_init_all_textures(t_mprms *mprms)
{
	ft_convert_file_to_image(mprms);
	ft_get_addr(&(mprms->tex));
}

unsigned int	*ft_pixel_take(t_tex tex, int x, int y)
{
	return ((unsigned int *)(tex.w_img.addr + (y * tex.w_img.line_l + x * (tex.w_img.bpp / 8))));
}

//void 	ft_get_screen_size(t_mprms *mprms)
//{
//	mlx_get_screen_size(mprms->data.mlx, &mprms->res.screen_x, &mprms->res.screen_y);
//	if (mprms->res.screen_x < mprms->res.x)
//		mprms->res.x = mprms->res.screen_x;
//	if (mprms->res.screen_y < mprms->res.y)
//		mprms->res.y = mprms->res.screen_y;
//	printf("Width = %d Hight = %d\n", mprms->res.screen_x, mprms->res.screen_y);
//}



int main(int argc, char **argv)
{
	int fd;
	t_mprms mprms;
	int		x;
	t_list *list;
	fd = 0;
	list = NULL;
	if (argc == 2 || argc == 3)
		ft_creat_mprms(&fd, argv[1], &mprms, &list);


	mprms.data.mlx = mlx_init();
	ft_init_all_textures(&mprms);
	mprms.ray.ZBuffer = (double *) malloc(mprms.res.x * sizeof (double));
//	ft_get_screen_size(&mprms);
	mprms.data.win = mlx_new_window(mprms.data.mlx, (int)WW, (int)HH, "cub3d");
	mprms.data.img = mlx_new_image(mprms.data.mlx, (int)WW, (int)HH);
	mprms.data.addr = mlx_get_data_addr(mprms.data.img, &mprms.data.bits_per_pixel, &mprms.data.line_length, &mprms.data.endian);

	mprms.colors.floor.trns = create_trgb(mprms.colors.floor.r, mprms.colors.floor.g, mprms.colors.floor.b);
	mprms.colors.ceil.trns = create_trgb(mprms.colors.ceil.r, mprms.colors.ceil.g, mprms.colors.ceil.b);
	mprms.plr.dir_x = 0.0;
	mprms.plr.dir_y = -1.0;
	mprms.plr.pl_x = -0.66;
	mprms.plr.pl_y = 0.00;
//	for(int i = 0; i < mprms.spr.count; i++)
//	{
//		mprms.spr.spr[i].dist = ((mprms.plr.x - mprms.spr.spr[i].x) * (mprms.plr.x - mprms.spr.spr[i].x) +
//								  (mprms.plr.y - mprms.spr.spr[i].y) * (mprms.plr.y - mprms.spr.spr[i].y)); //sqrt not taken, unneeded
//	}
//	sort_sprites(mprms.spr.spr, mprms.spr.count);
	draw(&mprms);

//	mlx_key_hook(mprms.data.win, key_press, &mprms);
	mlx_hook(mprms.data.win, 2, (1L << 0), &key_press, &mprms);
	mlx_hook(mprms.data.win, 3, (1L << 1), &key_release, &mprms);
//	mlx_hook(mprms.data.win, 17, (1L << 0), &key_press, &mprms);
	mlx_loop_hook(mprms.data.mlx, &move_plr, &mprms);
	mlx_loop(mprms.data.mlx);
	free_list(&list);
	clean_struct(&mprms);
	return (0);
}