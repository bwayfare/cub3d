#include "../include/cub3d.h"

static void head(t_mprms *mprms, int fd, int *num)
{
	unsigned int sz;
	unsigned char bmp[54];

	*num = (4 - (mprms->res.x * 3) % 4) % 4;
	sz = 54 + (*num + (mprms->res.x * 3)) * mprms->res.y;
	ft_memset(bmp, (unsigned char)0, 54);
	bmp[0] = 'B';
	bmp[1] = 'M';
	bmp[2] = (unsigned char)sz;
	bmp[3] = (unsigned char)(sz >> 8);
	bmp[4] = (unsigned char)(sz >> 16);
	bmp[5] = (unsigned char)(sz >> 24);
	bmp[10] = (unsigned char)54;
	bmp[14] = (unsigned char)40;
	bmp[18] = (unsigned char)(mprms->res.x);
	bmp[19] = (unsigned char)(mprms->res.x >> 8);
	bmp[20] = (unsigned char)(mprms->res.x >> 16);
	bmp[21] = (unsigned char)(mprms->res.x >> 24);
	bmp[22] = (unsigned char)(mprms->res.y);
	bmp[23] = (unsigned char)(mprms->res.y >> 8);
	bmp[24] = (unsigned char)(mprms->res.y >> 16);
	bmp[25] = (unsigned char)(mprms->res.y >> 24);
	bmp[26] = (unsigned char)1;
	bmp[28] = (unsigned char)24;
	write(fd, bmp, 54);
}

void screenshot(t_mprms *mprms)
{
	int    fd;
	int    i;
	int    num;
	unsigned char bmp[3];

	bmp[0] = (unsigned char)0;
	bmp[1] = (unsigned char)0;
	bmp[2] = (unsigned char)0;
	fd = open("screen.bmp", O_RDWR | O_CREAT, S_IRWXU, S_IRWXG);
	head(mprms, fd, &num);
	while (--mprms->res.y >= 0)
	{
		i = -1;
		while (++i < mprms->res.x)
			write(fd, &((int *)mprms->data.addr)[mprms->res.y * mprms->res.x + i], 3);
		write(fd, bmp, num);
	}
	close(fd);
	exit(0);
}