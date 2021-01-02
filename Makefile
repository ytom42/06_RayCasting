# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/19 23:21:23 by ytomiyos          #+#    #+#              #
#    Updated: 2020/12/19 23:21:25 by ytomiyos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	cub3D

SRCS	=	cub3d.c \
			ft_gnl.c \
			tools.c \
			tools2.c \
			init.c \
			map.c \
			textures.c 

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
