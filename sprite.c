/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:23:06 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/21 22:42:13 by ytomiyos         ###   ########.fr       */
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
		s->spriteorder[i] = i;
		s->spritedistance[i] = ((s->pos_x - s->sprites[i].x) * (s->pos_x - s->sprites[i].x) + (s->pos_y - s->sprites[i].y) * (s->pos_y - s->sprites[i].y));
		i++;
	}
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < (s->sprite_len - 1))
		{
			i_tmp = s->spriteorder[i];
			d_tmp = s->spritedistance[i];
			if (s->spritedistance[i] < s->spritedistance[i+1])
			{
				s->spriteorder[i] = s->spriteorder[i+1];
				s->spritedistance[i] = s->spritedistance[i+1];
				s->spriteorder[i+1] = i_tmp;
				s->spritedistance[i+1] = d_tmp;
				flag = 1;
			}
			i++;
		}
	}
}
