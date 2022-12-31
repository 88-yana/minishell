/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:24:23 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 18:25:44 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**clip_latter(char **cmd, size_t start)
{
	char	**latter;
	size_t	size;
	size_t	i;

	size = arraylen(cmd) - start;
	latter = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (cmd[start + i] != NULL)
	{
		latter[i] = cmd[start + i];
		i++;
	}
	latter[i] = NULL;
	return (latter);
}

char	**realloc_array(char **cmd, char *str)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (arraylen(cmd) + 2));
	i = 0;
	while (cmd[i])
	{
		new[i] = cmd[i];
		i++;
	}
	new[i] = ft_strdup(str);
	if (new[i] == NULL)
		exit(1);
	new[i + 1] = NULL;
	free(cmd);
	cmd = NULL;
	return (new);
}

DIR	*calldir(void)
{
	DIR		*dir;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	dir = opendir(cwd);
	free(cwd);
	return (dir);
}
