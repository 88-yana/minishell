/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:26:33 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:22:19 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

bool	match_quote(char *str, size_t *i, char quote)
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

bool	match_bracket(char *str, size_t *i)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != CKET
		&& str[*i] != SINGLEQ && str[*i] != DOUBLEQ)
		(*i)++;
	if (str[*i] == SINGLEQ)
		match_quote(str, i, SINGLEQ);
	else if (str[*i] == DOUBLEQ)
		match_quote(str, i, DOUBLEQ);
	else if (str[*i] == '\0')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `('", 2);
		return (false);
	}
	return (true);
}
