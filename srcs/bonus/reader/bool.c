/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:34:41 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 16:59:11 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

bool	is_se(char c)
{
	if (c == ' ')
		return (true);
	if (c == '\0')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	if (c == '&')
		return (true);
	if (c == '|')
		return (true);
	if (c == '(')
		return (true);
	if (c == ')')
		return (true);
	if (c == ';')
		return (true);
	return (false);
}

bool	is_dse(char c)
{
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	if (c == '&')
		return (true);
	if (c == '|')
		return (true);
	if (c == ';')
		return (true);
	return (false);
}

bool	is_bracket(const char c)
{
	if (c == '(')
		return (true);
	if (c == ')')
		return (true);
	return (false);
}

bool	is_redirect(t_type type)
{
	if (type == LT)
		return (true);
	if (type == GT)
		return (true);
	if (type == LTLT)
		return (true);
	if (type == GTGT)
		return (true);
	return (false);
}
