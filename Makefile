CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	cub3D

SRCS	=	main.c \
			ft_gnl.c \
			tools.c

OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) -L minilibx_opengl/ -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)
		./$(NAME)

clean	:
			rm -f *.o

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

# magick convert [-depth 8 -colors 16 -background while] -resize 64x64 test.png test.xpm