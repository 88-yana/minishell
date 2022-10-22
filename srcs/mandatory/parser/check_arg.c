/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:49:46 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 19:07:50 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

static bool	is_angle_bracket(char c)
{
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

static bool	is_cketbra(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) - 1)
	{
		if (str[i] == '>' && str[i + 1] == '<')
			return (false);
		i++;
	}
	return (true);
}

bool	check_arguments(char *str)
{
	size_t	i;
	size_t	quote;
	bool	during_quotes;

	during_quotes = false;
	i = 0;
	quote = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == DOUBLEQ)
			during_quotes = !during_quotes;
		if (during_quotes == false && is_angle_bracket(str[i]))
			quote++;
		else
			quote = 0;
		if (quote == 3)
			return (false);
		i++;
	}
	return (is_cketbra(str));
}
