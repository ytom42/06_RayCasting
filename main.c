#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 640
#define screenHeight 480

#define KEY_G 5

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct	s_all{
	void		*mlx;
	void		*win;

	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_all;

typedef struct	s_tex
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	int			width;
	int			height;
}				t_tex;


void	my_mlx_pixel_put(t_all *s, int x, int y, int color)
{
	char	*dst;

	dst = s->addr + (y * s->line_length + x * (s->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_all *s, int x, int y, t_tex *tex, int texX, int texY, int side)
{
	char	*dst;
	unsigned int color;

	dst = s->addr + (y * s->line_length + x * (s->bits_per_pixel / 8));
	color = *(unsigned int*)(tex->addr + (texY * tex->line_length + texX * (tex->bits_per_pixel / 8)));
	if(side == 1)
		color = (color >> 1) & 8355711;
	*(unsigned int*)dst = color;
}

double posX = 22, posY = 12;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;

double time = 0;
double oldTime = 0;

int	put_pixel(int keycode, t_all *s)
{
	int x;
	int y;
	t_tex tex;

	x = 0;
	y = 0;
	s->img = mlx_new_image(s->mlx, screenWidth, screenHeight);
	s->addr = mlx_get_data_addr(s->img, &s->bits_per_pixel, &s->line_length, &s->endian);
	tex.img = mlx_xpm_file_to_image(s->mlx, "pics/eagle.xpm", &tex.width, &tex.height);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.line_length, &tex.endian);

	double frameTime = 0.01;
	double moveSpeed = frameTime * 50.0;
	double rotSpeed = frameTime * 3.0;

	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(s->mlx, s->win);
		exit(0);
	}
	else if (keycode == KEY_W)
	{
		if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0)
			posX += dirX * moveSpeed;
		if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0)
			posY += dirY * moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0)
			posX -= dirX * moveSpeed;
		if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0)
			posY -= dirY * moveSpeed;
	}
	else if (keycode == RIGHT)
	{
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	else if(keycode == LEFT)
	{
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	else if(keycode == KEY_G)
	{
		mlx_put_image_to_window(s->mlx, s->win, tex.img, 0, 0);
		return (0);
	}

	while (x < screenWidth)
	{
		double cameraX = 2 * x / (double)screenWidth - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		
		int mapX = (int)(posX);
		int mapY = (int)(posY);

		double sideDistX;
		double sideDistY;
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;
		int hit = 0;
		int side;

		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		unsigned int color;
		double wallX;
		if(side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;

		y = 0;
		while (y < screenHeight)
		{
			if (y >= drawStart && y <= drawEnd)
			{
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				my_mlx_pixel_put2(s, x, y, &tex, texX, texY, side);
			}
			else if (y < (screenHeight / 2))
				my_mlx_pixel_put(s, x, y, 0x00F0F8FF);
			else
				my_mlx_pixel_put(s, x, y, 0x002F4F4F);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_all	s;

	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, screenWidth, screenHeight, "Hello world!");
	mlx_hook(s.win, 2, 0, put_pixel, &s);
	mlx_loop(s.mlx);
	return (1);
}





