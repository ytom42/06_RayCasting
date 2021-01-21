/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 01:00:45 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/21 23:07:12 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_line(t_all *s, char *line, int index)
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
		{
			s->pos_x = index + 0.5;
			s->pos_y = i + 0.5;
			s->dir_x = -1;
			s->dir_y = 0;
			s->plane_x = 0;
			s->plane_y = 0.66;
			s->flag.pos = 1;
		}
		else if (line[i] == 'S')
		{
			s->pos_x = index + 0.5;
			s->pos_y = i + 0.5;
			s->dir_x = 1;
			s->dir_y = 0;
			s->plane_x = 0;
			s->plane_y = -0.66;
			s->flag.pos = 1;
		}
		else if (line[i] == 'W')
		{
			s->pos_x = index + 0.5;
			s->pos_y = i + 0.5;
			s->dir_x = 0;
			s->dir_y = -1;
			s->plane_x = -0.66;
			s->plane_y = 0;
			s->flag.pos = 1;
		}
		else if (line[i] == 'E')
		{
			s->pos_x = index + 0.5;
			s->pos_y = i + 0.5;
			s->dir_x = 0;
			s->dir_y = 1;
			s->plane_x = 0.66;
			s->plane_y = 0;
			s->flag.pos = 1;
		}
		i++;
	}
	return (0);
}

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

void	first_read(t_all *s, int *before_line, int *map_height)
{
	int		fd;
	int		index;
	char	*line;

	fd = open(CUB, O_RDONLY);
	while ((gnl(fd, &line)))
	{
		printf("\t1:line-> %s\n", line);
		*before_line += 1;
		read_line(s, line);
		if (check_flag(s))
			break ;
	}
	index = 0;
	while ((gnl(fd, &line)))
	{
		printf("\t2:line-> %s\n", line);
		if (ft_strlen(line) < 3)
			continue ;
		if (check_line(s, line, index))
			break ;
		*map_height += 1;
		index++;
	}
	s->map_height = *map_height;
	close(fd);
	if (!(check_flag(s)))
		end(s, 2);
	if (s->flag.pos == 0)
		end(s, 3);
	printf("\tR  = %d\n", s->flag.r);
	printf("\tNO = %d\n", s->flag.no);
	printf("\tSO = %d\n", s->flag.so);
	printf("\tWE = %d\n", s->flag.we);
	printf("\tEA = %d\n", s->flag.ea);
	printf("\tS  = %d\n", s->flag.s);
	printf("\tF  = %d\n", s->flag.f);
	printf("\tC  = %d\n", s->flag.c);
	printf("\tPOS= %d\n", s->flag.pos);
	printf("\ts->pos_x -> %f\n", s->pos_x);
	printf("\ts->pos_y -> %f\n", s->pos_y);
	printf("\ts->map_height -> %d\n", s->map_height);
	printf("\ts->map_width  -> %d\n", s->map_width);
	printf("\ts->sprite_len -> %d\n", s->sprite_len);
	printf("\t\x1b[31mdone!! first_read\n\x1b[0m");
}
