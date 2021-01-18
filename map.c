/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:11:09 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/19 01:33:18 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_all *s)
{
	// 取得失敗時のエラー処理
	s->sprites = (t_sprite*)malloc(sizeof(t_sprite) * (s->sprite_len + 1));
	s->spriteOrder = (int*)malloc(sizeof(int) * (s->sprite_len + 1));
	s->spriteDistance = (double*)malloc(sizeof(double) * (s->sprite_len + 1));
	printf("\t\x1b[31mdone!! init_sprite\n\x1b[0m");
}

void	init_map(t_all *s)
{
	int		before_line;
	int		map_height;

	before_line = 0;
	map_height = 0;
	first_read(s, &before_line, &map_height);
	init_sprite(s);
	second_read(s, &before_line);
	check_map(s, map_height);
}
