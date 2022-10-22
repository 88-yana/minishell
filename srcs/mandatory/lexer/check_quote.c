/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:07:06 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 19:48:12 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

static bool	match_quote(char *str, size_t *i, char quote)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != quote)
		(*i)++;
	if (str[*i] != quote)
	{
		ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
		return (false);
	}
	return (true);
}

bool	check_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
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
