/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 03:16:44 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/21 23:14:48 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall_1(t_all *s)
{
	if (s->raydir_x < 0)
	{
		s->step_x = -1;
		s->sidedist_x = (s->pos_x - s->map_x) * s->deltadist_x;
	}
	else
	{
		s->step_x = 1;
		s->sidedist_x = (s->map_x + 1.0 - s->pos_x) * s->deltadist_x;
	}
	if (s->raydir_y < 0)
	{
		s->step_y = -1;
		s->sidedist_y = (s->pos_y - s->map_y) * s->deltadist_y;
	}
	else
	{
		s->step_y = 1;
		s->sidedist_y = (s->map_y + 1.0 - s->pos_y) * s->deltadist_y;
	}
}

void	put_wall_2(t_all *s)
{
	while (s->hit == 0)
	{
		if (s->sidedist_x < s->sidedist_y)
		{
			s->sidedist_x += s->deltadist_x;
			s->map_x += s->step_x;
			s->side = 0;
		}
		else
		{
			s->sidedist_y += s->deltadist_y;
			s->map_y += s->step_y;
			s->side = 1;
		}
		if (s->map[s->map_x][s->map_y] == 1)
			s->hit = 1;
	}
	if (s->side == 0)
		s->perpwalldist = (s->map_x - s->pos_x + (1 - s->step_x) / 2) / s->raydir_x;
	else
		s->perpwalldist = (s->map_y - s->pos_y + (1 - s->step_y) / 2) / s->raydir_y;
}

void	put_wall_3(t_all *s)
{
	s->line_h = (int)(s->screen_h / s->perpwalldist);
	s->drawstart = -(s->line_h) / 2 + s->screen_h / 2;
	if (s->drawstart < 0)
		s->drawstart = 0;
	s->drawend = s->line_h / 2 + s->screen_h / 2;
	if (s->drawend >= s->screen_h)
		s->drawend = s->screen_h - 1;
	if (s->side == 0)
		s->wall_x = s->pos_y + s->perpwalldist * s->raydir_y;
	else
		s->wall_x = s->pos_x + s->perpwalldist * s->raydir_x;
	s->wall_x -= floor(s->wall_x);
	s->tex_x = (int)(s->wall_x * (double)(TEX_WIDTH));
	if (s->side == 0 && s->raydir_x > 0)
		s->tex_x = TEX_WIDTH - s->tex_x - 1;
	if (s->side == 1 && s->raydir_y < 0)
		s->tex_x = TEX_WIDTH - s->tex_x - 1;
	s->step = 1.0 * TEX_HEIGHT / s->line_h;
	s->texpos = (s->drawstart - s->screen_h / 2 + s->line_h / 2) * s->step;
}

void	put_wall_init(t_all *s, int x)
{
	s->camera_x = 2 * x / (double)s->screen_w - 1;
	s->raydir_x = s->dir_x + s->plane_x * s->camera_x;
	s->raydir_y = s->dir_y + s->plane_y * s->camera_x;
	s->map_x = (int)(s->pos_x);
	s->map_y = (int)(s->pos_y);
	s->deltadist_x = fabs(1 / s->raydir_x);
	s->deltadist_y = fabs(1 / s->raydir_y);
	s->hit = 0;
}

void	put_wall_pixelput(t_all *s, int x)
{
	int		y;

	y = 0;
	while (y < s->screen_h)
	{
		if (y >= s->drawstart && y <= s->drawend)
		{
			s->tex_y = (int)s->texpos & (TEX_HEIGHT - 1);
			s->texpos += s->step;
			if (s->side == 1 && s->raydir_y >= 0)
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_n);
			else if (s->side == 1)
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_s);
			else if (s->raydir_x >= 0)
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_e);
			else
				my_mlx_pixel_put2(s, x, y, &s->texs.tex_w);
		}
		else if (y < (s->screen_h / 2))
			my_mlx_pixel_put(s, x, y, s->ceiling_color);
		else
			my_mlx_pixel_put(s, x, y, s->floor_color);
		y++;
	}
	s->buf.z_buffer[x] = s->perpwalldist;
}

void	put_wall(t_all *s)
{
	int x;

	x = 0;
	while (x < s->screen_w)
	{
		put_wall_init(s, x);
		put_wall_1(s);
		put_wall_2(s);
		put_wall_3(s);
		put_wall_pixelput(s, x);
		x++;
	}
}
