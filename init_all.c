/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:25:07 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 09:29:00 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_flag(t_all *s)
{
	s->flag.r = 0;
	s->flag.no = 0;
	s->flag.so = 0;
	s->flag.we = 0;
	s->flag.ea = 0;
	s->flag.f = 0;
	s->flag.c = 0;
	s->flag.s = 0;
	s->flag.pos = 0;
}

void	init_var(t_all *s)
{
	s->time = 0;
	s->oldtime = 0;
	s->movespeed = 0.6;
	s->rotspeed = 0.08;

	s->map_height = 0;
	s->map_width = 0;
	s->sprite_len = 0;

	s->map_before_line = 0;
}

void	init_ptr(t_all *s)
{
	s->texs.tex_n.img = NULL;
	s->texs.tex_s.img = NULL;
	s->texs.tex_e.img = NULL;
	s->texs.tex_w.img = NULL;
	s->texs.tex_sp.img = NULL;
	s->sprites = NULL;
	s->spriteorder = NULL;
	s->spritedistance = NULL;
}

void	init_window(t_all *s)
{
	if (!(s->img.img = mlx_new_image(s->mlx, s->screen_w, s->screen_h)))
		end(s, 17, -1);
	s->img.addr = mlx_get_data_addr(s->img.img, &s->img.bpp, &s->img.line_len, &s->img.endian);
	if (!(s->buf.z_buffer = (double*)malloc(sizeof(double) * (s->screen_w + 1))))
		end(s, 17, -1);
}

void	init_texaddr(t_all *s)
{
	s->texs.tex_n.addr = mlx_get_data_addr(s->texs.tex_n.img, &s->texs.tex_n.bpp, &s->texs.tex_n.line_len, &s->texs.tex_n.endian);
	s->texs.tex_s.addr = mlx_get_data_addr(s->texs.tex_s.img, &s->texs.tex_s.bpp, &s->texs.tex_s.line_len, &s->texs.tex_s.endian);
	s->texs.tex_e.addr = mlx_get_data_addr(s->texs.tex_e.img, &s->texs.tex_e.bpp, &s->texs.tex_e.line_len, &s->texs.tex_e.endian);
	s->texs.tex_w.addr = mlx_get_data_addr(s->texs.tex_w.img, &s->texs.tex_w.bpp, &s->texs.tex_w.line_len, &s->texs.tex_w.endian);
	s->texs.tex_sp.addr = mlx_get_data_addr(s->texs.tex_sp.img, &s->texs.tex_sp.bpp, &s->texs.tex_sp.line_len, &s->texs.tex_sp.endian);
}

void	init_all(t_all *s)
{
	printf("\x1b[32mSTART [init_all]----------------------------------\n\x1b[0m");
	if (!(s->mlx = mlx_init()))
		end(s, 17, 0);
	init_flag(s);
	init_var(s);
	init_ptr(s);
	init_map(s);
	init_window(s);
	init_texaddr(s);
	printf("\x1b[32mEND [init_all]----------------------------------\n\x1b[0m");
}
