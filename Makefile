CC      =		gcc

DIR     =		./srcs/

HEADER  =		./include/cub3d.h \
				./include/define_error.h \
				./get_next_line/get_next_line.h \
				./libft/libft.h

NAME    =		cub3D

RM      =		rm -f

SRCS	=		$(DIR)additional_ft.c \
				$(DIR)check_map.c \
				$(DIR)checks.c \
				$(DIR)draw_addition.c \
				$(DIR)draw_sprite.c \
				$(DIR)draw_wall.c \
				$(DIR)ft_parser.c \
				$(DIR)ft_write_error.c \
				$(DIR)get_texture.c \
				$(DIR)global_draw.c \
				$(DIR)key_map.c \
				$(DIR)main.c \
				$(DIR)memory_work.c \
				$(DIR)move_left_right.c \
				$(DIR)move_player.c \
				$(DIR)parse_path.c \
				$(DIR)screenshot.c \
				$(DIR)search_map.c \
				$(DIR)turn_player.c \
				./get_next_line/get_next_line.c \
				./get_next_line/get_next_line_utils.c


OBJS    =		$(SRCS:.c=.o)

.c.o:
				$(CC) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				@make bonus -C ./libft
				@make -C ./minilibx
				@make -C ./minilibx_mms_20200219
				mv ./minilibx_mms_20200219/libmlx.dylib ./
				$(CC) -Wall -Werror -Wextra -g $(SRCS) ./libft/libft.a ./minilibx/libmlx.a ./libmlx.dylib -framework OpenGL -framework Appkit -o $(NAME)
				rm -rf cub3D.dSYM

%.o:			%c $(HEADER)
				@gcc -c $<

clean:
				$(RM) $(OBJS)
				@make clean -C ./libft
				@make clean -C ./minilibx
				@make clean -C ./minilibx_mms_20200219


fclean:			clean
					$(RM) $(NAME)
					$(RM) libmlx.dylib
					@make fclean -C ./libft

re:				fclean all

bonus:			re

.PHONY:			all clean fclean re bonus
