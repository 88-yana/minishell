/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:06:39 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 18:27:10 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

bool	expand_each_asterisk(DIR *dir, char *str, bool *flag, char ***cmd)
{
	struct dirent	*dirent;

	dirent = readdir(dir);
	if (!dirent)
		return (false);
	if (match_asterisk(dirent->d_name, str))
	{
		*flag = true;
		*cmd = realloc_array(*cmd, dirent->d_name);
	}
	return (true);
}

void	expand_asterisk(char ***cmd, size_t pos)
{
	DIR				*dir;
	char			*str;
	char			**latter;
	bool			flag;

	flag = false;
	dir = calldir();
	str = (*cmd)[pos];
	latter = clip_latter(*cmd, pos + 1);
	(*cmd)[pos] = NULL;
	while (true)
	{
		if (!expand_each_asterisk(dir, str, &flag, cmd))
			break ;
	}
	closedir(dir);
	if (!flag)
		(*cmd)[pos] = str;
	else
	{
		free(str);
		*cmd = arrayjoin(*cmd, latter);
	}
	free(latter);
}

static bool	has_asterisk(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

char	**check_asterisk(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (has_asterisk(cmd[i]))
			expand_asterisk(&cmd, i);
		i++;
	}
	return (cmd);
}
