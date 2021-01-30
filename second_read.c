/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 01:02:33 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 17:43:37 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		building(t_all *s, char *line, int index, int *sprite_i)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			s->map[index][i] = -1;
		else if (line[i] == '0' || line[i] == '1')
			s->map[index][i] = (int)(line[i] - 48);
		else if (line[i] == '2')
		{
			s->sprites[*sprite_i].x = index + 0.5;
			s->sprites[*sprite_i].y = i + 0.5;
			*sprite_i += 1;
			s->map[index][i] = 0;
		}
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			s->map[index][i] = 0;
		else
			end(s, 4, -1);
		i++;
	}
	return (i);
}

int		build_map(t_all *s, char *line, int index)
{
	int			i;
	int			len;
	static int	sprite_i;

	i = 0;
	len = ft_strlen(line);
	i = building(s, line, index, &sprite_i);
	while (i < s->map_width)
	{
		s->map[index][i] = -1;
		i++;
	}
	return (0);
}

void	second_read(t_all *s)
{
	int		i;
	int		fd;
	char	*line;
	char	*tmp;

	i = 0;
	if ((fd = open(CUB, O_RDONLY)) == -1)
		end(s, 18, -1);
	while (s->map_before_line > 0)
	{
		gnl(fd, &line);
		tmp = line;
		free(tmp);
		s->map_before_line -= 1;
	}
	if (!(s->map = (int**)malloc(sizeof(int*) * (s->map_height + 1))))
		end(s, 17, -1);
	while (i < s->map_height)
	{
		if (!(s->map[i] = ((int*)malloc(sizeof(int) * (s->map_width + 1)))))
			end(s, 17, i);
		gnl(fd, &line);
		if (build_map(s, line, i))
			break ;
		tmp = line;
		free(tmp);
		printf("\tbuild -> %s\n", line);
		i++;
	}
	close(fd);
	printf("\t\x1b[32mdone!! second_read\n\x1b[0m");
}
