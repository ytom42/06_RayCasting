/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:30:01 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/13 22:11:47 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void sortSprites(int* order, double* dist, int amount)
{
	int i;
	int flag;
	int i_tmp;
	double d_tmp;

	flag = 1;
	i = 0;
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < (amount-1))
		{
			i_tmp = order[i];
			d_tmp = dist[i];
			if (dist[i] < dist[i+1])
			{
				order[i] = order[i+1];
				dist[i] = dist[i+1];
				order[i+1] = i_tmp;
				dist[i+1] = d_tmp;
				flag = 1;
			}
			i++;
		}
	}
}

int		put_img(t_all *s)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < s->screenWidth)
	{
		s->cameraX = 2 * x / (double)s->screenWidth - 1;
		s->rayDirX = s->dirX + s->planeX * s->cameraX;
		s->rayDirY = s->dirY + s->planeY * s->cameraX;

		s->mapX = (int)(s->posX);
		s->mapY = (int)(s->posY);

		s->deltaDistX = fabs(1 / s->rayDirX);
		s->deltaDistY = fabs(1 / s->rayDirY);

		s->hit = 0;

		if(s->rayDirX < 0)
		{
			s->stepX = -1;
			s->sideDistX = (s->posX - s->mapX) * s->deltaDistX;
		}
		else
		{
			s->stepX = 1;
			s->sideDistX = (s->mapX + 1.0 - s->posX) * s->deltaDistX;
		}
		if(s->rayDirY < 0)
		{
			s->stepY = -1;
			s->sideDistY = (s->posY - s->mapY) * s->deltaDistY;
		}
		else
		{
			s->stepY = 1;
			s->sideDistY = (s->mapY + 1.0 - s->posY) * s->deltaDistY;
		}
		while (s->hit == 0)
		{
			if(s->sideDistX < s->sideDistY)
			{
				s->sideDistX += s->deltaDistX;
				s->mapX += s->stepX;
				s->side = 0;
			}
			else
			{
				s->sideDistY += s->deltaDistY;
				s->mapY += s->stepY;
				s->side = 1;
			}
			if(s->map[s->mapX][s->mapY] == 1)
				s->hit = 1;
		}
		if(s->side == 0)
			s->perpWallDist = (s->mapX - s->posX + (1 - s->stepX) / 2) / s->rayDirX;
		else
			s->perpWallDist = (s->mapY - s->posY + (1 - s->stepY) / 2) / s->rayDirY;

		s->lineHeight = (int)(s->screenHeight / s->perpWallDist);

		s->drawStart = -(s->lineHeight) / 2 + s->screenHeight / 2;
		if(s->drawStart < 0)
			s->drawStart = 0;
		s->drawEnd = s->lineHeight / 2 + s->screenHeight / 2;
		if(s->drawEnd >= s->screenHeight)
			s->drawEnd = s->screenHeight - 1;

		if(s->side == 0)
			s->wallX = s->posY + s->perpWallDist * s->rayDirY;
		else
			s->wallX = s->posX + s->perpWallDist * s->rayDirX;
		s->wallX -= floor(s->wallX);

		s->texX = (int)(s->wallX * (double)(texWidth));
		if(s->side == 0 && s->rayDirX > 0)
			s->texX = texWidth - s->texX - 1;
		if(s->side == 1 && s->rayDirY < 0)
			s->texX = texWidth - s->texX - 1;

		s->step = 1.0 * texHeight / s->lineHeight;
		s->texPos = (s->drawStart - s->screenHeight / 2 + s->lineHeight / 2) * s->step;

		y = 0;
		while (y < s->screenHeight)
		{
			if (y >= s->drawStart && y <= s->drawEnd)
			{
				s->texY = (int)s->texPos & (texHeight - 1);
				s->texPos += s->step;
				if (s->side == 1 && s->rayDirY >= 0)
					my_mlx_pixel_put2(s, x, y, &s->tex_N);
				else if (s->side == 1)
					my_mlx_pixel_put2(s, x, y, &s->tex_S);
				else if (s->rayDirX >= 0)
					my_mlx_pixel_put2(s, x, y, &s->tex_E);
				else
					my_mlx_pixel_put2(s, x, y, &s->tex_W);
			}
			else if (y < (s->screenHeight / 2))
				my_mlx_pixel_put(s, x, y, s->ceiling_color);
			else
				my_mlx_pixel_put(s, x, y, s->floor_color);
			y++;
		}
		s->buf.ZBuffer[x] = s->perpWallDist;
		x++;
	}

	for(int i = 0; i < s->sprite_len; i++)
	{
		s->spriteOrder[i] = i;
		s->spriteDistance[i] = ((s->posX - s->sprites[i].x) * (s->posX - s->sprites[i].x) + (s->posY - s->sprites[i].y) * (s->posY - s->sprites[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(s->spriteOrder, s->spriteDistance, s->sprite_len);
	for(int i = 0; i < s->sprite_len; i++)
	{
		double spriteX = s->sprites[s->spriteOrder[i]].x - s->posX;
		double spriteY = s->sprites[s->spriteOrder[i]].y - s->posY;

		double invDet = 1.0 / (s->planeX * s->dirY - s->dirX * s->planeY);

		double transformX = invDet * (s->dirY * spriteX - s->dirX * spriteY);
		double transformY = invDet * (-(s->planeY) * spriteX + s->planeX * spriteY);
		int spriteScreenX = (int)((s->screenWidth / 2) * (1 + transformX / transformY));

		// #define vMove 0.0
		// int vMoveScreen = (int)(vMove / transformY);
		int spriteHeight = abs((int)(s->screenHeight / (transformY)));
		int drawStartY = (-spriteHeight / 2) + (s->screenHeight / 2);
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = (spriteHeight / 2) + (s->screenHeight / 2);
		if(drawEndY >= s->screenHeight)
			drawEndY = s->screenHeight - 1;

		int spriteWidth = abs((int)(s->screenHeight / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= s->screenWidth)
			drawEndX = s->screenWidth - 1;

		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			s->texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < s->screenWidth && transformY < s->buf.ZBuffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++)
				{
					int d = y * 256 - s->screenHeight * 128 + spriteHeight * 128;
					s->texY = ((d * texHeight) / spriteHeight) / 256;
					my_mlx_pixel_put3(s, stripe, y, &s->tex_SP);
				}
			}
		}
	}
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
	return (0);
}

void	move_pos(t_all *s, int key)
{
	if (key == KEY_W)
	{
		if(s->map[(int)(s->posX + s->dirX * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX += s->dirX * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY + s->dirY * s->moveSpeed)] == 0)
			s->posY += s->dirY * s->moveSpeed;
	}
	else if (key == KEY_S)
	{
		if(s->map[(int)(s->posX - s->dirX * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX -= s->dirX * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY - s->dirY * s->moveSpeed)] == 0)
			s->posY -= s->dirY * s->moveSpeed;
	}
	else if (key == KEY_D)
	{
		if(s->map[(int)(s->posX + s->dirY * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX += s->dirY * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY - s->dirX * s->moveSpeed)] == 0)
			s->posY -= s->dirX * s->moveSpeed;
	}
	else if (key == KEY_A)
	{
		if(s->map[(int)(s->posX - s->dirY * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX -= s->dirY * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY + s->dirX * s->moveSpeed)] == 0)
			s->posY += s->dirX * s->moveSpeed;
	}
}

void	turn_RL(t_all *s, int key)
{
	if (key == RIGHT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(-(s->rotSpeed)) - s->dirY * sin(-(s->rotSpeed));
		s->dirY = s->oldDirX * sin(-(s->rotSpeed)) + s->dirY * cos(-(s->rotSpeed));
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(-(s->rotSpeed)) - s->planeY * sin(-(s->rotSpeed));
		s->planeY = s->oldPlaneX * sin(-(s->rotSpeed)) + s->planeY * cos(-(s->rotSpeed));
	}
	else if(key == LEFT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(s->rotSpeed) - s->dirY * sin(s->rotSpeed);
		s->dirY = s->oldDirX * sin(s->rotSpeed) + s->dirY * cos(s->rotSpeed);
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(s->rotSpeed) - s->planeY * sin(s->rotSpeed);
		s->planeY = s->oldPlaneX * sin(s->rotSpeed) + s->planeY * cos(s->rotSpeed);
	}
}

int	check_key(int keycode, t_all *s)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(s->mlx, s->win);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_pos(s, KEY_W);
	else if (keycode == KEY_S)
		move_pos(s, KEY_S);
	else if (keycode == KEY_D)
		move_pos(s, KEY_D);
	else if (keycode == KEY_A)
		move_pos(s, KEY_A);
	else if (keycode == RIGHT)
		turn_RL(s, RIGHT);
	else if(keycode == LEFT)
		turn_RL(s, LEFT);
	put_img(s);
	return (0);
}

int		check_name(char *name)
{
	int		i;
	int		len;
	char	*save;

	i = 0;
	save = "--save";
	len = ft_strlen(name);
	if (len != 6)
		return (0);
	while (name[i])
	{
		if (name[i] != save[i])
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_all	s;

	init_all(&s);
	put_img(&s);
	if (ac == 2 && check_name(av[1]))
		create_bmp(&s);
	mlx_hook(s.win, 2, 0, check_key, &s);
	mlx_loop(s.mlx);
	return (0);
}
