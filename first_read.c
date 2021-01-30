/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 01:00:45 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 09:29:08 by ytomiyos         ###   ########.fr       */
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
				end(s, 7, -1);
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
				end(s, 7, -1);
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
				end(s, 7, -1);
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
				end(s, 7, -1);
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
			end(s, 5, -1);
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
	else
		end(s, 5, -1);
}


void	first_read(t_all *s)
{
	int		n;
	int		fd;
	int		index;
	int		flag;
	char	*line;
	char	*tmp;

	flag = 0;
	if ((fd = open(CUB, O_RDONLY)) == -1)
		end(s, 18, -1);
	while ((n = gnl(fd, &line)) > 0)
	{
		printf("\t1:line-> %s\n", line);
		s->map_before_line += 1;
		read_line(s, line);
		tmp = line;
		free(tmp);
		if (check_flag(s))
			break ;
	}
	if (n == 0 && (ft_strlen(line)) != 0)
		end(s, 15, -1);
	index = 0;
	while ((n = gnl(fd, &line)) > 0)
	{
		printf("\t2:line-> %s\n", line);
		if (ft_strlen(line) == 0 && flag == 0)
		{
			tmp = line;
			free(tmp);
			s->map_before_line += 1;
			continue ;
		}
		if (ft_allspace(line) && flag == 0)
		{
			tmp = line;
			free(tmp);
			s->map_before_line += 1;
			continue ;
		}
		flag = 1;
		if (ft_strlen(line) == 0)
			break ;
		if (check_line(s, line, index))
			break ;
		tmp = line;
		free(tmp);
		s->map_height += 1;
		index++;
	}
	if (n == 0 && (ft_strlen(line)) != 0)
		end(s, 15, -1);
	if (!(ft_allspace(line)))
		end(s, 5, -1);
	tmp = line;
	free(tmp);
	while ((gnl(fd, &line)))
	{
		printf("\t3:line-> %s\n", line);
		if (ft_strlen(line) == 0)
		{
			tmp = line;
			free(tmp);
			continue ;
		}
		else if (ft_allspace(line))
		{
			tmp = line;
			free(tmp);
			continue ;
		}
		else if(ft_ismap(line))
			end(s, 11, -1);
		else
			end(s, 5, -1);
		tmp = line;
		free(tmp);
	}
	close(fd);
	if (!(ft_allspace(line)))
		end(s, 5, -1);
	if (!(check_flag(s)))
		end(s, 2, -1);
	if (s->flag.pos == 0)
		end(s, 3, -1);
	free(line);
	printf("\t\x1b[32mdone!! first_read\n\x1b[0m");
}
