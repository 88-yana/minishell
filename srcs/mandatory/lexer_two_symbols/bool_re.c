/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_re.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:11:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 19:59:46 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer_two_symbols.h"

bool	is_separator_re(char c, char d)
{
	if ((c == '<' && d == '<'))
		return (true);
	if ((c == '>' && d == '>'))
		return (true);
	if ((c == '|' && d == '|'))
		return (true);
	if ((c == '&' && d == '&'))
		return (true);
	return (false);
}

bool	is_null(char c)
{
	if (c == '\0')
		return (true);
	return (false);
}