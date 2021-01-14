/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:11:09 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/14 11:35:29 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_line(t_all *s, char *line)
{
	int i;

	i = 0;
	skip_space(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		init_resolution(s, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		init_wall(s, line, 0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		init_wall(s, line, 1);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		init_wall(s, line, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		init_wall(s, line, 3);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		init_floor_ceiling(s, line, 0);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		init_floor_ceiling(s, line, 1);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		init_tex(s, line);
	else
		return ;
}

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
		else if (line[i] == 'N')
		{
			s->posX = index + 0.5;
			s->posY = i + 0.5;
			s->flag.POS = 1;
			s->map[index][i] = 0;
			s->dirX = -1;
			s->dirY = 0;
			s->planeX = 0;
			s->planeY = 0.66;
		}
		else if (line[i] == 'S')
		{
			s->posX = index + 0.5;
			s->posY = i + 0.5;
			s->flag.POS = 1;
			s->map[index][i] = 0;
			s->dirX = 1;
			s->dirY = 0;
			s->planeX = 0;
			s->planeY = -0.66;
		}
		else if (line[i] == 'W')
		{
			s->posX = index + 0.5;
			s->posY = i + 0.5;
			s->flag.POS = 1;
			s->map[index][i] = 0;
			s->dirX = 0;
			s->dirY = -1;
			s->planeX = -0.66;
			s->planeY = 0;
		}
		else if (line[i] == 'E')
		{
			s->posX = index + 0.5;
			s->posY = i + 0.5;
			s->flag.POS = 1;
			s->map[index][i] = 0;
			s->dirX = 0;
			s->dirY = 1;
			s->planeX = 0.66;
			s->planeY = 0;
		}
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
	if (len < 3)
		return (1);
	s->map[index] = (int*)malloc(sizeof(int*) * s->map_width);
	i = building(s, line, index, &sprite_i);
	while (i < s->map_width)
	{
		s->map[index][i] = -1;
		i++;
	}
	return (0);
}

void	first_read(t_all *s, int *before_line, int *map_height)
{
	int		fd;
	char	*line;

	fd = open(CUB, O_RDONLY);
	while ((gnl(fd, &line)))
	{
		*before_line += 1;
		read_line(s, line);
		if (check_flag(s))
			break ;
	}
	while (gnl(fd, &line))
	{
		if (ft_strlen(line) < 3)
			continue ;
		if (check_line(s, line))
			break ;
		*map_height += 1;
	}
	s->map_height = *map_height;
	close(fd);
}

void	second_read(t_all *s, int *before_line, int map_height)
{
	int		fd;
	int		index;
	char	*line;

	fd = open(CUB, O_RDONLY);
	index = 0;
	while (*before_line >= 0)
	{
		gnl(fd, &line);
		*before_line -= 1;
	}
	while (map_height)
	{
		gnl(fd, &line);
		if (ft_strlen(line) < 3)
			continue ;
		if (build_map(s, line, index))
			break ;
		printf("build -> %s\n", line);
		index++;
		map_height -= 1;
	}
	close(fd);
}

void	init_map(t_all *s)
{
	int		before_line;
	int		map_height;

	before_line = 0;
	map_height = 0;
	first_read(s, &before_line, &map_height);
	printf("sprites -> %d\n", s->sprite_len);
	init_sprite(s);
	s->map = (int**)malloc(sizeof(int*) * map_height);
	second_read(s, &before_line, map_height);
	check_map(s, map_height);
	int i;
	int j;
	i = 0;
	j = 0;
	while (i < s->map_height)
	{
		j = 0;
		while (j < s->map_width)
		{
			printf("%d", s->fill_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
