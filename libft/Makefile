CC      =		gcc

LIB     =		ar rc

DIR     =		./

HEADER  =		libft.h

FLAGS   =		-Wall -Werror -Wextra

NAME    =		libft.a

RM      =		rm -f

SRCS	=		$(DIR)ft_memset.c \
				$(DIR)ft_bzero.c \
				$(DIR)ft_memcpy.c \
				$(DIR)ft_memccpy.c \
				$(DIR)ft_memmove.c \
				$(DIR)ft_memchr.c \
				$(DIR)ft_memcmp.c \
				$(DIR)ft_strlen.c \
				$(DIR)ft_strlcpy.c \
				$(DIR)ft_strlcat.c \
				$(DIR)ft_strchr.c \
				$(DIR)ft_strrchr.c \
				$(DIR)ft_strnstr.c \
				$(DIR)ft_strncmp.c \
				$(DIR)ft_atoi.c \
				$(DIR)ft_isalpha.c \
				$(DIR)ft_isdigit.c \
				$(DIR)ft_isalnum.c \
				$(DIR)ft_isascii.c \
				$(DIR)ft_isprint.c \
				$(DIR)ft_toupper.c \
				$(DIR)ft_tolower.c \
				$(DIR)ft_calloc.c \
				$(DIR)ft_strdup.c \
				$(DIR)ft_substr.c \
				$(DIR)ft_strjoin.c \
				$(DIR)ft_strtrim.c \
				$(DIR)ft_split.c \
				$(DIR)ft_itoa.c \
				$(DIR)ft_strmapi.c \
				$(DIR)ft_putchar_fd.c \
				$(DIR)ft_putstr_fd.c \
				$(DIR)ft_putendl_fd.c \
				$(DIR)ft_putnbr_fd.c

SRCS_B	=		$(DIR)ft_lstnew.c \
				$(DIR)ft_lstadd_front.c \
				$(DIR)ft_lstsize.c \
				$(DIR)ft_lstlast.c \
				$(DIR)ft_lstadd_back.c \
				$(DIR)ft_lstdelone.c \
				$(DIR)ft_lstclear.c \
				$(DIR)ft_lstiter.c \
				$(DIR)ft_lstmap.c


OBJS    =		$(SRCS:.c=.o)

OBJS_B	=		$(SRCS_B:.c=.o)

.c.o:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(HEADER)
					$(LIB) $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(OBJS_B)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

so:				$(OBJS) $(OBJS_B)
					$(CC) -o libft.so $(OBJS) $(OBJS_B) -shared

bonus:			$(OBJS) $(OBJS_B)
					$(LIB) $(NAME) $(OBJS) $(OBJS_B)

.PHONY:			all clean fclean re bonus
