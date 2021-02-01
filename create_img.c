/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:54:35 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/01 20:54:00 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_map_area(t_all *s, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if ((int)s->pos_y == (x / 5) && (int)s->pos_x == (y / 5))
				my_mlx_pixel_put(s, (x + i), (y + j), 0xff0000);
			else if (s->map[y / 5][x / 5] == 1)
				my_mlx_pixel_put(s, (x + i), (y + j), 0);
			// else
			// 	my_mlx_pixel_put(s, (x + i), (y + j), 0xffffc5);
			j++;
		}
		i++;
	}
}

void	put_map(t_all *s)
{
	int		x;
	int		y;

	y = 0;
	while (y < (s->map_height * 5))
	{
		x = 0;
		while (x < (s->map_width * 5))
		{
			put_map_area(s, x, y);
			x += 5;
		}
		y += 5;
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
