/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:25:07 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/19 01:33:49 by ytomiyos         ###   ########.fr       */
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
}

void	init_window(t_all *s)
{
	// 取得失敗時のエラー処理
	s->win = mlx_new_window(s->mlx, s->screenWidth, s->screenHeight, "cub3D");
	s->img.img = mlx_new_image(s->mlx, s->screenWidth, s->screenHeight);
	s->img.addr = mlx_get_data_addr(s->img.img, &s->img.bpp, &s->img.line_len, &s->img.endian);
	s->buf.ZBuffer = (double*)malloc(sizeof(double) * (s->screenWidth + 1)); //widthが決まった後ではならない
}

void	init_texaddr(t_all *s)
{
	// 取得失敗時のエラー処理
	s->texs.tex_N.addr = mlx_get_data_addr(s->texs.tex_N.img, &s->texs.tex_N.bpp, &s->texs.tex_N.line_len, &s->texs.tex_N.endian);
	s->texs.tex_S.addr = mlx_get_data_addr(s->texs.tex_S.img, &s->texs.tex_S.bpp, &s->texs.tex_S.line_len, &s->texs.tex_S.endian);
	s->texs.tex_E.addr = mlx_get_data_addr(s->texs.tex_E.img, &s->texs.tex_E.bpp, &s->texs.tex_E.line_len, &s->texs.tex_E.endian);
	s->texs.tex_W.addr = mlx_get_data_addr(s->texs.tex_W.img, &s->texs.tex_W.bpp, &s->texs.tex_W.line_len, &s->texs.tex_W.endian);
	s->texs.tex_SP.addr = mlx_get_data_addr(s->texs.tex_SP.img, &s->texs.tex_SP.bpp, &s->texs.tex_SP.line_len, &s->texs.tex_SP.endian);
}

void	init_var(t_all *s)
{
	s->time = 0;
	s->oldTime = 0;
	s->moveSpeed = 0.6;
	s->rotSpeed = 0.08;

	s->map_height = 0;
	s->map_width = 0;
	s->sprite_len = 0;
}

void	init_all(t_all *s)
{
	printf("\x1b[32mSTART [init_all]----------------------------------\n\x1b[0m");
	s->mlx = mlx_init();
	init_flag(s);
	init_var(s);
	init_map(s);
		printf("\x1b[32mdone!! init_map\n\x1b[0m");
	init_window(s);
		printf("\x1b[32mdone!! init_window\n\x1b[0m");
	init_texaddr(s);
		printf("\x1b[32mdone!! init_texaddr\n\x1b[0m");
	printf("\x1b[31mEND [init_all]----------------------------------\n\x1b[0m");
}
