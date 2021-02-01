/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:23:37 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/01 11:08:30 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_rgb(t_all *s, char *line, int *i)
{
	s->r = ft_atoi_new(line, i);
	if (s->r < 0)
		end(s, 9, -1);
	if (line[*i] != ',')
		end(s, 13, -1);
	*i += 1;
	if (!(ft_isdigit(line[*i])))
		end(s, 14, -1);
	s->g = ft_atoi_new(line, i);
	if (s->g < 0)
		end(s, 9, -1);
	if (line[*i] != ',')
		end(s, 13, -1);
	*i += 1;
	if (!(ft_isdigit(line[*i])))
		end(s, 14, -1);
	s->b = ft_atoi_new(line, i);
	if (s->b < 0)
		end(s, 9, -1);
	if (!(ft_allspace(&line[*i])))
		end(s, 5, -1);
}

void	check_filename(t_all *s, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			break ;
		i++;
	}
	while (line[i])
	{
		if (line[i] == ' ')
			end(s, 10, -1);
		i++;
	}
}

int		ft_ismap(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
			return (1);
		else if (line[i] == '1')
			return (1);
		else if (line[i] == '2')
			return (1);
		else if (line[i] == 'N')
			return (1);
		else if (line[i] == 'S')
			return (1);
		else if (line[i] == 'E')
			return (1);
		else if (line[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

int		check_save(char *name)
{
	int		i;
	int		len;
	char	*save;

	i = 0;
	save = "--save";
	len = ft_strlen(name);
	if (len != 6)
		return (0);
	while (name[i])
	{
		if (name[i] != save[i])
			return (0);
		i++;
	}
	return (1);
}
