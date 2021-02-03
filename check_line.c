/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 00:37:11 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/03 19:07:46 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_len(t_all *s, char *line)
{
	int		len;

	len = ft_strlen(line);
	if (len > 200)
		end(s, 21, -1);
	if (s->map_width < len)
		s->map_width = len;
}

void	check_line(t_all *s, char *line, int index)
{
	int		i;

	i = 0;
	check_len(s, line);
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
