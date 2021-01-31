/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 01:00:45 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/31 01:45:01 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	read_info(t_all *s, int fd)
{
	int		n;
	char	*line;
	char	*tmp;

	while ((n = gnl(fd, &line)) > 0)
	{
		s->map_before_line += 1;
		read_line(s, line);
		tmp = line;
		free(tmp);
		if (check_flag(s))
			break ;
	}
	if (n == 0 && (ft_strlen(line)) != 0)
		end(s, 15, -1);
}

void	read_map(t_all *s, int fd, int *index, char **line)
{
	int		n;
	int		flag;
	char	*tmp;

	flag = 0;
	while ((n = gnl(fd, line)) > 0)
	{
		if (flag == 0 && ((ft_strlen(*line) == 0) || (ft_allspace(*line))))
		{
			tmp = *line;
			free(tmp);
			s->map_before_line += 1;
			continue ;
		}
		flag = 1;
		if (ft_strlen(*line) == 0)
			break ;
		check_line(s, *line, *index);
		tmp = *line;
		free(tmp);
		s->map_height += 1;
		*index += 1;
	}
	if (n == 0 && (ft_strlen(*line)) != 0)
		end(s, 15, -1);
}

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

void	first_read(t_all *s)
{
	int		fd;
	int		index;
	char	*line;
	char	*tmp;

	index = 0;
	if ((fd = open(CUB, O_RDONLY)) == -1)
		end(s, 18, -1);
	read_info(s, fd);
	read_map(s, fd, &index, &line);
	if (!(ft_allspace(line)))
		end(s, 5, -1);
	tmp = line;
	free(tmp);
	read_aftermap(s, fd, &line);
	if (!(ft_allspace(line)))
		end(s, 5, -1);
	if (!(check_flag(s)))
		end(s, 2, -1);
	if (s->flag.pos == 0)
		end(s, 3, -1);
	free(line);
	close(fd);
}
