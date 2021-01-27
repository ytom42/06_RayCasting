/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:30:01 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/27 10:42:49 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test(t_all *s)
{
	free(s->mlx);
	end(s, 100);
}

int		main(int ac, char **av)
{
	t_all	s;

	init_all(&s);
	if (ac == 1)
	{
		if (!(s.win = mlx_new_window(s.mlx, s.screen_w, s.screen_h, "cub3D")))
			end(&s, 17);
		create_img(&s);
		mlx_hook(s.win, 2, 0, push_key, &s);
		mlx_hook(s.win, 17, 0, close_window, &s);
		mlx_loop(s.mlx);
	}
	else if (ac == 2 && check_name(av[1]))
	{
		put_wall(&s);
		put_sprite(&s);
		create_bmp(&s);
	}
	else
		end(&s, 16);
	return (0);
}
