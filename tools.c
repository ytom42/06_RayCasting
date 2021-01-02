/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:29:59 by ytomiyos          #+#    #+#             */
/*   Updated: 2020/12/31 10:54:55 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long createRGB(int r, int g, int b)
{
	printf("r -> %d\n", r);
	printf("g -> %d\n", g);
	printf("b -> %d\n", b);
	return (r * 256 * 256 + g * 256 + b);
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void ft_strlcpy(char *dst, char *src, int size)
{
	int i;

	i = 0;
	while (src[i] && size > 0)
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
}

char *ft_strdup(char *s)
{
	int len;
	char *ptr;

	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(ptr, s, len);
	return (ptr);
}

char *ft_strjoin(char *s1, char *s2)
{
	int s1_len;
	int s2_len;
	char *ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	ft_strlcpy(ptr, s1, s1_len);
	ft_strlcpy((ptr + s1_len), s2, s2_len);
	return (ptr);
}

char *ft_hextoa(unsigned int  hex)
{
	int len;
	char *str;
	char *ptr;
	unsigned int tmp;

	len = 0;
	str = "0123456789abcdef";
	tmp = hex;
	if (tmp == 0)
		len++;
	while (tmp > 0 && ++len)
		tmp /= 16;
	ptr = malloc(sizeof(char *) * (len + 1));
	ptr[len] = '\0';
	while (len >= 0 && len--)
	{
		ptr[len] = str[hex % 16];
		hex /= 16;
	}
	return (ptr);
}

char *ft_itoa(int n)
{
	int minus;
	int len;
	int tmp;
	char *ptr;

	tmp = n;
	len = 0;
	minus = 0;
	if (tmp == -2147483648)
		return (ptr = "-2147483648");
	if (tmp == 0)
		return (ptr = "0");
	if (tmp < 0)
	{
		len++;
		tmp = -tmp;
		n = -n;
		minus = 1;
	}
	while (tmp > 0 && ++len)
		tmp /= 10;
	ptr = malloc(sizeof(char) * (len + 1));
	ptr[len] = '\0';
	while (len--)
	{
		ptr[len] = n % 10 + '0';
		n /= 10;
	}
	if (minus)
		ptr[0] = '-';
	return (ptr);
}
