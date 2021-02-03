/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:31:58 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/03 11:15:10 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] != ' ')
			return (&line[*i]);
		*i += 1;
	}
	return (NULL);
}

int		check_flag(t_all *s)
{
	if (s->flag.f && s->flag.c && s->flag.r && s->flag.no && \
		s->flag.so && s->flag.we && s->flag.ea && s->flag.s)
		return (1);
	return (0);
}

int		ft_allspace(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		ft_atoi_rgb(char *str, int *index)
{
	int		n;

	n = 0;
	while (str[*index] >= 48 && str[*index] <= 57)
	{
		if (n > 255)
			return (-1);
		n = n * 10 + (str[*index] - 48);
		*index += 1;
	}
	return (n);
}

int		ft_atoi_new(char *str, int *index)
{
	int		n;
	int		len;

	n = 0;
	len = 1;
	while (str[*index] >= 48 && str[*index] <= 57)
	{
		if (n < 0 || len >= 10)
			return (-1);
		n = n * 10 + (str[*index] - 48);
		*index += 1;
		len++;
	}
	return (n);
}
