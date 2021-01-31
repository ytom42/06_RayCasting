/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 00:37:11 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/31 00:50:13 by ytomiyos         ###   ########.fr       */
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

void	check_line(t_all *s, char *line, int index)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	if (s->map_width < len)
		s->map_width = len;
	while (line[i])
	{
		if (line[i] == '2')
			s->sprite_len += 1;
		else if (line[i] == 'N')
			player_n(s, index, &i);
		else if (line[i] == 'S')
			player_s(s, index, &i);
		else if (line[i] == 'W')
			player_w(s, index, &i);
		else if (line[i] == 'E')
			player_e(s, index, &i);
		else if (line[i] == ' ' && ++i)
			continue ;
		else if (line[i] != '1' && line[i] != '0')
			end(s, 5, -1);
		i++;
	}
}
