/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:27:16 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 19:31:02 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

unsigned long	create_rgb(t_all *s, int r, int g, int b)
{
	if (r < 0 || r > 255)
		end(s, 9, 1);
	else if (g < 0 || g > 255)
		end(s, 9, 1);
	else if (b < 0 || b > 255)
		end(s, 9, 1);
	return (r * 256 * 256 + g * 256 + b);
}

void			my_mlx_pixel_put(t_all *s, int x, int y, int color)
{
	char	*dst;

	dst = s->img.addr + (y * s->img.line_len + x * (s->img.bpp / 8));
	*(unsigned int*)dst = color;
}

void			my_mlx_pixel_put2(t_all *s, int x, int y, t_tex *tex)
{
	char			*dst;
	unsigned int	color;

	dst = s->img.addr + (y * s->img.line_len + x * (s->img.bpp / 8));
	color = *(unsigned int*)\
	(tex->addr + (s->tex_y * tex->line_len + s->tex_x * (tex->bpp / 8)));
	*(unsigned int*)dst = color;
}

void			my_mlx_pixel_put3(t_all *s, int x, int y, t_tex *tex)
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
