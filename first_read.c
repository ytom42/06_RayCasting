/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 01:00:45 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/03 19:23:59 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		before_map(t_all *s, int flag, char *line)
{
	char	*tmp;

	if (flag == 0 && ((ft_strlen(line) == 0) || (ft_allspace(line))))
	{
		tmp = line;
		free(tmp);
		s->map_before_line += 1;
		return (1);
	}
	return (0);
}

void	read_map(t_all *s, int fd, int *index, char **line)
{
	int		n;
	int		flag;
	char	*tmp;

	flag = 0;
	while ((n = gnl(fd, line)) > 0)
	{
		if (before_map(s, flag, *line))
			continue ;
		flag = 1;
		if (ft_strlen(*line) == 0)
			break ;
		check_line(s, *line, *index);
		tmp = *line;
		free(tmp);
		s->map_height += 1;
		if (s->map_height > 200)
			end(s, 21, -1);
		*index += 1;
	}
	if (n == 0 && (ft_strlen(*line)) != 0)
		end(s, 15, -1);
}

void	first_read(t_all *s)
{
	int		fd;
	int		index;
	char	*line;
	char	*tmp;

	index = 0;
	if ((fd = open(s->file_name, O_RDONLY)) == -1)
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
