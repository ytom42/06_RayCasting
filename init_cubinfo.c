/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubinfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:09:08 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/01 12:23:36 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_resolution(t_all *s, char *line)
{
	int		i;
	int		tmp;

	i = 1;
	if (s->flag.r == 1)
		end(s, 6, -1);
	skip_space(line, &i);
	tmp = ft_atoi_new(line, &i);
	if (tmp < 0 || tmp > 10000)
		end(s, 20, -1);
	s->screen_w = tmp;
	skip_space(line, &i);
	if (!(ft_isdigit(line[i])))
		end(s, 12, -1);
	tmp = ft_atoi_new(line, &i);
	if (tmp < 0 || tmp > 10000)
		end(s, 20, -1);
	s->screen_h = tmp;
	if (!(ft_allspace(&line[i])))
		end(s, 12, -1);
	s->flag.r = 1;
}

void	init_wall(t_all *s, char *line, int n)
{
	int		i;

	i = 2;
	skip_space(line, &i);
	check_filename(s, &line[i]);
	if (n == 0)
		north_tex_to_img(s, &line[i]);
	else if (n == 1)
		south_tex_to_img(s, &line[i]);
	else if (n == 2)
		east_tex_to_img(s, &line[i]);
	else if (n == 3)
		west_tex_to_img(s, &line[i]);
}

void	init_tex(t_all *s, char *line)
{
	int		i;

	i = 1;
	if (s->flag.s == 1)
		end(s, 6, -1);
	skip_space(line, &i);
	check_filename(s, &line[i]);
	s->texs.tex_sp.img = mlx_xpm_file_to_image(s->mlx, \
		&line[i], &s->texs.tex_sp.width, &s->texs.tex_sp.height);
	if (s->texs.tex_sp.img == NULL)
		end(s, 8, -1);
	if (s->texs.tex_sp.width != 64 || s->texs.tex_sp.height != 64)
		end(s, 19, -1);
	s->flag.s = 1;
}

void	init_floor_ceiling(t_all *s, char *line, int n)
{
	int		i;

	i = 1;
	skip_space(line, &i);
	get_rgb(s, line, &i);
	if (n == 0)
	{
		if (s->flag.f == 1)
			end(s, 6, -1);
		s->floor_color = create_rgb(s, s->r, s->g, s->b);
		s->flag.f = 1;
	}
	else if (n == 1)
	{
		if (s->flag.c == 1)
			end(s, 6, -1);
		s->ceiling_color = create_rgb(s, s->r, s->g, s->b);
		s->flag.c = 1;
	}
}
