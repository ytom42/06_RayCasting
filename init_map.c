/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:11:09 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/27 21:39:14 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_all *s)
{
	if (!(s->sprites = (t_sprite*)malloc(sizeof(t_sprite) * (s->sprite_len + 1))))
		end(s, 17);
	if (!(s->spriteorder = (int*)malloc(sizeof(int) * (s->sprite_len + 1))))
		end(s, 17);
	if (!(s->spritedistance = (double*)malloc(sizeof(double) * (s->sprite_len + 1))))
		end(s, 17);
}

void	init_map(t_all *s)
{
	int		map_before_line;
	int		map_height;

	map_before_line = 0;
	map_height = 0;
	first_read(s, &map_before_line, &map_height);
	init_sprite(s);
	second_read(s, &map_before_line);
	check_map(s, map_height);
}