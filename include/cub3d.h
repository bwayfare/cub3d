/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwayfare <bwayfare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:15:08 by bwayfare          #+#    #+#             */
/*   Updated: 2021/04/24 14:14:04 by bwayfare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_CUB3D_H
# define CUB_CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "define_error.h"

# include "../minilibx/mlx.h"
# include "../minilibx_mms_20200219/mlx1.h"
# include <math.h>

# define W mprms->res.x
# define H mprms->res.y
# define WWORLDMAP mprms->map.map
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	void			*mlx;
	void			*win;
}					t_data;

typedef struct		s_pres
{
	short			up;
	short			down;
	short			right;
	short			left;
	short			turnright;
	short			turnleft;
	short			esc;
}					t_pres;

typedef struct		s_img
{
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				end;
}					t_img;

typedef struct		s_tex
{
	t_img			w_img;
	int				width;
	int				height;
}					t_tex;

typedef struct		s_spr
{
	double			x;
	double			y;
	double			dist;
}					t_spr;

typedef struct		s_all_tex
{
	t_tex			north;
	t_tex			south;
	t_tex			east;
	t_tex			west;
}					t_all_tex;

typedef struct		s_all_sprite
{
	int				count;
	t_tex			obj;
	t_spr			*spr;
}					t_all_sprite;

typedef struct		s_res
{
	int				x;
	int				y;
	int				screen_x;
	int				screen_y;
}					t_res;

typedef struct		s_fclr
{
	int				r;
	int				g;
	int				b;
	int				trns;
}					t_fclr;

typedef struct		s_cclr
{
	int				r;
	int				g;
	int				b;
	int				trns;
}					t_cclr;

typedef struct		s_clrs
{
	t_fclr			floor;
	t_cclr			ceil;
}					t_clrs;

typedef struct		s_paths
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprt;
}					t_paths;

typedef struct		s_full_set
{
	int				f_clr;
	int				c_clr;
	int				res;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				sprt;
}					t_full;

typedef struct		s_map
{
	char			**map;
	int				len;
	int				size;
}					t_map;

typedef struct		s_player
{
	char			pl;
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			pl_x;
	double			pl_y;
}					t_plr;

typedef struct		s_ray
{
	double			cam_x;
	double			r_dir_x;
	double			r_dir_y;
	int				mp_x;
	int				mp_y;
	double			sd_dst_x;
	double			sd_dts_y;
	double			dlt_dst_x;
	double			dlt_dst_y;
	double			prp_wall_dst;
	int				stp_x;
	int				stp_y;
	unsigned int	*color;
	int				hit;
	int				side;
	int				line_hght;
	int				drw_start;
	int				drw_end;
	int				tx_num;
	double			wll_x;
	int				tx_x;
	double			step;
	double			tx_pos;
	int				tx_y;
	double			ld_dr_x;
	double			ld_pln_x;
	double			*z_buffer;
}					t_ray;

typedef struct		s_draw_spr
{
	double			sprt_x;
	double			sprt_y;
	double			nv_det;
	double			transf_x;
	double			transf_y;
	int				sprt_scrn_x;
	int				sprt_hght;
	int				drw_strt_y;
	int				drw_end_y;
	int				sprt_wdth;
	int				drw_strt_x;
	int				drw_end_x;
	int				tx_x;
	int				d;
	int				tx_y;
	unsigned int	*color;
}					t_draw_spr;

typedef struct		s_mprms
{
	int				check;
	t_res			res;
	t_clrs			colors;
	t_paths			paths;
	t_full			full;
	t_map			map;
	t_plr			plr;
	t_ray			ray;
	t_data			data;
	t_pres			pres;
	t_all_tex		tex;
	t_all_sprite	spr;
	t_draw_spr		draw_spr;
	int				screenshot;
	int				argc;
}					t_mprms;

void				ft_trimm_sp(char **line);
int					parse_line(t_mprms *mparams, char *line);
int					ft_jmp_sp(char **line, char *str, char flag);
int					ft_size_n(int n);
int					ft_res_check(char *line);
int					ft_check_clr(t_mprms *mprms, char *str);
int					prs_pth(t_mprms *mprms, char *st);
void				struct_init(t_mprms *mprms);
void				clean_struct(t_mprms *mprms);
int					ft_check_full(t_mprms *mprms);
int					ft_search_map(char *line, t_mprms *mprms,
					t_list *list, int *res);
int					map_creator(t_list *list, t_mprms *mprms);
void				free_list(t_list **head);
int					ft_ch_elem_map(t_mprms *mprms);
int					ch_wall(t_mprms *mprms, char **arr);
int					put_rtfm(char *str);
void				free_line(char **line);
void				init_texture(t_mprms *mprms);
unsigned int		*ft_pixel_take(t_tex tex, int x, int y);
void				draw_spr(t_mprms *mprms);
void				turn_player(t_mprms *mprms);
int					key_press(int key, t_mprms *mprms);
int					key_release(int key, t_mprms *mprms);
void				sort_sprites(t_spr *spr, int count);
int					create_trgb(int r, int g, int b);
void				draw_floor_ceil(t_mprms *mprms);
void				my_mlx_pixel_put(t_mprms *mprms, int x, int y, int color);
unsigned int		*ft_pixel_take(t_tex tex, int x, int y);
void				move_left(t_mprms *mprms, double speed);
void				move_right(t_mprms *mprms, double speed);
int					main_move_plr(t_mprms *mprms);
int					draw(t_mprms *mprms, int x);
void				wall_draw_init(t_mprms *mprms, int x);
void				wall_draw_init_2(t_mprms *mprms, int x);
void				while_ray_hit(t_mprms *mprms);
void				calculate_draw_wall(t_mprms *mprms);
void				circle_draw(t_mprms *mprms, int x, int y);
void				dist_sort(t_mprms *mprms);
void				draw_spr_param_init(t_mprms *mprms, int i);
void				draw_spr_param_init_2(t_mprms *mprms);
void				circle_drap_spr(t_mprms *mprms, int stripe);
void				draw_spr(t_mprms *mprms);
void				screenshot(t_mprms *mprms);
int					ft_exit(void);

#endif
