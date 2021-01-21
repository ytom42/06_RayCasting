/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:09:08 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/21 23:04:18 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_resolution(t_all *s, char *line)
{
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	line += 1;
	skip_space(line, &i);
	while (line[i] >= '0' && line[i] <= '9')
	{
		tmp = (tmp * 10) + (line[i] - 48);
		i++;
	}
	s->screen_w = tmp;
	tmp = 0;
	skip_space(line, &i);
	while (line[i] >= '0' && line[i] <= '9')
	{
		tmp = (tmp * 10) + (line[i] - 48);
		i++;
	}
	s->screen_h = tmp;
	s->flag.r = 1;
}

void	init_wall(t_all *s, char *line, int n)
{
	int i;

	i = 0;
	line += 2;
	skip_space(line, &i);
	if (n == 0)
	{
		s->texs.tex_n.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->texs.tex_n.width, &s->texs.tex_n.height);
		s->flag.no = 1;
	}
	else if (n == 1)
	{
		s->texs.tex_s.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->texs.tex_s.width, &s->texs.tex_s.height);
		s->flag.so = 1;
	}
	else if (n == 2)
	{
		s->texs.tex_e.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->texs.tex_e.width, &s->texs.tex_e.height);
		s->flag.ea = 1;
	}
	else if (n == 3)
	{
		s->texs.tex_w.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->texs.tex_w.width, &s->texs.tex_w.height);
		s->flag.we = 1;
	}
}

void	init_tex(t_all *s, char *line)
{
	int i;

	i = 0;
	line += 1;
	skip_space(line, &i);
	s->texs.tex_sp.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->texs.tex_sp.width, &s->texs.tex_sp.height);
	s->flag.s = 1;
}

void	init_floor_ceiling(t_all *s, char *line, int n)
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
	skip_space(line, &i);
	if (n == 0)
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			r = (r * 10) + (line[i] - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			g = (g * 10) + (line[i] - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			b = (b * 10) + (line[i] - '0');
			i++;
		}
		s->floor_color = create_rgb(r, g, b);
		s->flag.f = 1;
	}
	else if (n == 1)
	{
		while (line[i] >= '0' && line[i] <= '9')
		{
			r = (r * 10) + (line[i] - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			g = (g * 10) + (line[i] - '0');
			i++;
		}
		i++;
		while (line[i] >= '0' && line[i] <= '9')
		{
			b = (b * 10) + (line[i] - '0');
			i++;
		}
		s->ceiling_color = create_rgb(r, g, b);
		s->flag.c = 1;
	}
}
