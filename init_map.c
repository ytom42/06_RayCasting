/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:11:09 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 09:29:00 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_all *s)
{
	if (!(s->sprites = (t_sprite*)malloc(sizeof(t_sprite) * (s->sprite_len + 1))))
		end(s, 17, -1);
	if (!(s->spriteorder = (int*)malloc(sizeof(int) * (s->sprite_len + 1))))
		end(s, 17, -1);
	if (!(s->spritedistance = (double*)malloc(sizeof(double) * (s->sprite_len + 1))))
		end(s, 17, -1);
}

void	init_map(t_all *s)
{
	first_read(s);
	init_sprite(s);
	second_read(s);
	check_map(s);
}