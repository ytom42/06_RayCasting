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

typedef struct	s_all{
	void		*mlx;
	void		*win;

	int			screenWidth;
	int			screenHeight;

	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

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

	t_tex		tex_E;
	t_tex		tex_W;
	t_tex		tex_S;
	t_tex		tex_N;
	t_flag		flag;
}				t_all;



int				ft_strlen(char *s);
void			ft_strlcpy(char *dst, char *src, int size);
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*itoa(int n);
char			*ft_hextoa(unsigned int  hex);
unsigned long	createRGB(int r, int g, int b);
int				gnl(int fd, char **line);