/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:27:19 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 18:28:16 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	check_front(char *file, char *str)
{
	size_t	i;
	bool	is_dot;

	i = 0;
	if (ft_strchr(file, '.'))
		is_dot = true;
	else
		is_dot = false;
	if (is_dot == true && !ft_strchr(str, '.'))
		return (false);
	while (str[i] && str[i] != '*')
	{
		if (str[i] != file[i])
			return (false);
		i++;
	}
	return (true);
}

bool	check_back(char *file, char *str)
{
	size_t	i;
	size_t	j;
	size_t	len_str;
	size_t	len_file;

	len_str = ft_strlen(str);
	len_file = ft_strlen(file);
	if (len_str == 0 || len_file == 0 || str[len_str - 1] == '*')
		return (true);
	i = len_str - 1;
	j = len_file - 1;
	while (i >= 0 && j >= 0 && str[i] != '*')
	{
		if (str[i] != file[j])
			return (false);
		i--;
		j--;
	}
	return (true);
}

bool	move_asterisk(char **file, size_t i, char **words)
{
	size_t	file_len;
	size_t	word_len;
	size_t	j;

	file_len = ft_strlen(*file);
	word_len = ft_strlen(words[i]);
	*file = ft_strnstr(*file, words[i], file_len);
	if (!file)
	{
		safe_free_double_char(words);
		return (false);
	}
	j = 0;
	while (j < word_len)
	{
		(*file)++;
		j++;
	}
	return (true);
}

bool	match_asterisk(char *file, char *str)
{
	char	**words;
	size_t	i;

	i = 0;
	if (!check_front(file, str) || !check_back(file, str))
		return (false);
	words = ft_split(str, '*');
	while (words[i])
	{
		if (!move_asterisk(&file, i, words))
			return (false);
		i++;
	}
	safe_free_double_char(words);
	return (true);
}
