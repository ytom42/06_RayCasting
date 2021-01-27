/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 03:20:12 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/25 15:54:10 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_pos(t_all *s, int key)
{
	if (key == KEY_W)
	{
		if(s->map[(int)(s->pos_x + s->dir_x * s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x += s->dir_x * s->movespeed;
		if(s->map[(int)(s->pos_x)][(int)(s->pos_y + s->dir_y * s->movespeed)] == 0)
			s->pos_y += s->dir_y * s->movespeed;
	}
	else if (key == KEY_S)
	{
		if(s->map[(int)(s->pos_x - s->dir_x * s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x -= s->dir_x * s->movespeed;
		if(s->map[(int)(s->pos_x)][(int)(s->pos_y - s->dir_y * s->movespeed)] == 0)
			s->pos_y -= s->dir_y * s->movespeed;
	}
	else if (key == KEY_D)
	{
		if(s->map[(int)(s->pos_x + s->dir_y * s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x += s->dir_y * s->movespeed;
		if(s->map[(int)(s->pos_x)][(int)(s->pos_y - s->dir_x * s->movespeed)] == 0)
			s->pos_y -= s->dir_x * s->movespeed;
	}
	else if (key == KEY_A)
	{
		if(s->map[(int)(s->pos_x - s->dir_y * s->movespeed)][(int)(s->pos_y)] == 0)
			s->pos_x -= s->dir_y * s->movespeed;
		if(s->map[(int)(s->pos_x)][(int)(s->pos_y + s->dir_x * s->movespeed)] == 0)
			s->pos_y += s->dir_x * s->movespeed;
	}
}

void	turn_RL(t_all *s, int key)
{
	if (key == RIGHT)
	{
		s->olddir_x = s->dir_x;
		s->dir_x = s->dir_x * cos(-(s->rotspeed)) - s->dir_y * sin(-(s->rotspeed));
		s->dir_y = s->olddir_x * sin(-(s->rotspeed)) + s->dir_y * cos(-(s->rotspeed));
		s->oldplane_x = s->plane_x;
		s->plane_x = s->plane_x * cos(-(s->rotspeed)) - s->plane_y * sin(-(s->rotspeed));
		s->plane_y = s->oldplane_x * sin(-(s->rotspeed)) + s->plane_y * cos(-(s->rotspeed));
	}
	else if(key == LEFT)
	{
		s->olddir_x = s->dir_x;
		s->dir_x = s->dir_x * cos(s->rotspeed) - s->dir_y * sin(s->rotspeed);
		s->dir_y = s->olddir_x * sin(s->rotspeed) + s->dir_y * cos(s->rotspeed);
		s->oldplane_x = s->plane_x;
		s->plane_x = s->plane_x * cos(s->rotspeed) - s->plane_y * sin(s->rotspeed);
		s->plane_y = s->oldplane_x * sin(s->rotspeed) + s->plane_y * cos(s->rotspeed);
	}
}

int	push_key(int keycode, t_all *s)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(s->mlx, s->win);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_pos(s, KEY_W);
	else if (keycode == KEY_S)
		move_pos(s, KEY_S);
	else if (keycode == KEY_D)
		move_pos(s, KEY_D);
	else if (keycode == KEY_A)
		move_pos(s, KEY_A);
	else if (keycode == RIGHT)
		turn_RL(s, RIGHT);
	else if(keycode == LEFT)
		turn_RL(s, LEFT);
	create_img(s);
	return (0);
}
