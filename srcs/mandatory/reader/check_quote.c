/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:07:06 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/12 14:27:47 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

static bool	check_quote(char *line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (line[i] == DOUBLEQ)
			if (match_quote(line, &i, DOUBLEQ) == false)
				return (false);
		if (line[i] == SINGLEQ)
			if (match_quote(line, &i, SINGLEQ) == false)
				return (false);
		i++;
	}
	return (true);
}

static bool	check_bra(char *line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (line[i] == BRA)
			if (match_bracket(line, &i) == false)
				return (false);
		i++;
	}
	return (true);
}

static bool	check_cket(char *line)
{
	size_t	i;
	size_t	cnt_bracket;

	i = 0;
	cnt_bracket = 0;
	while (i < ft_strlen(line))
	{
		if (line[i] == BRA)
			cnt_bracket++;
		if (line[i] == CKET)
			cnt_bracket--;
		if (line[i] == SINGLEQ)
			match_quote(line, &i, SINGLEQ);
		if (line[i] == DOUBLEQ)
			match_quote(line, &i, DOUBLEQ);
		i++;
	}
	if (cnt_bracket != 0)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `)'", 2);
		return (false);
	}
	return (true);
}

bool	check_line(char *line)
{
	if (check_quote(line) == false)
		return (false);
	if (check_bra(line) == false)
		return (false);
	if (check_cket(line) == false)
		return (false);
	return (true);
}
