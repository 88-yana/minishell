/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:11:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/04 14:01:10 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide.h"

bool	is_separator_div(char c)
{
	if (c == '\0')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	if (c == '(')
		return (true);
	if (c == ')')
		return (true);
	if (c == '|')
		return (true);
	if (c == '&')
		return (true);
	return (false);
}

bool	is_sep(char c)
{
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	if (c == '(')
		return (true);
	if (c == ')')
		return (true);
	return (false);
}
