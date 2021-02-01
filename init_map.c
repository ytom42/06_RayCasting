/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:11:09 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/01 12:41:41 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_all *s)
{
	if (!(s->sprites = (t_sprite*)malloc(sizeof(t_sprite) * \
						(s->sprite_len + 1))))
		end(s, 17, -1);
	if (!(s->spriteorder = (int*)malloc(sizeof(int) * (s->sprite_len + 1))))
		end(s, 17, -1);
	if (!(s->spritedistance = (double*)malloc(sizeof(double) * \
						(s->sprite_len + 1))))
		end(s, 17, -1);
}

void	filename_check(t_all *s)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s->file_name);
	if (len < 5)
		end(s, 18, -1);
	if (s->file_name[len - 1] != 'b')
		end(s, 18, -1);
	if (s->file_name[len - 2] != 'u')
		end(s, 18, -1);
	if (s->file_name[len - 3] != 'c')
		end(s, 18, -1);
	if (s->file_name[len - 4] != '.')
		end(s, 18, -1);
}

void	init_map(t_all *s)
{
	filename_check(s);
	first_read(s);
	init_sprite(s);
	second_read(s);
	check_map(s);
}
