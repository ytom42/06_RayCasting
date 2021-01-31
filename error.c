/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:18:46 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/31 17:47:53 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_1(int n)
{
	if (n == 1)
		write(2, "Map is not closed\n", 18);
	else if (n == 2)
		write(2, "Not enough information\n", 23);
	else if (n == 3)
		write(2, "Player not found\n", 17);
	else if (n == 4)
		write(2, "Map contains incorrect values\n", 30);
	else if (n == 5)
		write(2, "Cubfile contains incorrect values\n", 34);
	else if (n == 6)
		write(2, "Duplicate definitions\n", 22);
	else if (n == 7)
		write(2, "Duplicate players\n", 18);
	else if (n == 8)
		write(2, "Failed to get texture\n", 22);
	else if (n == 9)
		write(2, "Illegal RGB value\n", 18);
	else if (n == 10)
		write(2, "Space after texture file name\n", 30);
}

void	end_2(int n)
{
	if (n == 11)
		write(2, "Do not include line breaks in the map\n", 38);
	else if (n == 12)
		write(2, "The resolution is not the correct value\n", 40);
	else if (n == 13)
		write(2, "Separate floor and ceiling colors with commas\n", 46);
	else if (n == 14)
		write(2, "The format is different\n", 24);
	else if (n == 15)
		write(2, "No newline after block\n", 23);
	else if (n == 16)
		write(2, "The only possible option is \"--save\"\n", 37);
	else if (n == 17)
		write(2, "malloc faild\n", 13);
	else if (n == 18)
		write(2, "Failed to open file\n", 20);
	else if (n == 19)
		write(2, "Texture size should be 64 * 64\n", 31);
}

void	end(t_all *s, int n, int free_n)
{
	if (s->win != NULL)
		mlx_destroy_window(s->mlx, s->win);
	all_free(s, free_n);
	end_1(n);
	end_2(n);
	exit(0);
}

int		close_window(t_all *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
}
