/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:57:38 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/21 22:44:08 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end(t_all *s, int n)
{
	printf("-----------\n---error---\n-----------\n");
	// free s->fill_map
	if (n == 1)
		write(2, "Map is not closed\n", 18);
	else if (n == 2)
		write(2, "Not enough information\n", 23);
	else if (n == 3)
		write(2, "Player not found\n", 17);
	s->screen_w = 1;
	exit(0);
}
