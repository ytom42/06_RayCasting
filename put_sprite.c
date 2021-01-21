/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 03:19:04 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/21 10:47:32 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sprite_init(t_all *s, int n)
{
	s->sp.sprite_x = s->sprites[s->spriteOrder[n]].x - s->posX;
	s->sp.sprite_y = s->sprites[s->spriteOrder[n]].y - s->posY;
	s->sp.invdet = 1.0 / (s->planeX * s->dirY - s->dirX * s->planeY);
	s->sp.transform_x = s->sp.invdet * \
		(s->dirY * s->sp.sprite_x - s->dirX * s->sp.sprite_y);
	s->sp.transform_y = s->sp.invdet * \
		(-(s->planeY) * s->sp.sprite_x + s->planeX * s->sp.sprite_y);
	s->sp.spritescreen_x = (int)((s->screenWidth / 2) * \
		(1 + s->sp.transform_x / s->sp.transform_y));
	s->sp.sprite_h = abs((int)(s->screenHeight / (s->sp.transform_y)));
	s->sp.drawstart_y = (-s->sp.sprite_h / 2) + (s->screenHeight / 2);
	if (s->sp.drawstart_y < 0)
		s->sp.drawstart_y = 0;
	s->sp.drawend_y = (s->sp.sprite_h / 2) + (s->screenHeight / 2);
	if (s->sp.drawend_y >= s->screenHeight)
		s->sp.drawend_y = s->screenHeight - 1;
	s->sp.sprite_w = abs((int)(s->screenHeight / (s->sp.transform_y)));
	s->sp.drawstart_x = -s->sp.sprite_w / 2 + s->sp.spritescreen_x;
	if (s->sp.drawstart_x < 0)
		s->sp.drawstart_x = 0;
	s->sp.drawend_x = s->sp.sprite_w / 2 + s->sp.spritescreen_x;
	if (s->sp.drawend_x >= s->screenWidth)
		s->sp.drawend_x = s->screenWidth - 1;
	s->sp.stripe = s->sp.drawstart_x;
}

void	put_sprite_pixelput(t_all *s)
{
	int		y;
	int		d;

	while (s->sp.stripe < s->sp.drawend_x)
	{
		s->texX = (int)(256 * \
			(s->sp.stripe - (-s->sp.sprite_w / 2 + s->sp.spritescreen_x))\
			* texWidth / s->sp.sprite_w) / 256;
		if (s->sp.transform_y > 0 && s->sp.stripe > 0 && \
			s->sp.stripe < s->screenWidth && \
			s->sp.transform_y < s->buf.ZBuffer[s->sp.stripe])
		{
			y = s->sp.drawstart_y;
			while (y < s->sp.drawend_y)
			{
				d = y * 256 - s->screenHeight * 128 + s->sp.sprite_h * 128;
				s->texY = ((d * texHeight) / s->sp.sprite_h) / 256;
				my_mlx_pixel_put3(s, s->sp.stripe, y, &s->texs.tex_SP);
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
