/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 03:19:04 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 18:04:53 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sprite_init(t_all *s, int n)
{
	s->sp.sprite_x = s->sprites[s->spriteorder[n]].x - s->pos_x;
	s->sp.sprite_y = s->sprites[s->spriteorder[n]].y - s->pos_y;
	s->sp.invdet = 1.0 / (s->plane_x * s->dir_y - s->dir_x * s->plane_y);
	s->sp.transform_x = s->sp.invdet * \
		(s->dir_y * s->sp.sprite_x - s->dir_x * s->sp.sprite_y);
	s->sp.transform_y = s->sp.invdet * \
		(-(s->plane_y) * s->sp.sprite_x + s->plane_x * s->sp.sprite_y);
	s->sp.spritescreen_x = (int)((s->screen_w / 2) * \
		(1 + s->sp.transform_x / s->sp.transform_y));
	s->sp.sprite_h = abs((int)(s->screen_h / (s->sp.transform_y)));
	s->sp.drawstart_y = (-s->sp.sprite_h / 2) + (s->screen_h / 2);
	if (s->sp.drawstart_y < 0)
		s->sp.drawstart_y = 0;
	s->sp.drawend_y = (s->sp.sprite_h / 2) + (s->screen_h / 2);
	if (s->sp.drawend_y >= s->screen_h)
		s->sp.drawend_y = s->screen_h - 1;
	s->sp.sprite_w = abs((int)(s->screen_h / (s->sp.transform_y)));
	s->sp.drawstart_x = -s->sp.sprite_w / 2 + s->sp.spritescreen_x;
	if (s->sp.drawstart_x < 0)
		s->sp.drawstart_x = 0;
	s->sp.drawend_x = s->sp.sprite_w / 2 + s->sp.spritescreen_x;
	if (s->sp.drawend_x >= s->screen_w)
		s->sp.drawend_x = s->screen_w - 1;
	s->sp.stripe = s->sp.drawstart_x;
}

void	put_sprite_pixelput(t_all *s)
{
	int		y;
	int		d;

	while (s->sp.stripe < s->sp.drawend_x)
	{
		s->tex_x = (int)(256 * \
			(s->sp.stripe - (-s->sp.sprite_w / 2 + s->sp.spritescreen_x))\
			* TEX_WIDTH / s->sp.sprite_w) / 256;
		if (s->sp.transform_y > 0 && s->sp.stripe > 0 && \
			s->sp.stripe < s->screen_w && \
			s->sp.transform_y < s->buf.z_buf[s->sp.stripe])
		{
			y = s->sp.drawstart_y;
			while (y < s->sp.drawend_y)
			{
				d = y * 256 - s->screen_h * 128 + s->sp.sprite_h * 128;
				s->tex_y = ((d * TEX_HEIGHT) / s->sp.sprite_h) / 256;
				my_mlx_pixel_put3(s, s->sp.stripe, y, &s->texs.tex_sp);
				y++;
			}
		}
		s->sp.stripe += 1;
	}
}

void	put_sprite(t_all *s)
{
	int		n;

	n = 0;
	sort_sprites(s);
	while (n < s->sprite_len)
	{
		put_sprite_init(s, n);
		put_sprite_pixelput(s);
		n++;
	}
}
