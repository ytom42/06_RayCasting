/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 19:23:15 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/03 19:24:04 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_aftermap(t_all *s, int fd, char **line)
{
	char	*tmp;

	while ((gnl(fd, line)))
	{
		if (ft_strlen(*line) == 0)
		{
			tmp = *line;
			free(tmp);
			continue ;
		}
		else if (ft_allspace(*line))
		{
			tmp = *line;
			free(tmp);
			continue ;
		}
		else if (ft_ismap(*line))
			end(s, 11, -1);
		else
			end(s, 5, -1);
		tmp = *line;
		free(tmp);
	}
}

void	read_line(t_all *s, char *line)
{
	int	i;

	i = 0;
	skip_space(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		init_resolution(s, &line[i]);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		init_wall(s, &line[i], 0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		init_wall(s, &line[i], 1);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		init_wall(s, &line[i], 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		init_wall(s, &line[i], 3);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		init_floor_ceiling(s, &line[i], 0);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		init_floor_ceiling(s, &line[i], 1);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		init_tex(s, &line[i]);
	else if (ft_strlen(&line[i]) == 0)
		return ;
	else
		end(s, 5, -1);
}
