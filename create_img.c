/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:54:35 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/25 15:54:53 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_img(t_all *s)
{
	put_wall(s);
	put_sprite(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
	return (0);
}
