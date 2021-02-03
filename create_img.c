/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:54:35 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/03 11:27:23 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_map_area(t_all *s, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < s->low && i < s->screen_h)
	{
		j = 0;
		while (j < s->low && j < s->screen_w)
		{
			if (color == 1)
				my_mlx_pixel_put(s, (x + i), (y + j), 0xff0000);
			else
				my_mlx_pixel_put(s, (x + i), (y + j), 0);
			j++;
		}
		i++;
	}
}

void	put_map(t_all *s)
{
	int		x;
	int		y;
	int		i;
	int		j;

	j = -1;
	y = 0;
	if ((s->screen_h / s->map_height) < (s->screen_w / s->map_width))
		s->low = (s->screen_h / 6) / s->map_height + 1;
	else
		s->low = (s->screen_w / 6) / s->map_width + 1;
	while (++j < s->map_height)
	{
		x = 0;
		i = -1;
		while (++i < s->map_width)
		{
			if (s->map[j][i] == 1)
				put_map_area(s, x, y, 0);
			else if ((int)s->pos_x == j && (int)s->pos_y == i)
				put_map_area(s, x, y, 1);
			x += s->low;
		}
		y += s->low;
	}
}

int		create_img(t_all *s)
{
	put_wall(s);
	put_sprite(s);
	put_map(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
	return (0);
}
