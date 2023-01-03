/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:07:06 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/03 16:59:18 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

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

static void	init_ckeck_bracket(int *i, int *str_len, bool during_[2], int *pra)
{
	*i = -1;
	*str_len = -1;
	during_[DQ] = false;
	during_[SQ] = false;
	*pra = 0;
}

static void	change_pra(char c, int *pra)
{
	if (c == '(')
		(*pra)++;
	if (c == ')')
		(*pra)--;
}

static bool	ckeck_bracket(char *line)
{
	int		i;
	int		str_len;
	bool	during_[2];
	int		pra;

	init_ckeck_bracket(&i, &str_len, during_, &pra);
	while (1)
	{
		i++;
		str_len++;
		if (line[i] == DOUBLEQ)
			during_[DQ] = !during_[DQ];
		if (line[i] == SINGLEQ)
			during_[SQ] = !during_[SQ];
		if (during_[DQ] || during_[SQ])
			continue ;
		change_pra(line[i], &pra);
		if (pra < 0)
			return (false);
		if (line[i] == '\0')
			break ;
	}
	if (pra != 0)
		return (false);
	return (true);
}

bool	check_line(char *line)
{
	if (check_quote(line) == false)
		return (false);
	if (ckeck_bracket(line) == false)
	{
		printf("syntax error near unexpected token\n");
		return (false);
	}
	return (true);
}
