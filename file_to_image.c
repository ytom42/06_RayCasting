/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:13:51 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/26 23:16:42 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 		north_tex_to_img(t_all *s, char *line)
{
	if (s->flag.no == 1)
		end(s, 6);
	s->texs.tex_n.img = mlx_xpm_file_to_image(s->mlx, line, &s->texs.tex_n.width, &s->texs.tex_n.height);
	if (s->texs.tex_n.img == NULL)
		end(s, 8);
	s->flag.no = 1;
}

void 		south_tex_to_img(t_all *s, char *line)
{
	if (s->flag.so == 1)
		end(s, 6);
	s->texs.tex_s.img = mlx_xpm_file_to_image(s->mlx, line, &s->texs.tex_s.width, &s->texs.tex_s.height);
	if (s->texs.tex_s.img == NULL)
		end(s, 8);
	s->flag.so = 1;
}

void 		east_tex_to_img(t_all *s, char *line)
{
	if (s->flag.ea == 1)
		end(s, 6);
	s->texs.tex_e.img = mlx_xpm_file_to_image(s->mlx, line, &s->texs.tex_e.width, &s->texs.tex_e.height);
	if (s->texs.tex_e.img == NULL)
		end(s, 8);
	s->flag.ea = 1;
}

void 		west_tex_to_img(t_all *s, char *line)
{
	if (s->flag.we == 1)
		end(s, 6);
	s->texs.tex_w.img = mlx_xpm_file_to_image(s->mlx, line, &s->texs.tex_w.width, &s->texs.tex_w.height);
	if (s->texs.tex_w.img == NULL)
		end(s, 8);
	s->flag.we = 1;
}
