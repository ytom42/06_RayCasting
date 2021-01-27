/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubinfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:09:08 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/27 09:57:03 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_resolution(t_all *s, char *line)
{
	int		i;
	int		tmp;

	i = 1;
	if (s->flag.r == 1)
		end(s, 6);
	skip_space(line, &i);
	tmp = ft_atoi_new(line, &i);
	s->screen_w = tmp;
	skip_space(line, &i);
	if (!(ft_isdigit(line[i])))
		end(s, 12);
	tmp = ft_atoi_new(line, &i);
	s->screen_h = tmp;
	if (!(ft_allspace(&line[i])))
		end(s, 12);
	s->flag.r = 1;
}

void	check_filename(t_all *s, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			break ;
		i++;
	}
	while (line[i])
	{
		if (line[i] == ' ')
			end(s, 10);
		i++;
	}
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
		end(s, 6);
	skip_space(line, &i);
	check_filename(s, &line[i]);
	s->texs.tex_sp.img = mlx_xpm_file_to_image(s->mlx, &line[i], &s->texs.tex_sp.width, &s->texs.tex_sp.height);
	if (s->texs.tex_sp.img == NULL)
		end(s, 8);
	s->flag.s = 1;
}

void	init_floor_ceiling(t_all *s, char *line, int n)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 1;
	r = 0;
	g = 0;
	b = 0;
	skip_space(line, &i);
	r = ft_atoi_new(line, &i);
	if (r < 0)
		end(s, 9);
	if (line[i++] != ',')
		end(s, 13);
	if (!(ft_isdigit(line[i])))
		end(s, 14);
	g = ft_atoi_new(line, &i);
	if (line[i++] != ',')
		end(s, 13);
	if (!(ft_isdigit(line[i])))
		end(s, 14);
	b = ft_atoi_new(line, &i);
	if (!(ft_allspace(&line[i])))
		end(s, 5);
	printf("r -> %d\n", r);
	printf("g -> %d\n", g);
	printf("b -> %d\n", b);
	if (n == 0)
	{
		if (s->flag.f == 1)
			end(s, 6);
		s->floor_color = create_rgb(s, r, g, b);
		s->flag.f = 1;
	}
	else if (n == 1)
	{
		if (s->flag.c == 1)
			end(s, 6);
		s->ceiling_color = create_rgb(s, r, g, b);
		s->flag.c = 1;
	}
}
