CC      =		gcc

LIB     =		ar rc

DIR     =		./srcs

HEADER  =		./include/cub3d.h \
				./include/define_error.h

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
				$(DIR)turn_player.c


OBJS    =		$(SRCS:.c=.o)

.c.o:
				$(CC) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(HEADER)
					$(LIB) $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(OBJS_B)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

bonus:			re

.PHONY:			all clean fclean re bonus
