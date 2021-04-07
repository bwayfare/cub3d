/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:14:33 by bwayfare          #+#    #+#             */
/*   Updated: 2021/03/31 22:19:06 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int ft_creat_mprms(int *fd, char *argv, t_mprms *mprms)
{
	t_list		*list;
	char		*line;

	list = NULL;
	struct_init(mprms);
	if (!(*fd = open(argv, O_RDONLY)))
		return (0);
	while (mprms->check && ft_check_full(mprms) != 8 &&
		   get_next_line(*fd, &line) > 0 && (parse_line(mprms, line) != -1))
		free_line(&line);
	if (line)
		free_line(&line);
	if (mprms->check)
		f_get_map(&line, &list, fd, mprms);
	print(mprms);
//	free_list(&list);
//	clean_struct(mprms);
	return (1);
}

/*void            my_mlx_pixel_put(t_mprms *mprms, int x, int y, int color)
{
	char    *dst;

	dst = mprms->data.addr + (y * mprms->data.line_length + x * (mprms->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int             key_hook(int keycode, t_data *vars)
{
	printf("Hello from key_hook!\n");
	return (1);
}

int		key_press(int key, t_mprms *mprms)
{
	if(key == 111)
	{
		if(mprms->map.map[(int)(mprms->plr.x + mprms->plr.dir_x * 0.5)][(int)(mprms->plr.y)] != '1')
			mprms->plr.x += mprms->plr.dir_x * 0.5;
		if(mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y + mprms->plr.dir_y * 0.5)] != '1')
			mprms->plr.y += mprms->plr.dir_y * 0.5;
		write(1, "test\n", 5);
	}
	//move backwards if no wall behind you
	if(key == 116)
	{
		if(mprms->map.map[(int)(mprms->plr.x - mprms->plr.dir_x * 0.5)][(int)(mprms->plr.y)] != '1')
			mprms->plr.x -= mprms->plr.dir_x * 0.5;
		if(mprms->map.map[(int)(mprms->plr.x)][(int)(mprms->plr.y - mprms->plr.dir_y * 0.5)] != '1')
			mprms->plr.y -= mprms->plr.dir_y * 0.5;
		write(1, "test2\n", 6);
	}
	draw(mprms);
	return (0);
	//rotate to the right
}

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
		mprms->ray.deltaDistX = fabs(1 / mprms->ray.rayDirX);
		mprms->ray.deltaDistY = fabs(1 / mprms->ray.rayDirY);

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
			if (WWORLDMAP[mprms->ray.mapY][mprms->ray.mapX] == '1') mprms->ray.hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
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
//		mprms->ray.wallX; //where exactly the wall was hit
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
			my_mlx_pixel_put(mprms, x, y, 0xff0000); // mprms->ray.color);
		}
	}
	mlx_put_image_to_window(mprms->data.mlx, mprms->data.win, mprms->data.img, 0, 0);
	return 1;
}*/


int main(int argc, char **argv) {
	int fd;
	t_mprms mprms;
	int		x;
	t_list *list;

	fd = 0;
	list = NULL;
	if (argc == 2 || argc == 3)
		ft_creat_mprms(&fd, argv[1], &mprms);

	/*mprms.data.mlx = mlx_init();
	mprms.data.win = mlx_new_window(mprms.data.mlx, 500, 500, "Hui w rot!");
	mprms.data.img = mlx_new_image(mprms.data.mlx, 500, 500);
	mprms.data.addr = mlx_get_data_addr(mprms.data.img, &mprms.data.bits_per_pixel, &mprms.data.line_length, &mprms.data.endian);
//	mlx_put_image_to_window(all.data.mlx, all.data.win, all.data.img, 0, 0);

	x = -1;
//	mprms.plr.x = 5.0;
//	mprms.plr.y = 5.0;
	mprms.plr.dir_x = -1.0;
	mprms.plr.dir_y = 0.0;
	mprms.plr.pl_x = 0.66;
	mprms.plr.pl_y = -0.66;
	draw(&mprms);*/
//	while (++x < W)
//	{
//		all.ray.cameraX = 2 * x / (double)W - 1; //x-coordinate in camera space
//		all.ray.rayDirX = all.character.dirX + all.character.planeX*all.ray.cameraX;
//		all.ray.rayDirY = all.character.dirY + all.character.planeY*all.ray.cameraX;
//
//		//which box of the map we're in
//		all.ray.mapX = (int)all.character.posX;
//		all.ray.mapY = (int)all.character.posY;
//
//		//length of ray from one x or y-side to next x or y-side
//		all.ray.deltaDistX = fabs(1 / all.ray.rayDirX);
//		all.ray.deltaDistY = fabs(1 / all.ray.rayDirY);
//
//		all.ray.hit = 0; //was there a wall hit?
//		all.ray.sideDistX = 0;
//		if(all.ray.rayDirX < 0)
//		{
//			all.ray.stepX = -1;
//			all.ray.sideDistX = (all.character.posX - all.ray.mapX) * all.ray.deltaDistX;
//		}
//		else
//		{
//			all.ray.stepX = 1;
//			all.ray.sideDistX = (all.ray.mapX + 1.0 - all.character.posX) * all.ray.deltaDistX;
//		}
//		if(all.ray.rayDirY < 0)
//		{
//			all.ray.stepY = -1;
//			all.ray.sideDistY = (all.character.posY - all.ray.mapY) * all.ray.deltaDistY;
//		}
//		else
//		{
//			all.ray.stepY = 1;
//			all.ray.sideDistY = (all.ray.mapY + 1.0 - all.character.posY) * all.ray.deltaDistY;
//		}
//		while (all.ray.hit == 0)
//		{
//			//jump to next map square, OR in x-direction, OR in y-direction
//			if (all.ray.sideDistX < all.ray.sideDistY)
//			{
//				all.ray.sideDistX += all.ray.deltaDistX;
//				all.ray.mapX += all.ray.stepX;
//				all.ray.side = 0;
//			}
//			else
//				{
//				all.ray.sideDistY += all.ray.deltaDistY;
//				all.ray.mapY += all.ray.stepY;
//				all.ray.side = 1;
//			}
//			//Check if ray has hit a wall
//			if (WORLDMAP[all.ray.mapY][all.ray.mapX] == '1') all.ray.hit = 1;
//		}
//		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
//		if (all.ray.side == 0)
//		{
//			all.ray.perpWallDist = (all.ray.mapX - all.character.posX + (1.0 - all.ray.stepX) / 2) / all.ray.rayDirX;
////			printf("mapX - %d, posX - %f, dirX - %f, perpWallDist - %f\n", all.ray.mapX, all.character.posX, all.ray.rayDirX, all.ray.perpWallDist);
//		}
//		else
//		{
//			all.ray.perpWallDist = (all.ray.mapY - all.character.posY + (1.0 - all.ray.stepY) / 2) / all.ray.rayDirY;
////			printf("mapY - %d, posY - %f, dirY - %f, perpWallDist - %f\n", all.ray.mapY, all.character.posY, all.ray.rayDirY, all.ray.perpWallDist);
//		}
//		//Calculate height of line to draw on screen
//		all.ray.lineHeight = (int)(H / all.ray.perpWallDist);
//
//		//calculate lowest and highest pixel to fill in current stripe
//		all.ray.drawStart = -all.ray.lineHeight / 2 + H / 2;
//		if(all.ray.drawStart < 0) all.ray.drawStart = 0;
//		all.ray.drawEnd = all.ray.lineHeight / 2 + H / 2;
//		if(all.ray.drawEnd >= H) all.ray.drawEnd = H - 1;
//
//		//texturing calculations
//		all.ray.texNum = WORLDMAP[all.ray.mapY][all.ray.mapX] - 1; //1 subtracted from it so that texture 0 can be used!
//
//		//calculate value of wallX
//		all.ray.wallX; //where exactly the wall was hit
//		if(all.ray.side == 0) all.ray.wallX = all.character.posY + all.ray.perpWallDist * all.ray.rayDirY;
//		else          all.ray.wallX = all.character.posX + all.ray.perpWallDist * all.ray.rayDirX;
//		all.ray.wallX -= floor((all.ray.wallX));
//
//		//x coordinate on the texture
//		all.ray.texX = (int)(all.ray.wallX * (double)texWidth);
//		if(all.ray.side == 0 && all.ray.rayDirX > 0) all.ray.texX = texWidth - all.ray.texX - 1;
//		if(all.ray.side == 1 && all.ray.rayDirY < 0) all.ray.texX = texWidth - all.ray.texX - 1;
//
//		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
//		// How much to increase the texture coordinate per screen pixel
//		all.ray.step = 1.0 * texHeight / all.ray.lineHeight;
//		// Starting texture coordinate
//		all.ray.texPos = (all.ray.drawStart - H / 2 + all.ray.lineHeight / 2) * all.ray.step;
////		printf("x - %d\n", x);
////		printf("drawStart - %d\n", all.ray.drawStart);
////		printf("drawEnd - %d\n", all.ray.drawEnd);
//		for(int y = all.ray.drawStart; y < all.ray.drawEnd; y++)
//		{
//			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//			all.ray.texY = (int)all.ray.texPos & (texHeight - 1);
//			all.ray.texPos += all.ray.step;
//			if(all.ray.side == 1) all.ray.color = 0xff00ff; // (all.ray.color >> 1) & 8355711;
//			printf("x - %d, y - %d\n", x, y);
//			my_mlx_pixel_put(&all, x, y, 0xff0000); // all.ray.color);
//		}
//	}


	//speed modifiers

//	if(keyDown(SDLK_RIGHT))
//	{
//		both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//	}
	//rotate to the left
//	if(keyDown(SDLK_LEFT))
//	{
//		both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//	}
//	if(keyDown(SDLK_ESCAPE))
//	{
//		break;
//	}

//	my_mlx_pixel_put(&img, 0, 0, 0x00FF0000);
	/*mlx_hook(mprms.data.win, 2, (1L << 0), &key_press, &mprms);
	mlx_loop(mprms.data.mlx);*/
	return (0);
}
