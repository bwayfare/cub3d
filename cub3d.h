#ifndef CUB_CUB3D_H
# define CUB_CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>

# define NO_MAP_ERROR "Need map file as argument!\n"

typedef struct		s_res {
	int				x;
	int				y;
}					t_res;

typedef struct		s_fclr {
	int				r;
	int 			g;
	int 			b;
}					t_fclr;

typedef struct		s_cclr {
	int				r;
	int				g;
	int 			b;
}					t_cclr;

typedef struct		s_clrs {
	t_fclr			floor_color;
	t_cclr			cell_color;
}					t_clrs;

typedef struct		s_paths {
	char			*no;
	char 			*so;
	char			*we;
	char 			*ea;
	char			*sprt;
}					t_paths;

typedef struct 		s_full_set
{
	int 			f_clr;
	int 			c_clr;
	int 			res;
	int 			no;
	int 			so;
	int 			we;
	int 			ea;
	int 			sprt;
}					t_full;

typedef struct 		s_map
{
	char 			**map;
	int 			len;
	int 			size;
}					t_map;

typedef struct 		s_player
{
	char 			pl;
}					t_plr;

typedef struct		s_mprms
{
	int				check;
	t_res			res;
	t_clrs			colors;
	t_paths			paths;
	t_full 			full;
	t_map 			map;
	t_plr			plr;
}					t_mprms;


void 				ft_trimm_sp(char **line);
int    				parse_line(t_mprms *mparams, char *line);
int					ft_jmp_sp(char **line, char *str, char flag);
int					ft_size_n(int n);
int 				ft_res_check(char *line);
int 				ft_check_clr(t_mprms *mprms);
int					prs_pth(t_mprms *mprms, char *line);
void 				struct_init(t_mprms *mprms);
void 				clean_struct(t_mprms *mprms);
int					ft_check_full(t_mprms *mprms);
int					ft_search_map(char *line, t_mprms *mprms, t_list *list, int *res);
int 				map_creator(t_list *list, t_mprms *mprms);
void 				free_list(t_list **head);
int 				ft_ch_elem_map(t_mprms *mprms);
int					ch_wall(t_mprms *mprms);

#endif //CUB_CUB3D_H