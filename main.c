#include "cub3d.h"

#define worldMap s->map

// int worldMap[mapWidth][mapHeight]=
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

void	my_mlx_pixel_put(t_all *s, int x, int y, int color)
{
	char	*dst;

	dst = s->addr + (y * s->line_len + x * (s->bpp / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_all *s, int x, int y, t_tex *tex, int texX, int texY)
{
	char	*dst;
	unsigned int color;

	dst = s->addr + (y * s->line_len + x * (s->bpp / 8));
	color = *(unsigned int*)(tex->addr + (texY * tex->line_len + texX * (tex->bpp / 8)));
	*(unsigned int*)dst = color;
}

char	*ft_space(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] != ' ')
			return (&line[*i]);
		*i += 1;
	}
	return (NULL);
}


void	ft_R(t_all *s, char *line)
{
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	line += 1;
	ft_space(line, &i);
	while (line[i] >= '0' && line[i] <= '9')
	{
		tmp = (tmp * 10) + (line[i] - 48);
		i++;
	}
	s->screenWidth = tmp;
	tmp = 0;
	ft_space(line, &i);
	while (line[i] >= '0' && line[i] <= '9')
	{
		tmp = (tmp * 10) + (line[i] - 48);
		i++;
	}
	s->screenHeight = tmp;
	s->flag.R = 1;
}

void	ft_NO(t_all *s, char *line, int n)
{
	int i;

	i = 0;
	line += 2;
	ft_space(line, &i);
	if (n == 0)
	{
		s->tex_N.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->tex_N.width, &s->tex_N.height);
		s->flag.NO = 1;
	}
	else if (n == 1)
	{
		s->tex_S.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->tex_S.width, &s->tex_S.height);
		s->flag.SO = 1;
	}
	else if (n == 2)
	{
		s->tex_E.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->tex_E.width, &s->tex_E.height);
		s->flag.WE = 1;
	}
	else if (n == 3)
	{
		s->tex_W.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->tex_W.width, &s->tex_W.height);
		s->flag.EA = 1;
	}
}

void	ft_FC(t_all *s, char *line, int n)
{
	int i;
	int r;
	int g;
	int b;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	line += 1;
	ft_space(line, &i);
	if (n == 0)
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			r = (r * 10) + (r - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			g = (g * 10) + (g - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			b = (b * 10) + (b - '0');
			i++;
		}
		s->floor_color = createRGB(r, g, b);
		s->flag.F = 1;
	}
	else if (n == 1)
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			r = (r * 10) + (r - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			g = (g * 10) + (g - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			b = (b * 10) + (b - '0');
			i++;
		}
		s->ceiling_color = createRGB(r, g, b);
		s->flag.C = 1;
	}
}

void	check_line(t_all *s, char *line)
{
	int i;

	i = 0;
	ft_space(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_R(s, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_NO(s, line, 0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_NO(s, line, 1);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		ft_NO(s, line, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		ft_NO(s, line, 3);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_FC(s, line, 0);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_FC(s, line, 1);
	else
		return ;
	// else if (line[i] == 'S' && line[i + 1] == ' ')
	// 	ft_R(s, line);
}

int		check_flag(t_all *s)
{
	// printf("F  -> %d\n", s->F.F);
	// printf("C  -> %d\n", s->F.C);
	// printf("R  -> %d\n", s->F.R);
	// printf("NO -> %d\n", s->F.NO);
	// printf("SO -> %d\n", s->F.SO);
	// printf("WE -> %d\n", s->F.WE);
	// printf("EA -> %d\n\n", s->F.EA);
	if (s->flag.F && s->flag.C && s->flag.R && s->flag.NO && s->flag.SO && s->flag.WE && s->flag.EA)
		return (1);
	return (0);
}

int		check_map(t_all *s, char *line)
{
	int len;

	len = ft_strlen(line);
	if (s->map_width < len)
		s->map_width = len;
	return (0);
}

int		build_map(t_all *s, char *line, int index)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(line);
	s->map[index] = (int*)malloc(sizeof(int*) * s->map_width);
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
			s->map[index][i] = (int)(line[i] - 48);
		else if (line[i] == ' ')
			s->map[index][i] = -1;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		{
			if (s->flag.POS)
			{
				write(1 , "double pos\n", 11);
				exit(1);
			}
			s->posX = index + 1;
			s->posY = i + 1;
			s->flag.POS = 1;
			s->map[index][i] = 0;
		}
		i++;
	}
	while (i < s->map_width)
	{
		s->map[index][i] = -1;
		i++;
	}
	return (0);
}

void	test(t_all *s)
{
	int i;
	int fd;
	int size;
	int count;
	int height;
	char *line;

	size = 1;
	count = 0;
	height = 0;
	fd = open("test.cub", O_RDONLY);
	while ((gnl(fd, &line)))
	{
		if (check_flag(s))
			break ;
		check_line(s, line);
		printf("%s\n", line);
		count++;
	}
	while (size > 0)
	{
		size = gnl(fd, &line);
		printf("%s\n", line);
		if (check_map(s, line))
			break ;
		height++;
	}
	s->map_height = height;
	close(fd);
	s->map = (int**)malloc(sizeof(int*) * height);
	fd = open("test.cub", O_RDONLY);
	i = 0;
	while (count > 0)
	{
		gnl(fd, &line);
		count--;
	}
	size = 1;
	while (size > 0)
	{
		size = gnl(fd, &line);
		printf("%s\n", line);
		if (build_map(s, line, i))
			break ;
		i++;
	}

	printf("posX -> %f\nposY -> %f\n", s->posX, s->posY);
	int ii;
	int jj;
	ii = 0;
	while (ii < s->map_height)
	{
		jj = 0;
		while (jj < s->map_width)
		{
			printf("%2d ", s->map[ii][jj]);
			jj++;
		}
		printf("\n");
		ii++;
	}
	printf("map_width -> %d\n", s->map_width);
}

void	all_init(t_all *s)
{
	s->mlx = mlx_init();
	s->flag.R = 0;
	s->flag.NO = 0;
	s->flag.SO = 0;
	s->flag.WE = 0;
	s->flag.EA = 0;
	s->flag.F = 0;
	s->flag.C = 0;
	// s->F.S = 0;
	s->flag.POS = 0;
	test(s);
	s->win = mlx_new_window(s->mlx, s->screenWidth, s->screenHeight, "cub3D");
	s->img = mlx_new_image(s->mlx, s->screenWidth, s->screenHeight);
	s->addr = mlx_get_data_addr(s->img, &s->bpp, &s->line_len, &s->endian);
	s->dirX = -1;
	s->dirY = 0;
	s->planeX = 0;
	s->planeY = 0.66;
	s->time = 0;
	s->oldTime = 0;
	s->moveSpeed = 0.6;
	s->rotSpeed = 0.08;
	s->tex_N.addr = mlx_get_data_addr(s->tex_N.img, &s->tex_N.bpp, &s->tex_N.line_len, &s->tex_N.endian);
	s->tex_S.addr = mlx_get_data_addr(s->tex_S.img, &s->tex_S.bpp, &s->tex_S.line_len, &s->tex_S.endian);
	s->tex_E.addr = mlx_get_data_addr(s->tex_E.img, &s->tex_E.bpp, &s->tex_E.line_len, &s->tex_E.endian);
	s->tex_W.addr = mlx_get_data_addr(s->tex_W.img, &s->tex_W.bpp, &s->tex_W.line_len, &s->tex_W.endian);
}

int	put_pixel(int keycode, t_all *s)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(s->mlx, s->win);
		exit(0);
	}
	else if (keycode == KEY_W)
	{
		if(worldMap[(int)(s->posX + s->dirX * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX += s->dirX * s->moveSpeed;
		if(worldMap[(int)(s->posX)][(int)(s->posY + s->dirY * s->moveSpeed)] == 0)
			s->posY += s->dirY * s->moveSpeed;
	}
	else if (keycode == KEY_S)
	{
		if(worldMap[(int)(s->posX - s->dirX * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX -= s->dirX * s->moveSpeed;
		if(worldMap[(int)(s->posX)][(int)(s->posY - s->dirY * s->moveSpeed)] == 0)
			s->posY -= s->dirY * s->moveSpeed;
	}
	else if (keycode == KEY_D)
	{
		if(worldMap[(int)(s->posX + s->dirY * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX += s->dirY * s->moveSpeed;
		if(worldMap[(int)(s->posX)][(int)(s->posY - s->dirX * s->moveSpeed)] == 0)
			s->posY -= s->dirX * s->moveSpeed;
	}
	else if (keycode == KEY_A)
	{
		if(worldMap[(int)(s->posX - s->dirY * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX -= s->dirY * s->moveSpeed;
		if(worldMap[(int)(s->posX)][(int)(s->posY + s->dirX * s->moveSpeed)] == 0)
			s->posY += s->dirX * s->moveSpeed;
	}
	else if (keycode == RIGHT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(-(s->rotSpeed)) - s->dirY * sin(-(s->rotSpeed));
		s->dirY = s->oldDirX * sin(-(s->rotSpeed)) + s->dirY * cos(-(s->rotSpeed));
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(-(s->rotSpeed)) - s->planeY * sin(-(s->rotSpeed));
		s->planeY = s->oldPlaneX * sin(-(s->rotSpeed)) + s->planeY * cos(-(s->rotSpeed));
	}
	else if(keycode == LEFT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(s->rotSpeed) - s->dirY * sin(s->rotSpeed);
		s->dirY = s->oldDirX * sin(s->rotSpeed) + s->dirY * cos(s->rotSpeed);
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(s->rotSpeed) - s->planeY * sin(s->rotSpeed);
		s->planeY = s->oldPlaneX * sin(s->rotSpeed) + s->planeY * cos(s->rotSpeed);
	}

	while (x < s->screenWidth)
	{
		double cameraX = 2 * x / (double)s->screenWidth - 1;
		double rayDirX = s->dirX + s->planeX * cameraX;
		double rayDirY = s->dirY + s->planeY * cameraX;
		
		int mapX = (int)(s->posX);
		int mapY = (int)(s->posY);

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
			sideDistX = (s->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - s->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (s->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - s->posY) * deltaDistY;
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
			perpWallDist = (mapX - s->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - s->posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(s->screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + s->screenHeight / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + s->screenHeight / 2;
		if(drawEnd >= s->screenHeight)
			drawEnd = s->screenHeight - 1;

		double wallX;
		if(side == 0)
			wallX = s->posY + perpWallDist * rayDirY;
		else
			wallX = s->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - s->screenHeight / 2 + lineHeight / 2) * step;

		y = 0;
		while (y < s->screenHeight)
		{
			if (y >= drawStart && y <= drawEnd)
			{
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				if (side == 1 && rayDirY >= 0)
					my_mlx_pixel_put2(s, x, y, &s->tex_N, texX, texY);
				else if (side == 1)
					my_mlx_pixel_put2(s, x, y, &s->tex_S, texX, texY);
				else if (rayDirX >= 0)
					my_mlx_pixel_put2(s, x, y, &s->tex_E, texX, texY);
				else
					my_mlx_pixel_put2(s, x, y, &s->tex_W, texX, texY);
			}
			else if (y < (s->screenHeight / 2))
				my_mlx_pixel_put(s, x, y, s->ceiling_color);
			else
				my_mlx_pixel_put(s, x, y, s->floor_color);
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

	all_init(&s);
	mlx_hook(s.win, 2, 0, put_pixel, &s);
	mlx_loop(s.mlx);
	return (0);
}
