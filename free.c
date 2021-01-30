/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:57:38 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 17:33:31 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_all *s, int n)
{
	int		i;

	i = 0;
	if (n == -1)
		n = s->map_height;
	printf("in_freemap.\nn = %d\n", n);
	while (i < n)
	{
		printf("map[%d]\n", i);
		free(s->map[i]);
		i++;
	}
	free(s->map);
}

void	free_fillmap(t_all *s, int n)
{
	int		i;

	printf("in_free_fillmap\n");
	i = 0;
	if (n == -1)
		n = s->map_height;
	while (i < n)
	{
		printf("fill_map[%d]\n", i);
		free(s->fill_map[i]);
		i++;
	}
	free(s->fill_map);
}

void	all_free(t_all *s, int n)
{
	if (s->map != NULL)
		free_map(s, n);
	if (s->fill_map != NULL)
		free_fillmap(s, n);
}
