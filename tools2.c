/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:23:37 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/21 22:58:33 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] != ' ')
			return (&line[*i]);
		*i += 1;
	}
	return (NULL);
}

int		check_flag(t_all *s)
{
	if (s->flag.f && s->flag.c && s->flag.r && s->flag.no && \
		s->flag.so && s->flag.we && s->flag.ea && s->flag.s)
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_all *s, int x, int y, int color)
{
	char	*dst;

	dst = s->img.addr + (y * s->img.line_len + x * (s->img.bpp / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_all *s, int x, int y, t_tex *tex)
{
	char			*dst;
	unsigned int	color;

	dst = s->img.addr + (y * s->img.line_len + x * (s->img.bpp / 8));
	color = *(unsigned int*)\
	(tex->addr + (s->tex_y * tex->line_len + s->tex_x * (tex->bpp / 8)));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put3(t_all *s, int x, int y, t_tex *tex)
{
	char			*dst;
	unsigned int	color;

	dst = s->img.addr + (y * s->img.line_len + x * (s->img.bpp / 8));
	color = *(unsigned int*)\
	(tex->addr + (s->tex_y * tex->line_len + s->tex_x * (tex->bpp / 8)));
	if (color == 0)
		return ;
	*(unsigned int*)dst = color;
}
