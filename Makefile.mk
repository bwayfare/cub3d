##
## Makefile for MiniLibX in /home/boulon/work/c/raytraceur/minilibx
## 
## Made by Olivier Crouzet
## Login   <ol@epitech.net>
## 
## Started on  Tue Oct  5 15:56:43 2004 Olivier Crouzet
## Last update Tue May 15 15:41:20 2007 Olivier Crouzet
##

## Please use configure script


INC	=%%%%
HT	=%%%%
DOCP	=%%%%

CC	= gcc

NAME	= libmlx.a

SRC	= minilibx-linux-master/mlx_init.c minilibx-linux-master/mlx_new_window.c \
	minilibx-linux-master/mlx_pixel_put.c minilibx-linux-master/mlx_loop.c \
	minilibx-linux-master/mlx_mouse_hook.c minilibx-linux-master/mlx_key_hook.c \
	minilibx-linux-master/mlx_expose_hook.c minilibx-linux-master/mlx_loop_hook.c \
	minilibx-linux-master/mlx_int_anti_resize_win.c minilibx-linux-master/mlx_int_do_nothing.c \
	minilibx-linux-master/mlx_int_wait_first_expose.c minilibx-linux-master/mlx_int_get_visual.c \
	minilibx-linux-master/mlx_flush_event.c minilibx-linux-master/mlx_string_put.c \
	minilibx-linux-master/mlx_set_font.c \
	minilibx-linux-master/mlx_new_image.c minilibx-linux-master/mlx_get_data_addr.c \
	minilibx-linux-master/mlx_put_image_to_window.c minilibx-linux-master/mlx_get_color_value.c minilibx-linux-master/mlx_clear_window.c \
	minilibx-linux-master/mlx_xpm.c minilibx-linux-master/mlx_int_str_to_wordtab.c minilibx-linux-master/mlx_destroy_window.c \
	minilibx-linux-master/mlx_int_param_event.c minilibx-linux-master/mlx_int_set_win_event_mask.c minilibx-linux-master/mlx_hook.c \
	minilibx-linux-master/mlx_rgb.c mlx_destroy_image.c minilibx-linux-master/mlx_mouse.c minilibx-linux-master/mlx_screen_size.c \
	minilibx-linux-master/mlx_destroy_display.c

OBJ	=$(SRC:.c=.o)
CFLAGS	= -O3 -I$(INC)

all	: $(NAME) $(DOCP)

$(NAME)	: $(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

do_cp	:
	cp $(NAME) libmlx_$(HT).a


clean	:
	rm -f $(OBJ) $(NAME) libmlx_$(HT).a *~ core *.core
