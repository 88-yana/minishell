/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:47:01 by yahokari          #+#    #+#             */
/*   Updated: 2022/08/13 20:02:21 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static char	*ft_read_char(int fd, char *save)
{
	char	*buf;
	char	*tmp;
	int		read_len;

	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (ft_strchr(save, '\n') == NULL)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == -1 || (read_len == 0 && save[0] == '\0'))
		{
			free(buf);
			free(save);
			return (NULL);
		}
		buf[read_len] = '\0';
		tmp = ft_strjoin(save, buf);
		free(save);
		save = tmp;
		if (read_len == 0)
			break ;
	}
	free(buf);
	return (save);
}

static char	*ft_get_str(char *save, char **str)
{
	char	*tmp;
	size_t	save_len;
	size_t	next_line;

	next_line = ft_strchr(save, '\n') - save + 1;
	save_len = ft_strlen(save);
	*str = ft_substr_size_t(save, 0, next_line);
	if (*str == NULL)
	{
		free(save);
		return (NULL);
	}
	tmp = ft_substr_size_t(save, next_line, save_len - next_line + 1);
	free(save);
	if (tmp == NULL)
		return (NULL);
	save = tmp;
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[256];
	char		*str;

	if (fd < 0 || fd > 255)
		return (NULL);
	if (save[fd] == NULL)
	{
		save[fd] = malloc(sizeof(char));
		if (save[fd] == NULL)
			return (NULL);
		save[fd][0] = '\0';
	}
	save[fd] = ft_read_char(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	str = NULL;
	save[fd] = ft_get_str(save[fd], &str);
	if (save[fd] == NULL)
		return (NULL);
	return (str);
}
