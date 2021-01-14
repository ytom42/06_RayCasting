/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:25:07 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/13 22:12:03 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_flag(t_all *s)
{
	s->flag.R = 0;
	s->flag.NO = 0;
	s->flag.SO = 0;
	s->flag.WE = 0;
	s->flag.EA = 0;
	s->flag.F = 0;
	s->flag.C = 0;
	s->flag.S = 0;
	s->flag.POS = 0;
	s->sprite_len = 0;
}

void	init_sprite(t_all *s)
{
	// 取得失敗時のエラー処理
	s->sprites = malloc(sizeof(t_sprite) * s->sprite_len);
	s->spriteOrder = malloc(sizeof(int) * s->sprite_len);
	s->spriteDistance = malloc(sizeof(double) * s->sprite_len);
}

void	init_window(t_all *s)
{
	// 取得失敗時のエラー処理
	s->win = mlx_new_window(s->mlx, s->screenWidth, s->screenHeight, "cub3D");
	s->img.img = mlx_new_image(s->mlx, s->screenWidth, s->screenHeight);
	s->img.addr = mlx_get_data_addr(s->img.img, &s->img.bpp, &s->img.line_len, &s->img.endian);
	
	s->time = 0;
	s->oldTime = 0;
	s->moveSpeed = 0.6;
	s->rotSpeed = 0.08;
	s->buf.ZBuffer = malloc(sizeof(double) * s->screenWidth); //widthが決まった後ではならない
}

void	init_texaddr(t_all *s)
{
	// 取得失敗時のエラー処理
	s->tex_N.addr = mlx_get_data_addr(s->tex_N.img, &s->tex_N.bpp, &s->tex_N.line_len, &s->tex_N.endian);
	s->tex_S.addr = mlx_get_data_addr(s->tex_S.img, &s->tex_S.bpp, &s->tex_S.line_len, &s->tex_S.endian);
	s->tex_E.addr = mlx_get_data_addr(s->tex_E.img, &s->tex_E.bpp, &s->tex_E.line_len, &s->tex_E.endian);
	s->tex_W.addr = mlx_get_data_addr(s->tex_W.img, &s->tex_W.bpp, &s->tex_W.line_len, &s->tex_W.endian);
	s->tex_SP.addr = mlx_get_data_addr(s->tex_SP.img, &s->tex_SP.bpp, &s->tex_SP.line_len, &s->tex_SP.endian);
}

void	init_all(t_all *s)
{
	s->mlx = mlx_init();
	init_flag(s);
	init_sprite(s);
	init_map(s);
	init_window(s);
	init_texaddr(s);
}
