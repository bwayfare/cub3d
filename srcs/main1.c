#include "../include/cub3d.h"

int		draw(t_mprms *mprms);

void print(t_mprms *mprms)
{
	printf("R = %ld %ld\n", mprms->res.x, mprms->res.y);
	printf("C = %d %d %d\n", mprms->colors.cell_color.r, mprms->colors.cell_color.g, mprms->colors.cell_color.b);
	printf("F = %d %d %d\n", mprms->colors.floor_color.r, mprms->colors.floor_color.g, mprms->colors.floor_color.b);
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
		printf("key = %d \n", key);
//100
//97
	if (key == 119)
		mprms->pres.up = 1;
	if (key == 115)
		mprms->pres.down = 1;
	if (key == 100)
		mprms->pres.right = 1;
	if (key == 97)
		mprms->pres.left = 1;
	write(1, "press\n", 6);
	return (0);
}

int 		key_release(int key, t_mprms * mprms)
{
	if (key == 119)
		mprms->pres.up = 0;
	if (key == 115)
		mprms->pres.down = 0;
	if (key == 100)
		mprms->pres.right = 0;
	if (key == 97)
		mprms->pres.left = 0;
	write(1, "releas\n", 7);
	return (0);
}

int 		move_plr(t_mprms *mprms)
{
//		write(1, "test\n", 5);
//	printf("key = %d \n", key);
	if(mprms->pres.up)
	{
		if(mprms->map.map[(int)(mprms->plr.y)][(int)(mprms->plr.x + mprms->plr.dir_x * 0.005)] != '1')
			mprms->plr.x += mprms->plr.dir_x * 0.005;
		if(mprms->map.map[(int)(mprms->plr.y + mprms->plr.dir_y * 0.005)][(int)(mprms->plr.x)] != '1')
			mprms->plr.y += mprms->plr.dir_y * 0.005;
		write(1, "test\n", 5);
	}
	//move backwards if no wall behind you
	if(mprms->pres.down)
	{
		if(mprms->map.map[(int)(mprms->plr.y)][(int)(mprms->plr.x - mprms->plr.dir_x * 0.005)] != '1')
			mprms->plr.x -= mprms->plr.dir_x * 0.005;
		if(mprms->map.map[(int)(mprms->plr.y - mprms->plr.dir_y * 0.005)][(int)(mprms->plr.x)] != '1')
			mprms->plr.y -= mprms->plr.dir_y * 0.005;
		write(1, "test2\n", 6);
	}
	if (mprms->pres.right)
	{
		//both camera direction and camera plane must be rotated
		mprms->ray.oldDirX = mprms->plr.dir_x;
		mprms->plr.dir_x = mprms->plr.dir_x * cos(-0.005) - mprms->plr.dir_y * sin(-0.005);
		mprms->plr.dir_y = mprms->ray.oldDirX * sin(-0.005) + mprms->plr.dir_y * cos(-0.005);
		mprms->ray.oldPlaneX = mprms->plr.pl_x;
		mprms->plr.pl_x = mprms->plr.pl_x * cos(-0.005) - mprms->plr.pl_y * sin(-0.005);
		mprms->plr.pl_y = mprms->ray.oldPlaneX * sin(-0.005) + mprms->plr.pl_y * cos(-0.005);
	}
	//rotate to the left
	if (mprms->pres.left)
	{
		//both camera direction and camera plane must be rotated
		mprms->ray.oldDirX = mprms->plr.dir_x;
		mprms->plr.dir_x = mprms->plr.dir_x * cos(0.005) - mprms->plr.dir_y * sin(0.005);
		mprms->plr.dir_y = mprms->ray.oldDirX * sin(0.005) + mprms->plr.dir_y * cos(0.005);
		mprms->ray.oldPlaneX = mprms->plr.pl_x;
		mprms->plr.pl_x = mprms->plr.pl_x * cos(0.005) - mprms->plr.pl_y * sin(0.005);
		mprms->plr.pl_y = mprms->ray.oldPlaneX * sin(0.005) + mprms->plr.pl_y * cos(0.005);
	}
//	mprms->ray.color += 1;
	draw(mprms);
	return (0);
}

//int		key_press(int key, t_mprms *mprms)
//{
////	write(1, "test\n", 5);
//	printf("key = %d \n", key);
//	if(key == 119)
//	{
//		if(mprms->map.map[(int)(mprms->plr.y)][(int)(mprms->plr.x + mprms->plr.dir_x * 0.5)] != '1')
//			mprms->plr.x += mprms->plr.dir_x * 0.5;
//		if(mprms->map.map[(int)(mprms->plr.y + mprms->plr.dir_y * 0.05)][(int)(mprms->plr.x)] != '1')
//			mprms->plr.y += mprms->plr.dir_y * 0.5;
//		write(1, "test\n", 5);
//	}
//	//move backwards if no wall behind you
//	if(key == 115)
//	{
//		if(mprms->map.map[(int)(mprms->plr.y)][(int)(mprms->plr.x - mprms->plr.dir_x * 0.5)] != '1')
//			mprms->plr.x -= mprms->plr.dir_x * 0.5;
//		if(mprms->map.map[(int)(mprms->plr.y - mprms->plr.dir_y * 0.5)][(int)(mprms->plr.x)] != '1')
//			mprms->plr.y -= mprms->plr.dir_y * 0.5;
//		write(1, "test2\n", 6);
//	}
//	draw(mprms);
//	return (0);
//	//rotate to the right
//}

int		draw(t_mprms *mprms)
{
	int x = -1;
	W = 500;
	H = 500;
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
			if (WWORLDMAP[mprms->ray.mapY][mprms->ray.mapX] == '1')
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
		mprms->ray.texNum = WWORLDMAP[mprms->ray.mapY][mprms->ray.mapX] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		mprms->ray.wallX; //where exactly the wall was hit
		if(mprms->ray.side == 0) mprms->ray.wallX = mprms->plr.y + mprms->ray.perpWallDist * mprms->ray.rayDirY;
		else mprms->ray.wallX = mprms->plr.x + mprms->ray.perpWallDist * mprms->ray.rayDirX;
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
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			mprms->ray.texY = (int)mprms->ray.texPos & (texHeight - 1);
			mprms->ray.texPos += mprms->ray.step;
			if(mprms->ray.side == 1) mprms->ray.color = 0xff00ff; // (mprms->ray.color >> 1) & 8355711;
//			printf("x - %d, y - %d\n", x, y);
			my_mlx_pixel_put(mprms, x, y, mprms->colors.floor_color.trns);
			my_mlx_pixel_put(mprms, x, y, mprms->ray.color); // mprms->ray.color);
		}
	}
	mlx_put_image_to_window(mprms->data.mlx, mprms->data.win, mprms->data.img, 0, 0);
	mlx_destroy_image(mprms->data.mlx, mprms->data.img);
	mprms->data.addr = NULL;
	mprms->data.img = NULL;
	mprms->data.img = mlx_new_image(mprms->data.mlx, 500, 500);
	mprms->data.addr = mlx_get_data_addr(mprms->data.img, &mprms->data.bits_per_pixel, &mprms->data.line_length, &mprms->data.endian);
}

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
	mprms.data.win = mlx_new_window(mprms.data.mlx, 500, 500, "cub3d");
	mprms.data.img = mlx_new_image(mprms.data.mlx, 500, 500);
	mprms.data.addr = mlx_get_data_addr(mprms.data.img, &mprms.data.bits_per_pixel, &mprms.data.line_length, &mprms.data.endian);

	mprms.colors.floor_color.trns = create_trgb(mprms.colors.floor_color.r, mprms.colors.floor_color.g, mprms.colors.floor_color.b);
	mprms.colors.cell_color.trns = create_trgb(mprms.colors.cell_color.r, mprms.colors.cell_color.g, mprms.colors.cell_color.b);
	mprms.plr.dir_x = -1.0;
	mprms.plr.dir_y = 0.0;
	mprms.plr.pl_x = -0.66;
	mprms.plr.pl_y = 0.66;
	draw(&mprms);

//	mlx_key_hook(mprms.data.win, key_press, &mprms);
	mlx_hook(mprms.data.win, 2, (1L << 0), &key_press, &mprms);
	mlx_hook(mprms.data.win, 3, (1L << 1), &key_release, &mprms);
	mlx_loop_hook(mprms.data.mlx, &move_plr, &mprms);
	mlx_loop(mprms.data.mlx);
	free_list(&list);
	clean_struct(&mprms);
	return (0);
}