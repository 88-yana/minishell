/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:21:21 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/22 17:48:11 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"

static size_t	ft_count_size(char *s, char c, size_t count, size_t str_len)
{
	size_t	i;
	int		during_duble_quote;
	int		during_single_quote;

	i = 0;
	during_duble_quote = 0;
	during_single_quote = 0;
	while (1)
	{
		if ((s[i] == c || s[i] == '\0') && str_len > 0)
			count++;
		if (s[i] == '\0')
			break ;
		if (s[i] == '"')
			during_duble_quote = 1 - during_duble_quote;
		if (s[i] == '\'')
			during_single_quote = 1 - during_single_quote;
		if (s[i] != c && !during_duble_quote && !during_single_quote)
			str_len++;
		else
			str_len = 0;
		i++;
	}
	return (count);
}

static char	**ft_safe_free(size_t count, char **copy)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free (copy[i]);
		i++;
	}
	free(copy);
	return (NULL);
}

static char	**ft_store_str(char *s, char c, char **copy, size_t str_len)
{
	size_t	i;
	size_t	count;
	int		during_duble_quote;
	int		during_single_quote;

	i = 0;
	count = 0;
	during_duble_quote = 0;
	during_single_quote = 0;
	while (1)
	{
		if (s[i] == '\"')
		{
			i++;
			str_len++;
			while (s[i] != '\"')
				str_len++;
			copy[count] = malloc(sizeof(char) * (str_len + 1));
			if (copy[count] == NULL)
				return (ft_safe_free(count, copy));
			ft_strlcpy(copy[count], &s[i - 1], str_len + 1);
			count++;
			i += str_len - 1;
			str_len = 0;
		}
		if (s[i] == '\'')
		{
			i++;
			str_len++;
			while (s[i] != '\'')
				str_len++;
			copy[count] = malloc(sizeof(char) * (str_len + 1));
			if (copy[count] == NULL)
				return (ft_safe_free(count, copy));
			ft_strlcpy(copy[count], &s[i - 1], str_len + 1);
			count++;
			i += str_len - 1;
			str_len = 0;
		}
		if ((s[i] == c || s[i] == '\0') && str_len > 0)
		{
			copy[count] = malloc(sizeof(char) * (str_len + 1));
			if (copy[count] == NULL)
				return (ft_safe_free(count, copy));
			ft_strlcpy(copy[count], &s[i - str_len], str_len + 1);
			count++;
		}
		if (s[i] == '\0')
			break ;
		if (s[i] != c)
			str_len++;
		else
			str_len = 0;
		i++;
	}
	return (copy);
}

char	**lx_split(char *s, char c)
{
	char	**copy;
	size_t	copy_size;

	if (s == NULL)
		return (NULL);
	copy_size = ft_count_size(s, c, 0, 0);
	copy = ft_calloc(copy_size + 1, sizeof(char *));
	if (copy == NULL)
		return (NULL);
	copy = ft_store_str(s, c, copy, 0);
	if (copy == NULL)
		return (NULL);
	copy[copy_size] = NULL;
	return (copy);
}
