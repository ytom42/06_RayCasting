/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:30:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2020/12/29 08:28:26 by ytomiyos         ###   ########.fr       */
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

#define mapWidth			24
#define mapHeight			24
#define texWidth			64
#define texHeight			64

#define CUB "tex.cub"

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

typedef struct	s_all
{
	void		*mlx;
	void		*win;

	int			screenWidth;
	int			screenHeight;

	t_img		img;

	double		moveSpeed;
	double		rotSpeed;
	double		oldDirX;
	double		oldPlaneX;

	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		time;
	double		oldTime;

	unsigned long	ceiling_color;
	unsigned long	floor_color;

	int				**map;
	int				map_width;
	int				map_height;

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

	t_tex		tex_E;
	t_tex		tex_W;
	t_tex		tex_S;
	t_tex		tex_N;
	t_tex		tex_SP;
	t_flag		flag;
	t_buf		buf;

	int			sprite_len;
	t_sprite	*sprites;
	int			*spriteOrder;
	double		*spriteDistance;
}				t_all;


void			init_all(t_all *s);
void			init_flag(t_all *s);
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
int				check_map(t_all *s, char *line);
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
