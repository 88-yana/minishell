/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:36:44 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/22 18:58:40 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gt_strjoin(char **save, char **buf)
{
	size_t	save_len;
	size_t	buf_len;
	char	*line;
	size_t	i;

	save_len = gt_strlen(*save);
	buf_len = gt_strlen(*buf);
	line = malloc(save_len + buf_len + 1);
	if (line == NULL)
		return (gt_free(save, buf));
	i = 0;
	while (i < save_len)
	{
		line[i] = (*save)[i];
		i++;
	}
	while (i < save_len + buf_len + 1)
	{
		line[i] = (*buf)[i - save_len];
		i++;
	}
	gt_free(save, NULL);
	*save = line;
	return (*save);
}

static char	*gt_strclip(char **save, char **buf)
{
	size_t	s_len;
	size_t	i;
	char	*line;

	if (*save == NULL)
		return (gt_free(save, buf));
	s_len = gt_strlen(*save);
	line = malloc(s_len + 1);
	if (line == NULL)
		return (gt_free(save, buf));
	i = 0;
	while (i < s_len + 1)
	{
		line[i] = (*save)[i];
		if ((*save)[i] == '\n')
		{
			line[i] = '\0';
			gt_strlcpy(save, i + 1, s_len - i - 1);
			gt_free(NULL, buf);
			return (line);
		}
		i++;
	}
	gt_free(save, buf);
	return (line);
}

char	*get_line(int fd)
{
	char		*buf;
	static char	*save[FILE_OPEN_MAX];
	int			bytes;

	if (BUFFER_SIZE < 1 || fd < 0 || FILE_OPEN_MAX < fd)
		return (NULL);
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (buf == NULL)
		return (gt_free(&save[fd], &buf));
	while (1)
	{
		if (gt_find_nl(save[fd]))
			break ;
		bytes = read(fd, buf, (size_t) BUFFER_SIZE);
		if (bytes == -1)
			return (gt_free(&save[fd], &buf));
		buf[bytes] = 0;
		if (bytes == 0)
			break ;
		if (gt_strjoin(&save[fd], &buf) == NULL)
			return (NULL);
	}
	return (gt_strclip(&save[fd], &buf));
}
