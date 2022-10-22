/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:36:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/03 22:36:39 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gt_strlen(const char *str)
{
	size_t	cnt;

	if (str == NULL)
		return (0);
	cnt = 0;
	while (str[cnt] != 0)
		cnt++;
	return (cnt);
}

char	*gt_strlcpy(char **save, size_t start, size_t len)
{
	size_t	i;

	if (len == 0)
		return (gt_free(save, NULL));
	i = 0;
	while (i < len + 1)
	{
		(*save)[i] = (*save)[start + i];
		i++;
	}
	return (*save);
}

char	*gt_free(char **save, char **buf)
{
	if (save != NULL)
	{
		free(*save);
		*save = NULL;
	}
	if (buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return (NULL);
}

int	gt_find_nl(char *save)
{
	if (save == NULL)
		return (0);
	while (*save != 0)
	{
		if (*save == '\n')
			return (1);
		save++;
	}
	return (0);
}
