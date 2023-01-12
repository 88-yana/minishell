/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:34:15 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/13 07:22:12 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	init_lexer(int *i, int *str_len, bool during_[2])
{
	*i = -1;
	*str_len = -1;
	during_[DQ] = false;
	during_[SQ] = false;
}

static char	**add_array(char **array, char *line, int i, int *str_len)
{
	char	*temp;

	if (*str_len > 0)
	{
		temp = ft_substr(line, i - *str_len, *str_len);
		array = realloc_array(array, temp);
		free(temp);
	}
	*str_len = -1;
	return (array);
}

static char	**lexer(char *line)
{
	int		i;
	int		str_len;
	bool	during_[2];
	char	**array;

	array = malloc(sizeof(char *));
	*array = NULL;
	init_lexer(&i, &str_len, during_);
	while (1)
	{
		i++;
		str_len++;
		if (line[i] == DOUBLEQ && !during_[SQ])
			during_[DQ] = !during_[DQ];
		if (line[i] == SINGLEQ && !during_[DQ])
			during_[SQ] = !during_[SQ];
		if (during_[DQ] || during_[SQ])
			continue ;
		if (line[i] == ' ' | line[i] == '\0')
			array = add_array(array, line, i, &str_len);
		if (line[i] == '\0')
			break ;
	}
	return (array);
}

static char	**arrayjoinnotfree(char **arr1, char **arr2)
{
	size_t	length;
	size_t	i;
	size_t	j;
	char	**new;

	length = arraylen(arr1) + arraylen(arr2);
	new = malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (arr1[i] != NULL)
	{
		new[i] = arr1[i];
		i++;
	}
	j = 0;
	while (arr2[j] != NULL)
	{
		new[i + j] = arr2[j];
		j++;
	}
	new[length] = NULL;
	i = 0;
	free(arr1);
	return (new);
}

void	split_env(char ***cmd)
{
	int		i;
	char	**splited;
	char	**latter;
	char	*str;

	i = 0;
	while ((*cmd)[i] && (*cmd)[i][0])
	{
		latter = clip_latter(*cmd, i + 1);
		str = (*cmd)[i];
		(*cmd)[i] = NULL;
		splited = lexer(str);
		free(str);
		*cmd = arrayjoinnotfree(*cmd, splited);
		*cmd = arrayjoinnotfree(*cmd, latter);
		if (arraylen(splited) > 1)
			i += arraylen(splited);
		else
			i++;
		free(latter);
		free(splited);
	}
}
