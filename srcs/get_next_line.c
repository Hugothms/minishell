/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:39 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/15 21:43:55 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	find_pos_eol(const char *str)
{
	size_t	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != END_OF_LINE)
		i++;
	return (i);
}

int		fill_line_with_buff(char **line, char buff[][BUFFER_SIZE + 2], int fd)
{
	size_t		len;
	size_t		eol;
	char		*tmp;

	if (!*buff[fd] && **line)
		return (OK);
	if (*buff[fd] == END_OF_LINE && !buff[fd][1])
	{
		ft_memmove(buff[fd], &buff[fd][1], 1);
		return (OK);
	}
	eol = find_pos_eol(buff[fd]);
	len = ft_strlen(&buff[fd][eol]);
	tmp = *line;
	*line = ft_strjoin(tmp, &buff[fd][0]);
	free(tmp);
	ft_memmove(buff[fd], &buff[fd][eol] + 1, len + 1);
	buff[fd][len] = '\0';
	if (len != BUFFER_SIZE)
		ft_bzero(&buff[fd][len], eol);
	if (len)
		return (OK);
	return (END);
}

int		get_next_line(int fd, char **line)
{
	static char	buff[OPEN_MAX + 1][BUFFER_SIZE + 2];
	size_t		bytes_read;

	if (BUFFER_SIZE == 0 || fd < 0 || fd > OPEN_MAX + 1 || !line)
		return (ERR);
	if (!(*line = malloc(sizeof(char))))
		return (ERR);
	**line = 0;
	while (*buff[fd])
	{
		if (fill_line_with_buff(line, buff, fd))
			return (OK);
	}
	while ((bytes_read = read(fd, buff[fd], BUFFER_SIZE)))
	{
		if (bytes_read < 0)
			return (ERR);
		buff[fd][bytes_read] = '\0';
		if (fill_line_with_buff(line, buff, fd))
			return (OK);
	}
	return (END);
}
