# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/19 23:21:23 by ytomiyos          #+#    #+#              #
#    Updated: 2021/01/31 17:37:18 by ytomiyos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	cub3D

SRCS	=	cub3d.c \
			ft_gnl.c \
			tools1.c \
			tools2.c \
			tools3.c \
			tools4.c \
			init_all.c \
			init_map.c \
			init_cubinfo.c \
			check_map.c \
			check_line.c \
			sort_sprites.c \
			first_read.c \
			second_read.c \
			create_img.c \
			push_key.c \
			put_wall.c \
			put_sprite.c \
			file_to_image.c \
			create_bmp.c \
			free.c \
			error.c

OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) -L minilibx_opengl/ -l mlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)

clean	:
			rm -f *.o

fclean	:	clean
			rm -f $(NAME)
			rm -f window.bmp

re		:	fclean all

.PHONY	:	all clean fclean re
