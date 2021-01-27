/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 01:02:33 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/23 14:30:54 by ytomiyos         ###   ########.fr       */
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
			end(s, 4);
		i++;
	}
	return (i);
}

int		build_map(t_all *s, char *line, int index)
{
	int			i;
	int			len;
	static int	sprite_i;

	// printf("--start-- build_map\n");
	i = 0;
	len = ft_strlen(line);
	if (len < 3)
		return (1);
	i = building(s, line, index, &sprite_i);
	while (i < s->map_width)
	{
		s->map[index][i] = -1;
		i++;
	}
	return (0);
}

void	second_read(t_all *s, int *before_line)
{
	int		i;
	int		fd;
	int		index;
	char	*line;

	i = 0;
	fd = open(CUB, O_RDONLY);
	index = 0;
	while (*before_line > 0)
	{
		gnl(fd, &line);
		*before_line -= 1;
	}
	s->map = (int**)malloc(sizeof(int*) * (s->map_height + 1));
	while (i < s->map_height)
	{
		s->map[i] = ((int*)malloc(sizeof(int) * (s->map_width + 1)));
		i++;
		gnl(fd, &line);
		if (ft_strlen(line) < 3)
			break ;
		if (build_map(s, line, index))
			break ;
		printf("\tbuild -> %s\n", line);
		index++;
	}
	close(fd);
	
	int x = 0;
	int y = 0;
	printf("\t\t\x1b[32m---------------------\n\x1b[0m");
	while (x < s->map_height)
	{
		y = 0;
		printf("\t\t\x1b[32m|\x1b[0m");
		while (y < s->map_width)
		{
			printf("%d", s->map[x][y]);
			y++;
		}
		printf("\x1b[32m|\x1b[0m");
		printf("\n");
		x++;
	}
	printf("\t\t\x1b[32m---------------------\n\x1b[0m");
	printf("\t\x1b[32mdone!! second_read\n\x1b[0m");
}
