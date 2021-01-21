/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 03:20:12 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/19 03:20:42 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_pos(t_all *s, int key)
{
	if (key == KEY_W)
	{
		if(s->map[(int)(s->posX + s->dirX * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX += s->dirX * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY + s->dirY * s->moveSpeed)] == 0)
			s->posY += s->dirY * s->moveSpeed;
	}
	else if (key == KEY_S)
	{
		if(s->map[(int)(s->posX - s->dirX * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX -= s->dirX * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY - s->dirY * s->moveSpeed)] == 0)
			s->posY -= s->dirY * s->moveSpeed;
	}
	else if (key == KEY_D)
	{
		if(s->map[(int)(s->posX + s->dirY * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX += s->dirY * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY - s->dirX * s->moveSpeed)] == 0)
			s->posY -= s->dirX * s->moveSpeed;
	}
	else if (key == KEY_A)
	{
		if(s->map[(int)(s->posX - s->dirY * s->moveSpeed)][(int)(s->posY)] == 0)
			s->posX -= s->dirY * s->moveSpeed;
		if(s->map[(int)(s->posX)][(int)(s->posY + s->dirX * s->moveSpeed)] == 0)
			s->posY += s->dirX * s->moveSpeed;
	}
}

void	turn_RL(t_all *s, int key)
{
	if (key == RIGHT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(-(s->rotSpeed)) - s->dirY * sin(-(s->rotSpeed));
		s->dirY = s->oldDirX * sin(-(s->rotSpeed)) + s->dirY * cos(-(s->rotSpeed));
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(-(s->rotSpeed)) - s->planeY * sin(-(s->rotSpeed));
		s->planeY = s->oldPlaneX * sin(-(s->rotSpeed)) + s->planeY * cos(-(s->rotSpeed));
	}
	else if(key == LEFT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(s->rotSpeed) - s->dirY * sin(s->rotSpeed);
		s->dirY = s->oldDirX * sin(s->rotSpeed) + s->dirY * cos(s->rotSpeed);
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(s->rotSpeed) - s->planeY * sin(s->rotSpeed);
		s->planeY = s->oldPlaneX * sin(s->rotSpeed) + s->planeY * cos(s->rotSpeed);
	}
}

int	check_key(int keycode, t_all *s)
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
	put_img(s);
	return (0);
}
