/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:35:05 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/03 18:50:42 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	push_ws(t_all *s, int key)
{
	if (key == KEY_W)
	{
		if (s->map[(int)(s->pos_x + s->dir_x * \
		s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x += s->dir_x * s->movespeed;
		if (s->map[(int)(s->pos_x)][(int)(s->pos_y + \
		s->dir_y * s->movespeed)] == 0)
			s->pos_y += s->dir_y * s->movespeed;
	}
	else if (key == KEY_S)
	{
		if (s->map[(int)(s->pos_x - s->dir_x * \
		s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x -= s->dir_x * s->movespeed;
		if (s->map[(int)(s->pos_x)][(int)(s->pos_y - \
		s->dir_y * s->movespeed)] == 0)
			s->pos_y -= s->dir_y * s->movespeed;
	}
}

void	push_da(t_all *s, int key)
{
	if (key == KEY_D)
	{
		if (s->map[(int)(s->pos_x + s->dir_y * \
		s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x += s->dir_y * s->movespeed;
		if (s->map[(int)(s->pos_x)][(int)(s->pos_y - \
		s->dir_x * s->movespeed)] == 0)
			s->pos_y -= s->dir_x * s->movespeed;
	}
	else if (key == KEY_A)
	{
		if (s->map[(int)(s->pos_x - s->dir_y * \
		s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x -= s->dir_y * s->movespeed;
		if (s->map[(int)(s->pos_x)][(int)(s->pos_y + \
		s->dir_x * s->movespeed)] == 0)
			s->pos_y += s->dir_x * s->movespeed;
	}
}

void	push_rl(t_all *s, int key)
{
	s->olddir_x = s->dir_x;
	s->oldplane_x = s->plane_x;
	if (key == RIGHT)
	{
		s->dir_x = s->dir_x * cos(-(s->rotspeed)) - \
		s->dir_y * sin(-(s->rotspeed));
		s->dir_y = s->olddir_x * sin(-(s->rotspeed)) + \
		s->dir_y * cos(-(s->rotspeed));
		s->plane_x = s->plane_x * cos(-(s->rotspeed)) - \
		s->plane_y * sin(-(s->rotspeed));
		s->plane_y = s->oldplane_x * sin(-(s->rotspeed)) + \
		s->plane_y * cos(-(s->rotspeed));
	}
	else if (key == LEFT)
	{
		s->dir_x = s->dir_x * cos(s->rotspeed) - \
		s->dir_y * sin(s->rotspeed);
		s->dir_y = s->olddir_x * sin(s->rotspeed) + \
		s->dir_y * cos(s->rotspeed);
		s->plane_x = s->plane_x * cos(s->rotspeed) - \
		s->plane_y * sin(s->rotspeed);
		s->plane_y = s->oldplane_x * sin(s->rotspeed) + \
		s->plane_y * cos(s->rotspeed);
	}
}

int		push_key(int keycode, t_all *s)
{
	if (keycode == KEY_ESC)
		end(s, -1, -1);
	else if (keycode == KEY_W)
		push_ws(s, KEY_W);
	else if (keycode == KEY_S)
		push_ws(s, KEY_S);
	else if (keycode == KEY_D)
		push_da(s, KEY_D);
	else if (keycode == KEY_A)
		push_da(s, KEY_A);
	else if (keycode == RIGHT)
		push_rl(s, RIGHT);
	else if (keycode == LEFT)
		push_rl(s, LEFT);
	else
		return (0);
	create_img(s);
	return (0);
}
