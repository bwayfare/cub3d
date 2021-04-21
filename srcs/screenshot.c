#include "../include/cub3d.h"

void	ft_create_header(int fd, int bmp_size)
{
	unsigned char	bmp_file_header[14];

	ft_bzero(bmp_file_header, 14);
	bmp_file_header[0] = (unsigned char)('B');
	bmp_file_header[1] = (unsigned char)('M');
	bmp_file_header[2] = (unsigned char)(bmp_size);
	bmp_file_header[3] = (unsigned char)(bmp_size >> 8);
	bmp_file_header[4] = (unsigned char)(bmp_size >> 16);
	bmp_file_header[5] = (unsigned char)(bmp_size >> 24);
	bmp_file_header[10] = (unsigned char)(54);
	write(fd, bmp_file_header, 14);
}

void	ft_create_info(t_mprms *mprms, int fd)
{
	unsigned char	bmp_info_header[40];

	ft_bzero(bmp_info_header, 40);
	bmp_info_header[0] = (unsigned char)(40);
	bmp_info_header[4] = (unsigned char)(mprms->res.x);
	bmp_info_header[5] = (unsigned char)(mprms->res.x >> 8);
	bmp_info_header[6] = (unsigned char)(mprms->res.x >> 16);
	bmp_info_header[7] = (unsigned char)(mprms->res.x >> 24);
	bmp_info_header[8] = (unsigned char)(mprms->res.y);
	bmp_info_header[9] = (unsigned char)(mprms->res.y >> 8);
	bmp_info_header[10] = (unsigned char)(mprms->res.y >> 16);
	bmp_info_header[11] = (unsigned char)(mprms->res.y >> 24);
	bmp_info_header[12] = (unsigned char)(1);
	bmp_info_header[14] = (unsigned char)(32);
	write(fd, bmp_info_header, 40);
}

void	ft_make_bmp(t_mprms *mprms)
{
	int				fd;
	int				bmp_size;
	int				height;
	int				line_len;

	fd = open("snapshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0655);
	if (fd < 0)
	{
		put_rtfm("ERROR: can't make snapshot.bmp\n");
	}
	draw(mprms);
	bmp_size = 14 + 40 + (4 * mprms->res.x * mprms->res.y);
	ft_create_header(fd, bmp_size);
	ft_create_info(mprms, fd);
	height = mprms->res.x;
	line_len = mprms->res.y * mprms->data.bits_per_pixel / 8;
	while (height > -1)
	{
		write(fd, (unsigned char *)(mprms->data.addr \
			+ height * mprms->data.line_length), line_len);
		height--;
	}
	close(fd);
}