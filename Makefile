# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/19 23:21:23 by ytomiyos          #+#    #+#              #
#    Updated: 2021/02/03 19:58:34 by ytomiyos         ###   ########.fr        #
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
			move.c \
			sort_sprites.c \
			first_read.c \
			first_read2.c \
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
		$(CC) $(CFLAGS) libmlx.dylib -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)

clean	:
			rm -f *.o

fclean	:	clean
			rm -f $(NAME)
			rm -f window.bmp

re		:	fclean all

.PHONY	:	all clean fclean re
