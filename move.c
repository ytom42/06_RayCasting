/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 19:07:25 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/03 19:07:53 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_n(t_all *s, int index, int *i)
{
	if (s->flag.pos == 1)
		end(s, 7, -1);
	s->pos_x = index + 0.5;
	s->pos_y = *i + 0.5;
	s->dir_x = -1;
	s->dir_y = 0;
	s->plane_x = 0;
	s->plane_y = 0.66;
	s->flag.pos = 1;
}

void	player_s(t_all *s, int index, int *i)
{
	if (s->flag.pos == 1)
		end(s, 7, -1);
	s->pos_x = index + 0.5;
	s->pos_y = *i + 0.5;
	s->dir_x = 1;
	s->dir_y = 0;
	s->plane_x = 0;
	s->plane_y = -0.66;
	s->flag.pos = 1;
}

void	player_w(t_all *s, int index, int *i)
{
	if (s->flag.pos == 1)
		end(s, 7, -1);
	s->pos_x = index + 0.5;
	s->pos_y = *i + 0.5;
	s->dir_x = 0;
	s->dir_y = -1;
	s->plane_x = -0.66;
	s->plane_y = 0;
	s->flag.pos = 1;
}

void	player_e(t_all *s, int index, int *i)
{
	if (s->flag.pos == 1)
		end(s, 7, -1);
	s->pos_x = index + 0.5;
	s->pos_y = *i + 0.5;
	s->dir_x = 0;
	s->dir_y = 1;
	s->plane_x = 0.66;
	s->plane_y = 0;
	s->flag.pos = 1;
}
