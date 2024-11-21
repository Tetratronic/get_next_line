/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:34:11 by abenkaro          #+#    #+#             */
/*   Updated: 2024/11/20 18:05:33 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *remainder)
{
	char	*line;
	int		i;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update(char *line, char **remainder)
{
	int		i;
	int		nl_index;
	char	*new_remainder;

	if (!line)
		return (clean(remainder));
	i = 0;
	nl_index = ft_strlen(line);
	new_remainder = malloc(ft_strlen(*remainder) - nl_index + 1);
	if (!new_remainder)
		return (clean(remainder));
	while ((*remainder)[nl_index] != '\0')
		new_remainder[i++] = (*remainder)[nl_index++];
	new_remainder[i] = '\0';
	clean(remainder);
	return (new_remainder);
}

void	fill(int bytes, char **remainder, char *buffer)
{
	char	*tmp;

	buffer[bytes] = '\0';
	tmp = ft_strjoin(*remainder, buffer);
	free(*remainder);
	*remainder = tmp;
}

char	*check_last(int bytes, char **remainder, char **buffer)
{
	char	*tmp;

	if (bytes == 0 && *remainder && **remainder)
	{
		tmp = ft_strdup(*remainder);
		clean(remainder);
		clean(buffer);
		return (tmp);
	}
	clean(remainder);
	clean(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remainder[10240];
	char		*line;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (clean(&(remainder[fd])));
	while (1)
	{
		if (remainder[fd] && ft_strchr(remainder[fd], '\n'))
		{
			line = extract_line(remainder[fd]);
			remainder[fd] = update(line, &(remainder[fd]));
			clean(&buffer);
			return (line);
		}
		bytes = read(fd, buffer, (size_t)BUFFER_SIZE);
		if (bytes <= 0)
			return (check_last(bytes, &(remainder[fd]), &buffer));
		fill(bytes, &(remainder[fd]), buffer);
	}
}
