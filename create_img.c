/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:54:35 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/02 21:20:45 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_map_area(t_all *s, int x, int y, int n, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
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

// void	put_map(t_all *s)
// {
// 	int		x;
// 	int		y;
// 	double	tmp_x;
// 	double	tmp_y;

// 	y = 0;
// 	while (y < (s->screen_h / 8))
// 	{
// 		x = 0;
// 		tmp_y = ((double)y / ((double)s->screen_h / 8));
// 		while (x < (s->screen_w / 6))
// 		{
// 			tmp_x = ((double)x / ((double)s->screen_w / 6));
// 			if (s->map[(int)((s->map_height - 1) * tmp_y)][(int)((s->map_width - 1) * tmp_x)] == 1)
// 				my_mlx_pixel_put(s, x, y, 0x000000);
// 			else if ((int)s->pos_x == (int)((s->map_height - 1) * tmp_y) && (int)s->pos_y == (int)((s->map_width - 1) * tmp_x))
// 				my_mlx_pixel_put(s, x, y, 0xff0000);
// 			else
// 				my_mlx_pixel_put(s, x, y, 0xffffff);

// 			x += 1;
// 		}
// 		y += 1;
// 	}
// }

void	put_map(t_all *s)
{
	int		x;
	int		y;
	// double	tmp_x;
	// double	tmp_y;
	int		i;
	int		j;
	int		low;

	if (s->map_height < s->map_width)
		low = (s->screen_h / 8) / s->map_height + 1;
	else
		low = (s->screen_w / 8) / s->map_width + 1;
	if (s->screen_w == 0 || s->screen_h == 0)
		low = 0;
	printf("low -> %d\n", low);
	// y = 0;
	// while (y < (s->screen_h / 8))
	// {
	// 	x = 0;
	// 	// tmp_y = ((double)y / ((double)s->screen_h / 8));
	// 	while (x < (s->screen_w / 8))
	// 	{
	// 		// tmp_x = ((double)x / ((double)s->screen_w / 6));
	// 		// if (s->map[(int)((s->map_height - 1) * tmp_y)][(int)((s->map_width - 1) * tmp_x)] == 1)
	// 		// 	my_mlx_pixel_put(s, x, y, 0x000000);
	// 		// else if ((int)s->pos_x == (int)((s->map_height - 1) * tmp_y) && (int)s->pos_y == (int)((s->map_width - 1) * tmp_x))
	// 		// 	my_mlx_pixel_put(s, x, y, 0xff0000);
	// 		// else
	// 			my_mlx_pixel_put(s, x, y, 0xffffff);

	// 		x += 1;
	// 	}
	// 	y += 1;
	// }

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (j < s->map_height)
	{
		x = 0;
		i = 0;
		while (i < s->map_width)
		{
			if (s->map[j][i] == 1)
				put_map_area(s, x, y, low, 0);
			else if ((int)s->pos_x == j && (int)s->pos_y == i)
				put_map_area(s, x, y, low, 1);
			x += low;
			i++;
		}
		y += low;
		j++;
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
