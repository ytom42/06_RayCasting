/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:30:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/19 03:08:00 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

#include "minilibx_opengl/mlx.h"


#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17

#define KEY_ESC				53
#define KEY_W				13
#define KEY_A				0
#define KEY_S				1
#define KEY_D				2
#define LEFT				123
#define RIGHT				124

#define NONE				0xFF000000
#define WHITE				0x00FFFFFF
#define BLACK				0x00000000
#define RED					0x00FF0000
#define GREEN				0x0000FF00
#define BLUE				0x000000FF
#define MAGENTA				0x00FF00FF
#define YELLOW				0x00FFFF00
#define CYAN				0x0000FFFF

#define texWidth			64
#define texHeight			64

#define CUB "test2.cub"

typedef struct	s_tex
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

	int			width;
	int			height;
}				t_tex;

typedef struct s_flag
{
	int		R;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		S;
	int		F;
	int		C;
	int		POS;
}				t_flag;

typedef struct	s_buf
{
	double		*ZBuffer;
}				t_buf;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_sprite
{
	double x;
	double y;
}				t_sprite;

typedef struct	s_texs
{
	t_tex		tex_E;
	t_tex		tex_W;
	t_tex		tex_S;
	t_tex		tex_N;
	t_tex		tex_SP;
}				t_texs;

typedef struct	s_all
{
	void		*mlx;

	int			sprite_len;
	t_sprite	*sprites;
	int			*spriteOrder;
	double		*spriteDistance;

	int				map_width;
	int				map_height;
	int				**map;

	void		*win;
	t_img		img;

	double		time;
	double		oldTime;
	double		moveSpeed;
	double		rotSpeed;
	t_buf		buf;

	t_flag		flag;
	t_texs		texs;

	int				screenWidth;
	int				screenHeight;
	unsigned long	ceiling_color;
	unsigned long	floor_color;




	double		oldDirX;
	double		oldPlaneX;

	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;


	int			**fill_map;

	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;

	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	double		wallX;
	int			texX;
	int			texY;
	double		step;
	double		texPos;
}				t_all;

void			init_all(t_all *s);
void			init_flag(t_all *s);
void			init_var(t_all *s);
void			init_sprite(t_all *s);
void			init_map(t_all *s);
void			init_window(t_all *s);
void			init_texaddr(t_all *s);

void			read_line(t_all *s, char *line);
void			init_wall(t_all *s, char *line, int n);
void			init_floor_ceiling(t_all *s, char *line, int n);
void			init_tex(t_all *s, char *line);
unsigned long	createRGB(int r, int g, int b);
int				gnl(int fd, char **line);
char			*skip_space(char *line, int *i);
int				check_flag(t_all *s);
int				check_line(t_all *s, char *line, int index);
void			check_map(t_all *s, int map_height);
void			my_mlx_pixel_put(t_all *s, int x, int y, int color);
void			my_mlx_pixel_put2(t_all *s, int x, int y, t_tex *tex);
void			my_mlx_pixel_put3(t_all *s, int x, int y, t_tex *tex);
void			init_resolution(t_all *s, char *line);
int				build_map(t_all *s, char *line, int index);
void			test(t_all *s);
int				ft_strlen(char *s);
void			ft_strlcpy(char *dst, char *src, int size);
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_itoa(int n);
char			*ft_hextoa(unsigned int  hex);
void			init_window(t_all *s);
void			sort_sprites(t_all *s);
int				put_img(t_all *s);
void			put_wall(t_all *s);
void			put_sprite(t_all *s);
void			first_read(t_all *s, int *before_line, int *map_height);
void			second_read(t_all *s, int *before_line);


void			create_bmp(t_all *s);
void			bmp_file(t_all *s, int fd);
void			bmp_info(t_all *s, int fd);
void			bmp_data(t_all *s, int fd);
