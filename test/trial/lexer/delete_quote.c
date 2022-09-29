/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:49:50 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/29 21:57:48 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	delete_quote(char *str)
{
	size_t	i;

	if (ft_strchr(str, '$') != NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DUBLEQ)
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != DUBLEQ)
				i++;
			if (str[i] == '\0')
				break ;
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		if (str[i] == SINGLEQ)
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != SINGLEQ)
				i++;
			if (str[i] == '\0')
				break ;
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		i++;
	}
}

static void	shape_array(t_array *data)
{
	size_t	i;

	i = 0;
	while (data->array[i] != NULL)
	{
		delete_quote(data->array[i]);
		i++;
	}
}
