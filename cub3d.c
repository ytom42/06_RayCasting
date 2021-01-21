/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:30:01 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/20 22:28:52 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		put_img(t_all *s)
{
	put_wall(s);
	put_sprite(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
	return (0);
}

int		check_name(char *name)
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

int		main(int ac, char **av)
{
	t_all	s;

	init_all(&s);
	if (ac == 2 && check_name(av[1]))
	{
		put_wall(&s);
		put_sprite(&s);
		create_bmp(&s);
	}
	else
	{
		s.win = mlx_new_window(s.mlx, s.screenWidth, s.screenHeight, "cub3D");
		put_img(&s);
		mlx_hook(s.win, 2, 0, check_key, &s);
		mlx_loop(s.mlx);
	}
	return (0);
}
