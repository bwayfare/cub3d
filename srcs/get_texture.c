#include "../include/cub3d.h"

void	ft_convert_file_to_image(t_mprms *mprms)
{
	mprms->tex.north.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.no, &(mprms->tex.north.width), \
		&(mprms->tex.north.height));
	if (mprms->tex.north.w_img.img == NULL || mprms->tex.north.height != 64
		|| mprms->tex.north.width != 64)
		put_rtfm(ETC);
	mprms->tex.south.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.so, &(mprms->tex.south.width), \
		&(mprms->tex.south.height));
	if (mprms->tex.south.w_img.img == NULL || mprms->tex.south.height != 64
		|| mprms->tex.south.width != 64)
		put_rtfm(ETC);
	mprms->tex.west.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.we, &(mprms->tex.west.width), \
		&(mprms->tex.west.height));
	if (mprms->tex.west.w_img.img == NULL || mprms->tex.west.height != 64
		|| mprms->tex.west.width != 64)
		put_rtfm(ETC);
	mprms->tex.east.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx, \
		mprms->paths.ea, &(mprms->tex.east.width), \
		&(mprms->tex.east.height));
	if (mprms->tex.east.w_img.img == NULL || mprms->tex.east.height != 64
		|| mprms->tex.east.width != 64)
		put_rtfm(ETC);
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

void	get_sprite_tex(t_mprms *mprms)
{
	mprms->spr.obj.w_img.img = mlx_xpm_file_to_image(mprms->data.mlx,
	mprms->paths.sprt, &(mprms->spr.obj.width), &(mprms->spr.obj.height));
	if (mprms->spr.obj.w_img.img == NULL || mprms->spr.obj.width != 64
		|| mprms->spr.obj.height != 64)
		put_rtfm(ETC);
	mprms->spr.obj.w_img.addr = mlx_get_data_addr(mprms->spr.obj.w_img.img,
	&(mprms->spr.obj.w_img.bpp), &(mprms->spr.obj.w_img.line_l),
	&(mprms->spr.obj.w_img.end));
}

void	init_texture(t_mprms *mprms)
{
	ft_convert_file_to_image(mprms);
	ft_get_addr(&(mprms->tex));
	get_sprite_tex(mprms);
}