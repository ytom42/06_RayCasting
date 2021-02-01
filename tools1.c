/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:29:59 by ytomiyos          #+#    #+#             */
/*   Updated: 2021/02/01 12:25:18 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_strlen(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void			ft_strlcpy(char *dst, char *src, int size)
{
	int		i;

	i = 0;
	while (src[i] && size > 0)
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
}

char			*ft_strdup(char *s)
{
	int		len;
	char	*ptr;

	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(ptr, s, len);
	return (ptr);
}

char			*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	ft_strlcpy(ptr, s1, s1_len);
	ft_strlcpy((ptr + s1_len), s2, s2_len);
	return (ptr);
}

int				ft_atoi_new(char *str, int *index)
{
	int		n;

	n = 0;
	while (str[*index] >= 48 && str[*index] <= 57)
	{
		n = n * 10 + (str[*index] - 48);
		*index += 1;
	}
	return (n);
}
