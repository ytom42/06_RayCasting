/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:40:56 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/01/30 17:52:27 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bmp_data(t_all *s, int fd)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned char	buffer[4];

	y = s->screen_h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < s->screen_w)
		{
			color = *(unsigned int*)(s->img.addr + \
					(y * s->img.line_len + x * (s->img.bpp / 8)));
			buffer[0] = (unsigned char)(color % 256);
			buffer[1] = (unsigned char)(color / 256 % 256);
			buffer[2] = (unsigned char)(color / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			x++;
		}
		y--;
	}
}

void	bmp_info(t_all *s, int fd)
{
	int		n;
	char	buf[40];

	n = 0;
	while (n < 40)
		buf[n++] = (unsigned char)(0);
	buf[0] = (unsigned char)(40);
	n = s->screen_w;
	buf[4] = (unsigned char)(n % 256);
	buf[5] = (unsigned char)(n / 256 % 256);
	buf[6] = (unsigned char)(n / 256 / 256 % 256);
	buf[7] = (unsigned char)(n / 256 / 256 / 256);
	n = s->screen_h;
	buf[8] = (unsigned char)(n % 256);
	buf[9] = (unsigned char)(n / 256 % 256);
	buf[10] = (unsigned char)(n / 256 / 256 % 256);
	buf[11] = (unsigned char)(n / 256 / 256 / 256);
	buf[12] = (unsigned char)(1);
	buf[14] = (unsigned char)(32);
	write(fd, buf, 40);
}

void	bmp_file(t_all *s, int fd)
{
	int		n;
	char	buf[14];

	n = 0;
	while (n < 14)
		buf[n++] = (unsigned char)(0);
	buf[0] = (unsigned int)('B');
	buf[1] = (unsigned int)('M');
	n = s->screen_w * s->screen_h * 4 + 54;
	buf[2] = (unsigned char)(n % 256);
	buf[3] = (unsigned char)(n / 256 % 256);
	buf[4] = (unsigned char)(n / 256 / 256 % 256);
	buf[5] = (unsigned char)(n / 256 / 256 / 256);
	buf[10] = (unsigned char)(54);
	write(fd, buf, 14);
}

void	create_bmp(t_all *s)
{
	int		fd;

	fd = open("window.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		end(s, 18, -1);
	bmp_file(s, fd);
	bmp_info(s, fd);
	bmp_data(s, fd);
	close(fd);
	exit(0);
}
