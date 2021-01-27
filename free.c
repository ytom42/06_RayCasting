/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:57:38 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/26 14:43:03 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_all *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < s->screen_h)
	{
		free(s->map[i]);
		i++;
	}
	free(s->map);
}

void	free_fillmap(t_all *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < s->screen_h)
	{
		free(s->fill_map[i]);
		i++;
	}
	free(s->fill_map);
}

void	all_free(t_all *s)
{
	s->screen_w = 0;
	// free(s->sprites);
	// free(s->spriteorder);
	// free(s->spritedistance);
	// free_map(s);
	// free_fillmap(s);
}
