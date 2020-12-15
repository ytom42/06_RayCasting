#include "cub3d.h"

static char	*nl_to_null(char *buffer)
{
	if (buffer == NULL)
		return (NULL);
	while (*buffer)
	{
		if (*buffer == '\n')
		{
			*buffer = '\0';
			return (buffer);
		}
		buffer++;
	}
	return (NULL);
}

static int	ft_setup(int fd, char **line, char **buffer, char **next_start)
{
	if (fd < 0)
		return (-1);
	if (*next_start == NULL)
	{
		*line = ft_strdup("");
		if (!(*line))
			return (-1);
	}
	else
	{
		*line = *next_start;
		*next_start = nl_to_null(*next_start);
	}
	*buffer = (char *)malloc(sizeof(char) * (2));
	if (!(*buffer))
		return (-1);
	return (1);
}

static int	ft_gnl(int size, char **line, char **buffer, char **next_start)
{
	char		*tmp;

	buffer[0][size] = '\0';
	*next_start = nl_to_null(*buffer);
	tmp = *line;
	*line = ft_strjoin(*line, *buffer);
	free(tmp);
	if (!(*line))
	{
		free(*buffer);
		return (-1);
	}
	return (1);
}

static int	ft_clean(int size, char **buffer, char **next_start)
{
	if (size == -1)
	{
		free(*buffer);
		return (-1);
	}
	if (*next_start)
	{
		*next_start = ft_strdup(*next_start + 1);
		free(*buffer);
		if (!(*next_start))
			return (-1);
		return (1);
	}
	free(*buffer);
	return (0);
}

int			gnl(int fd, char **line)
{
	int			n;
	int			size;
	char		*buffer;
	static char	*next_start;

	if (ft_setup(fd, line, &buffer, &next_start) <= 0)
		return (-1);
	while (!next_start && (size = read(fd, buffer, 1)) > 0)
	{
		if (ft_gnl(size, line, &buffer, &next_start) <= 0)
			return (-1);
	}
	n = ft_clean(size, &buffer, &next_start);
	if (n == -1)
		return (-1);
	if (n == 1)
		return (1);
	return (0);
}
