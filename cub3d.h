/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:30:10 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/29 08:29:47 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# include "minilibx_opengl/mlx.h"

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

# define KEY_ESC			53
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define LEFT				123
# define RIGHT				124

# define NONE				0xFF000000
# define WHITE				0x00FFFFFF
# define BLACK				0x00000000
# define RED				0x00FF0000
# define GREEN				0x0000FF00
# define BLUE				0x000000FF
# define MAGENTA			0x00FF00FF
# define YELLOW				0x00FFFF00
# define CYAN				0x0000FFFF

# define TEX_WIDTH			64
# define TEX_HEIGHT			64

# define CUB				"test1.cub"

typedef struct		s_tex
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;

	int				width;
	int				height;
}					t_tex;

typedef struct		s_flag
{
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
	int				pos;
}					t_flag;

typedef struct		s_buf
{
	double			*z_buffer;
}					t_buf;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_texs
{
	t_tex			tex_e;
	t_tex			tex_w;
	t_tex			tex_s;
	t_tex			tex_n;
	t_tex			tex_sp;
}					t_texs;

typedef struct		s_sp
{
	double			sprite_x;
	double			sprite_y;
	double			invdet;
	double			transform_x;
	double			transform_y;
	int				spritescreen_x;
	int				sprite_h;
	int				sprite_w;
	int				drawstart_x;
	int				drawstart_y;
	int				drawend_x;
	int				drawend_y;
	int				stripe;
}					t_sp;

typedef struct		s_all
{
	void			*mlx;
	void			*win;
	t_img			img;

	int				sprite_len;
	t_sprite		*sprites;
	int				*spriteorder;
	double			*spritedistance;
	t_sp			sp;

	int				map_width;
	int				map_height;
	int				**map;
	int				**fill_map;

	double			time;
	double			oldtime;
	double			movespeed;
	double			rotspeed;
	t_buf			buf;

	t_flag			flag;
	t_texs			texs;

	int				screen_w;
	int				screen_h;
	unsigned long	ceiling_color;
	unsigned long	floor_color;

	double			olddir_x;
	double			oldplane_x;

	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;

	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			perpwalldist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;

	int				line_h;
	int				drawstart;
	int				drawend;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			texpos;

	int				map_before_line;
}					t_all;

void				init_all(t_all *s);
void				init_flag(t_all *s);
void				init_var(t_all *s);
void				init_sprite(t_all *s);
void				init_map(t_all *s);
void				init_window(t_all *s);
void				init_texaddr(t_all *s);
int					push_key(int keycode, t_all *s);
void				read_line(t_all *s, char *line);
void				init_wall(t_all *s, char *line, int n);
void				init_floor_ceiling(t_all *s, char *line, int n);
void				init_tex(t_all *s, char *line);
unsigned long		create_rgb(t_all *s, int r, int g, int b);
int					gnl(int fd, char **line);
char				*skip_space(char *line, int *i);
int					check_flag(t_all *s);
int					check_line(t_all *s, char *line, int index);
void				check_map(t_all *s);
int					check_name(char *name);
void				my_mlx_pixel_put(t_all *s, int x, int y, int color);
void				my_mlx_pixel_put2(t_all *s, int x, int y, t_tex *tex);
void				my_mlx_pixel_put3(t_all *s, int x, int y, t_tex *tex);
void				init_resolution(t_all *s, char *line);
int					build_map(t_all *s, char *line, int index);
void				test(t_all *s);
int					ft_strlen(char *s);
void				ft_strlcpy(char *dst, char *src, int size);
char				*ft_strdup(char *s);
char				*ft_strjoin(char *s1, char *s2);
int					ft_atoi_new(char *str, int *index);
char				*ft_itoa(int n);
char				*ft_hextoa(unsigned int hex);
int					ft_isdigit(char c);
int					ft_ismap(char *line);
int					ft_allspace(char *line);
int					close_window(t_all *s);
void				init_window(t_all *s);
void				sort_sprites(t_all *s);
int					create_img(t_all *s);
void				put_wall(t_all *s);
void				put_sprite(t_all *s);
void				first_read(t_all *s);
void				second_read(t_all *s);

void 				north_tex_to_img(t_all *s, char *line);
void 				south_tex_to_img(t_all *s, char *line);
void 				east_tex_to_img(t_all *s, char *line);
void 				west_tex_to_img(t_all *s, char *line);

void				create_bmp(t_all *s);
void				bmp_file(t_all *s, int fd);
void				bmp_info(t_all *s, int fd);
void				bmp_data(t_all *s, int fd);

void				all_free(t_all *s, int n);
void				end(t_all *s, int n, int free_n);

#endif
