/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:23:06 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/19 01:43:15 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void sort_sprites(t_all *s)
{
	int i;
	int flag;
	int i_tmp;
	double d_tmp;

	flag = 1;
	i = 0;
	while (i < s->sprite_len)
	{
		s->spriteOrder[i] = i;
		s->spriteDistance[i] = ((s->posX - s->sprites[i].x) * (s->posX - s->sprites[i].x) + (s->posY - s->sprites[i].y) * (s->posY - s->sprites[i].y));
		i++;
	}
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < (s->sprite_len - 1))
		{
			i_tmp = s->spriteOrder[i];
			d_tmp = s->spriteDistance[i];
			if (s->spriteDistance[i] < s->spriteDistance[i+1])
			{
				s->spriteOrder[i] = s->spriteOrder[i+1];
				s->spriteDistance[i] = s->spriteDistance[i+1];
				s->spriteOrder[i+1] = i_tmp;
				s->spriteDistance[i+1] = d_tmp;
				flag = 1;
			}
			i++;
		}
	}
}
