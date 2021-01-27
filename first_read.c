/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 01:00:45 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/27 00:11:32 by ytomiyos         ###   ########.fr       */
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
			if (s->flag.pos == 1)
				end(s, 7);
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
			if (s->flag.pos == 1)
				end(s, 7);
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
			if (s->flag.pos == 1)
				end(s, 7);
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
			if (s->flag.pos == 1)
				end(s, 7);
			s->pos_x = index + 0.5;
			s->pos_y = i + 0.5;
			s->dir_x = 0;
			s->dir_y = 1;
			s->plane_x = 0.66;
			s->plane_y = 0;
			s->flag.pos = 1;
		}
		else if (line[i] == ' ')
		{
			i++;
			continue ;
		}
		else if (line[i] != '1' && line[i] != '0')
			end(s, 5);
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
	else if (line[i] == '0' || line[i] == '1')
		end(s, 2);
	else
		end(s, 5);
}


void	first_read(t_all *s, int *before_line, int *map_height)
{
	int		n;
	int		fd;
	int		index;
	int		flag;
	char	*line;

	flag = 0;
	fd = open(CUB, O_RDONLY);
	while ((gnl(fd, &line)) >= 0)
	{
		printf("\t1:line-> %s\n", line);
		*before_line += 1;
		read_line(s, line);
		if (check_flag(s))
			break ;
	}
	index = 0;
	while ((n = gnl(fd, &line)) > 0)
	{
		printf("\t2:line-> %s\n", line);
		if (ft_strlen(line) == 0 && flag == 0)
		{
			*before_line += 1;
			continue ;
		}
		if (ft_allspace(line) && flag == 0)
		{
			*before_line += 1;
			continue ;
		}
		flag = 1;
		if (ft_strlen(line) < 3)
			break ;
		if (check_line(s, line, index))
			break ;
		*map_height += 1;
		index++;
	}
	if (n == 0 && (ft_strlen(line)) != 0)
		end(s, 15);
	if (!(ft_allspace(line)))
		end(s, 5);
	while ((gnl(fd, &line)))
	{
		printf("\t3:line-> %s\n", line);
		if (ft_strlen(line) == 0)
			continue ;
		else if (ft_allspace(line))
			continue ;
		else if(ft_ismap(line))
			end(s, 11);
		else
			end(s, 5);
	}
	if (!(ft_allspace(line)))
		end(s, 5);
	s->map_height = *map_height;
	close(fd);
	if (!(check_flag(s)))
		end(s, 2);
	if (s->flag.pos == 0)
		end(s, 3);
	printf("\tscreen_h -> %d\n", s->screen_h);
	printf("\tscreen_w -> %d\n", s->screen_w);
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
	printf("\t\x1b[32mdone!! first_read\n\x1b[0m");
}
