/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 03:16:44 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/19 15:15:57 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall_1(t_all *s)
{
	if (s->rayDirX < 0)
	{
		s->stepX = -1;
		s->sideDistX = (s->posX - s->mapX) * s->deltaDistX;
	}
	else
	{
		s->stepX = 1;
		s->sideDistX = (s->mapX + 1.0 - s->posX) * s->deltaDistX;
	}
	if (s->rayDirY < 0)
	{
		s->stepY = -1;
		s->sideDistY = (s->posY - s->mapY) * s->deltaDistY;
	}
	else
	{
		s->stepY = 1;
		s->sideDistY = (s->mapY + 1.0 - s->posY) * s->deltaDistY;
	}
}

void	put_wall_2(t_all *s)
{
	while (s->hit == 0)
	{
		if (s->sideDistX < s->sideDistY)
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
		if (s->map[s->mapX][s->mapY] == 1)
			s->hit = 1;
	}
	if (s->side == 0)
		s->perpWallDist = (s->mapX - s->posX + (1 - s->stepX) / 2) / s->rayDirX;
	else
		s->perpWallDist = (s->mapY - s->posY + (1 - s->stepY) / 2) / s->rayDirY;
}

void	put_wall_3(t_all *s)
{
	s->lineHeight = (int)(s->screenHeight / s->perpWallDist);
	s->drawStart = -(s->lineHeight) / 2 + s->screenHeight / 2;
	if (s->drawStart < 0)
		s->drawStart = 0;
	s->drawEnd = s->lineHeight / 2 + s->screenHeight / 2;
	if (s->drawEnd >= s->screenHeight)
		s->drawEnd = s->screenHeight - 1;
	if (s->side == 0)
		s->wallX = s->posY + s->perpWallDist * s->rayDirY;
	else
		s->wallX = s->posX + s->perpWallDist * s->rayDirX;
	s->wallX -= floor(s->wallX);
	s->texX = (int)(s->wallX * (double)(texWidth));
	if (s->side == 0 && s->rayDirX > 0)
		s->texX = texWidth - s->texX - 1;
	if (s->side == 1 && s->rayDirY < 0)
		s->texX = texWidth - s->texX - 1;
	s->step = 1.0 * texHeight / s->lineHeight;
	s->texPos = (s->drawStart - s->screenHeight / 2 + s->lineHeight / 2) * s->step;
}

void	put_wall_init(t_all *s, int x)
{
	s->cameraX = 2 * x / (double)s->screenWidth - 1;
	s->rayDirX = s->dirX + s->planeX * s->cameraX;
	s->rayDirY = s->dirY + s->planeY * s->cameraX;
	s->mapX = (int)(s->posX);
	s->mapY = (int)(s->posY);
	s->deltaDistX = fabs(1 / s->rayDirX);
	s->deltaDistY = fabs(1 / s->rayDirY);
	s->hit = 0;
}

void	put_wall_pixelput(t_all *s, int x)
{
	int		y;

	y = 0;
	while (y < s->screenHeight)
	{
		if (y >= s->drawStart && y <= s->drawEnd)
		{
			s->texY = (int)s->texPos & (texHeight - 1);
			s->texPos += s->step;
			if (s->side == 1 && s->rayDirY >= 0)
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_N);
			else if (s->side == 1)
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_S);
			else if (s->rayDirX >= 0)
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_E);
			else
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_W);
		}
		else if (y < (s->screenHeight / 2))
			my_mlx_pixel_put(s, x, y, s->ceiling_color);
		else
			my_mlx_pixel_put(s, x, y, s->floor_color);
		y++;
	}
	s->buf.ZBuffer[x] = s->perpWallDist;
}

void	put_wall(t_all *s)
{
	int x;

	x = 0;
	while (x < s->screenWidth)
	{
		put_wall_init(s, x);
		put_wall_1(s);
		put_wall_2(s);
		put_wall_3(s);
		put_wall_pixelput(s, x);
		x++;
	}
}
